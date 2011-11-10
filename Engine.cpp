#include "Engine.h"

using namespace Shipping;	

void Engine::locationIs(Location::Ptr l) {
  string name = l->name();
  Location::Ptr m = location_[name];
   if(m) {
      throw Fwk::NameInUseException(name);
   } else {
     m = l;
     location_.newMember(m);
   }
   retrycell:
   U32 ver = notifiee_.version();
   if(notifiees()) for(NotifieeIterator n=notifieeIter();n.ptr();++n) try {
	   n->onLocationIs(l);
       if( ver != notifiee_.version() ) goto retrycell;
   } catch(...) { n->onNotificationException(NotifieeConst::location__); }
}

void Engine::locationDel(const string& l) {
  try {
	  Location::Ptr p = location_[l];
	  int i = 1;
	  Segment::PtrConst s = p->segment(i); 
	  while(s) {
		  segment_[s->name()]->sourceIs(NULL);
		  s = p->segment(++i); 
	  }
	  location_.memberDel(l);
  } catch (...) {}
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

void Engine::segmentDel(const string& s) {
  try {
	  Segment::Ptr p = segment_[s];
	  p->returnSegment()->returnSegmentIs(NULL);
	  segment_.memberDel(s);
  } catch (...) {}
}

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

Fwk::String valueToStrep(string s) { return s; }

Stats::~Stats() {
}

Stats::Stats( const string& _name, Fwk::Ptr<Engine> _engine) :
		NamedInterface(_name), engine_(_engine), customer_(0), 
		port_(0), truckTerminal_(0), boatTerminal_(0),
		planeTerminal_(0), boatSegment_(0), truckSegment_(0), 
		planeSegment_(0), expedite_(0) { 
	engine_->statsIs(this);
}

