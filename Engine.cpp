#include "Engine.h"

using namespace Shipping;

void Segment::sourceIs( Fwk::Ptr<Location> _source )
{
	if( _source )
	{
		source_->segmentDel( this );
		source_ = _source;
		source_->segmentIs( this );
	}
	return;
}

Segment::Segment( const string& _name, Mode _mode, Fwk::Ptr<Engine> _engine ) : 
NamedInterface(_name), mode_(_mode), engine_(_engine), 
	length_(0), difficulty_(0), expedite_(expNo_) {
		engine_->segmentIs(this);
}
	
Location::Location( const string& _name, Type _type, Fwk::Ptr<Engine> _engine ) :
NamedInterface(_name), type_(_type), engine_(_engine) {
	engine_->locationIs(this);
}

void TruckSegment::sourceIs( Fwk::Ptr<Location> _source )
{
	if( _source && _source->type() != Location::boat() && _source->type() != Location::plane()  )
	{
		source_->segmentDel( this );
		source_ = _source;
		source_->segmentIs( this );
	}
	return;
}

void BoatSegment::sourceIs( Fwk::Ptr<Location> _source )
{
	if( _source && _source->type() != Location::truck() && _source->type() != Location::plane()  )
	{
		source_->segmentDel( this );
		source_ = _source;
		source_->segmentIs( this );
	}
	return;
}

void PlaneSegment::sourceIs( Fwk::Ptr<Location> _source )
{
	if( _source && _source->type() != Location::truck() && _source->type() != Location::boat()  )
	{
		source_->segmentDel( this );
		source_ = _source;
		source_->segmentIs( this );
	}
	return;
}

void Segment::returnSegmentIs( Segment::Ptr _returnSegment )
{
	if( returnSegment_ == _returnSegment ||  mode() != _returnSegment->mode() )
	{
		return;
	}

	if( returnSegment_ )
	{
		returnSegment_->returnSegmentIs( NULL );
	}
	
	if( _returnSegment )
	{
		returnSegment_ = _returnSegment;
		if( returnSegment_->returnSegment() != this )
		{
			returnSegment_->returnSegmentIs( this );
		}
	}
	else
	{
		returnSegment_ = NULL;
	}

	return;
}

void Segment::expediteIs( ExpVal e )
{
	ExpVal old = expedite_;
	expedite_ = e;
	retry:
	U32 ver = notifiee_.version();
	if(notifiees()) for(NotifieeIterator n=notifieeIter();n.ptr();++n) try {
		n->onExpedite(this, old);
	    if( ver != notifiee_.version() ) goto retry;
	 } catch(...) { n->onNotificationException(NotifieeConst::segment__); }
}

// ------- Location

void Location::segmentDel( Segment::PtrConst _segment )
{
	for( SegmentList::iterator iter = segment_.begin(); iter != segment_.end(); iter++ )
	{
		if( *iter == _segment )
		{
			segment_.erase( iter );
			break;
		}
	}
}

void
Location::onZeroReferences() {
  retry:
   U32 ver = notifiee_.version();
   if(notifiees()) for( NotifieeIterator n = notifieeIter(); n.ptr(); ++n ) try {
      n->isNonReferencingIs(false);
      n->onDelete();
      if(ver != notifiee_.version()) goto retry;
      // If notification modified the list, then restart the iteration
   }
   catch(...) { n->onNotificationException(Fwk::RootNotifiee::references__); }
   if(notifiees()) {
      assert(references());
      return;
   }
   // handle case of notifiee being notified when refcount goes to zero
   // vs. autodelete by the notifiee destructor
   // Notifiees that do not hold a smart pointer to the notifier
   // (like proxy instances of TacEntityLog) must remove themselves
   // from the notifiee list.
   delete this;
}
//----------| NotifieeConst Implementation |------------//

Segment::NotifieeConst::~NotifieeConst() {
   if(notifier_) {
      notifier_->deleteNotifiee(this);
   }
   if(notifier_&&isNonReferencing()) notifier_->newRef();
}

void
Segment::NotifieeConst::notifierIs(const Segment::PtrConst& _notifier) {
   Segment::Ptr notifierSave(const_cast<Segment *>(notifier_.ptr()));
   if(_notifier==notifier_) return;
   notifier_ = _notifier;
   if(notifierSave) {
      notifierSave->deleteNotifiee(this);
   }
   if(_notifier) {
      _notifier->newNotifiee(this);
   }
   if(isNonReferencing_) {
      if(notifierSave) notifierSave->newRef();
      if(notifier_) notifier_->deleteRef();
   }
}

void Engine::segmentIs(Segment::Ptr s) {
  string name = s->name();
  Segment::Ptr m = segment_[name];
   if(m) {
      throw Fwk::NameInUseException(name);
   } else {
     m = s;
     segment_.newMember(m);
	 if (!expreactor_) 
		 expreactor_ = Stats::SegmentExpediteReactor::SegmentExpediteReactorIs(s, this);
	 s->newNotifiee(expreactor_);
   }
   retrycell:
   U32 ver = notifiee_.version();
   if(notifiees()) for(NotifieeIterator n=notifieeIter();n.ptr();++n) try {
	   n->onSegmentIs(s);
      if( ver != notifiee_.version() ) goto retrycell;
   } catch(...) { n->onNotificationException(NotifieeConst::segment__); }
}

void Engine::locationIs(Location::Ptr s) {
  string name = s->name();
  Location::Ptr m = location_[name];
   if(m) {
      throw Fwk::NameInUseException(name);
   } else {
     m = s;
     location_.newMember(m);
   }
   retrycell:
   U32 ver = notifiee_.version();
   if(notifiees()) for(NotifieeIterator n=notifieeIter();n.ptr();++n) try {
	   n->onLocationIs(s);
      if( ver != notifiee_.version() ) goto retrycell;
   } catch(...) { n->onNotificationException(NotifieeConst::location__); }
}


void
Location::NotifieeConst::isNonReferencingIs(bool _isNonReferencing){
   if(_isNonReferencing==isNonReferencing_) return;
   isNonReferencing_ = _isNonReferencing;
   if(notifier_) {
      if(_isNonReferencing) notifier_->deleteRef();
      else notifier_->newRef();
   }
}

//----------| Notifiee Implementation |------------//
/*
Fwk::String
Location::attributeString( Fwk::RootNotifiee::AttributeId a ) const {
   Fwk::String str = "unknown";
   switch(a) {
      case NotifieeConst::version__: str = "version"; break;
      case NotifieeConst::notificationException__: str = "notificationException"; break;
      case NotifieeConst::membrane__: str = "membrane"; break;
      case NotifieeConst::Location__: str = "Location"; break;
      default: str = Fwk::RootNotifiee::attributeString(a); break;
   }
   return str;
>>>>>>> d246abdc59a33bca662561918e0790d9051d3027
}
*/

Stats::~Stats() {
}

Stats::Stats( const string& _name, Fwk::Ptr<Engine> _engine) :
		NamedInterface(_name), engine_(_engine), customer_(0), 
		port_(0), truckTerminal_(0), boatTerminal_(0),
		planeTerminal_(0), boatSegment_(0), truckSegment_(0), 
		planeSegment_(0), expedite_(0) { 
	engine_->statsIs(this);
}

// ======== Engine
/*void
Engine::onZeroReferences() {
  retry:
   U32 ver = notifiee_.version();
   if(notifiees()) for( NotifieeIterator n = notifieeIter(); n.ptr(); ++n ) try {
      n->isNonReferencingIs(false);
      n->onDelete();
      if(ver != notifiee_.version()) goto retry;
      // If notification modified the list, then restart the iteration
   }
   catch(...) { n->onNotificationException(Fwk::RootNotifiee::references__); }
   if(notifiees()) {
      assert(references());
      return;
   }
   // handle case of notifiee being notified when refcount goes to zero
   // vs. autodelete by the notifiee destructor
   // Notifiees that do not hold a smart pointer to the notifier
   // (like proxy instances of TacEntityLog) must remove themselves
   // from the notifiee list.
   delete this;
}*/
//----------| NotifieeConst Implementation |------------//

Engine::NotifieeConst::~NotifieeConst() {
   if(notifier_) {
      notifier_->deleteNotifiee(this);
   }
   if(notifier_&&isNonReferencing()) notifier_->newRef();
}

void
Engine::NotifieeConst::notifierIs(const Engine::PtrConst& _notifier) {
   Engine::Ptr notifierSave(const_cast<Engine *>(notifier_.ptr()));
   if(_notifier==notifier_) return;
   notifier_ = _notifier;
   if(notifierSave) {
      notifierSave->deleteNotifiee(this);
   }
   if(_notifier) {
      _notifier->newNotifiee(this);
   }
   if(isNonReferencing_) {
      if(notifierSave) notifierSave->newRef();
      if(notifier_) notifier_->deleteRef();
   }
}

void
Engine::NotifieeConst::isNonReferencingIs(bool _isNonReferencing){
   if(_isNonReferencing==isNonReferencing_) return;
   isNonReferencing_ = _isNonReferencing;
   if(notifier_) {
      if(_isNonReferencing) notifier_->deleteRef();
      else notifier_->newRef();
   }
}

void Engine::statsIs(Stats::Ptr s) { 
	stats_ = s;
	slreactor_ = Stats::LocationSegmentReactor::LocationSegmentReactorIs(this);
}

//----------| Notifiee Implementation |------------//
/*
Fwk::String
Location::attributeString( Fwk::RootNotifiee::AttributeId a ) const {
   Fwk::String str = "unknown";
   switch(a) {
      case NotifieeConst::version__: str = "version"; break;
      case NotifieeConst::notificationException__: str = "notificationException"; break;
      case NotifieeConst::membrane__: str = "membrane"; break;
      case NotifieeConst::Location__: str = "Location"; break;
      default: str = Fwk::RootNotifiee::attributeString(a); break;
   }
   return str;
>>>>>>> d246abdc59a33bca662561918e0790d9051d3027
}
*/

Fwk::String valueToStrep(string s) { return s; }
