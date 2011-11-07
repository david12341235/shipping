#include "Engine.h"

using namespace Shipping;

Segment::SegmentId Segment::SegmentIdInstance ( int v ) {
	// TODO: implement
	return 0;
}

// ------- Location
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

Location::NotifieeConst::~NotifieeConst() {
   if(notifier_) {
      notifier_->deleteNotifiee(this);
   }
   if(notifier_&&isNonReferencing()) notifier_->newRef();
}

void
Location::NotifieeConst::notifierIs(const Location::PtrConst& _notifier) {
   Location::Ptr notifierSave(const_cast<Location *>(notifier_.ptr()));
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
}
*/

Stats::~Stats() {
}

