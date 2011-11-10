#include "Engine.h"
#include "Segment.h"

using namespace Shipping;

void Segment::sourceIs( Fwk::Ptr<Location> _source )
{
	if (source_ != NULL) source_->segmentDel( this );
	source_ = _source;
	source_->segmentIs( this );
}

Segment::Segment( const string& _name, Mode _mode, Fwk::Ptr<Engine> _engine ) : 
NamedInterface(_name), mode_(_mode), engine_(_engine), 
	length_(0), difficulty_(1), expedite_(expNo_) {
		engine_->segmentIs(this);
}

void TruckSegment::sourceIs( Fwk::Ptr<Location> _source )
{
	if (_source == NULL) {
		if (source_ != NULL)
			source_->segmentDel( this );
		source_ = NULL;
	} else if( _source->type() != Location::boat() && _source->type() != Location::plane()  )
	{
		if (source_ != NULL)
			source_->segmentDel( this );
		source_ = _source;
		source_->segmentIs( this );
	} else {
		cerr << "Truck segment " << name() << " can't be connected to a plane or boat terminal." << endl;
	}
	return;
}

void BoatSegment::sourceIs( Fwk::Ptr<Location> _source )
{
	if (_source == NULL) {
		if (source_ != NULL)
			source_->segmentDel( this );
		source_ = NULL;
	} else if( _source != NULL && _source->type() != Location::truck() && _source->type() != Location::plane()  ) {
		if (source_ != NULL)
			source_->segmentDel( this );
		source_ = _source;
		source_->segmentIs( this );
	} else {
		cerr << "Boat segment " << name() << " can't be connected to a truck or plane terminal." << endl;
	}
	return;
}

void PlaneSegment::sourceIs( Fwk::Ptr<Location> _source )
{
	if (_source == NULL) {
		if (source_ != NULL)
			source_->segmentDel( this );
		source_ = NULL;
	} else if( _source != NULL && _source->type() != Location::truck() && _source->type() != Location::boat()  ) {
		if (source_ != NULL)
			source_->segmentDel( this );
		source_ = _source;
		source_->segmentIs( this );
	} else {
		cerr << "Plane segment " << name() << " can't be connected to a truck or boat terminal." << endl;
	}
	return;
}

void Segment::returnSegmentIs( Segment::Ptr _returnSegment )
{
	if( returnSegment_ == _returnSegment ||  (_returnSegment != NULL && (mode() != _returnSegment->mode())) )
	{
		return;
	}
	
	if( returnSegment_  != NULL )
	{
		returnSegment_->returnSegment_ = NULL;
	}

	if( _returnSegment != NULL )
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

Segment::NotifieeConst::~NotifieeConst() {
   if(notifier_ != NULL ) {
      notifier_->deleteNotifiee(this);
   }
   if(notifier_ != NULL &&isNonReferencing()) notifier_->newRef();
}

void
Segment::NotifieeConst::notifierIs(const Segment::PtrConst& _notifier) {
   Segment::Ptr notifierSave(const_cast<Segment *>(notifier_.ptr()));
   if(_notifier==notifier_) return;
   notifier_ = _notifier;
   if(notifierSave != NULL ) {
      notifierSave->deleteNotifiee(this);
   }
   if(_notifier != NULL ) {
      _notifier->newNotifiee(this);
   }
   if(isNonReferencing_) {
      if(notifierSave != NULL ) notifierSave->newRef();
      if(notifier_ != NULL ) notifier_->deleteRef();
   }
}

