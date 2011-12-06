#include "Engine.h"

using namespace Shipping;

Location::Location( const string& _name, Type _type, Fwk::Ptr<Engine> _engine ) :
    NamedInterface(_name), type_(_type), engine_(_engine)
{
    engine_->locationIs(this);
}

Location::Location( const string& _name, Type _type) :
    NamedInterface(_name), type_(_type), engine_(NULL)
{
}


// ------- Location

void Location::segmentDel( Segment::PtrConst _segment )
{
    for( SegmentList::iterator iter = segment_.begin(); iter != segment_.end(); iter++ ) {
        if( *iter == _segment ) {
            segment_.erase( iter );
            break;
        }
    }
}

void Location::shipmentIs( Shipment::Ptr _newShipment )
{
	// figure out the next segment to forward the packet to and immediately
	// queue it onto that segment
	Segment::Ptr _segment = nextSegment_[ _newShipment->destination()];
	_segment->shipmentIs( _newShipment );
}

void
Location::onZeroReferences()
{
retry:
    U32 ver = notifiee_.version();
    if(notifiees()) for( NotifieeIterator n = notifieeIter(); n.ptr(); ++n ) try {
                n->isNonReferencingIs(false);
                n->onDelete();
                if(ver != notifiee_.version()) goto retry;
                // If notification modified the list, then restart the iteration
            } catch(...) {
                n->onNotificationException(Fwk::RootNotifiee::references__);
            }
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

void
Location::NotifieeConst::isNonReferencingIs(bool _isNonReferencing)
{
    if(_isNonReferencing==isNonReferencing_) return;
    isNonReferencing_ = _isNonReferencing;
    if(notifier_ != NULL ) {
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

void Customer::transferRateIs(ShipmentsPerDay _transferRate) {
	if (_transferRate != transferRate_) {
		transferRate_ = _transferRate;
		if (transferRate_ == 0)
			sendingShipmentsIs(false);
		else
			sendingShipmentsIs(true);
	}
}

void Customer::shipmentSizeIs(NumPackages _shipmentSize) {
	if (_shipmentSize != shipmentSize_) {
		shipmentSize_ = _shipmentSize;
		if (shipmentSize_ == 0)
			sendingShipmentsIs(false);
		else
			sendingShipmentsIs(true);
	}
}

void Customer::destinationIs(string _destination) {
	if (_destination != destination_) {
		destination_ = _destination;
		if (destination_ == "")
			sendingShipmentsIs(false);
		else
			sendingShipmentsIs(true);
	}
}
	
void Customer::sendingShipmentsIs(bool _sendingShipments) {
	if (sendingShipments_ == _sendingShipments) return;
	 if (_sendingShipments && (destination_ == "" || transferRate_ == 0 || shipmentSize_ == 0)) return;

    sendingShipments_ = _sendingShipments;
retry:
    U32 ver = notifiee_.version();
    if(notifiees()) for(NotifieeIterator n=notifieeIter(); n.ptr(); ++n) try {
                n->onSendingShipmentsIs(this);
                if( ver != notifiee_.version() ) goto retry;
            } catch(...) {
                n->onNotificationException(NotifieeConst::customer__);
            }
}

void
Customer::NotifieeConst::notifierIs(const Customer::PtrConst& _notifier)
{
    Customer::Ptr notifierSave(const_cast<Customer *>(notifier_.ptr()));
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

void Customer::shipmentIs(Shipment::Ptr _newShipment) {
	cout << this->name() << " received shipment: " << _newShipment->name() << endl;
	if( _newShipment->destination() == name() )
	{
		map<string, NumPackages>::iterator found = shipmentsPending_.find( _newShipment->destination() );
		if( found == shipmentsPending_.end() )
		{
			shipmentsPending_.insert( pair<string, NumPackages>( _newShipment->destination(), _newShipment->load() ) );
		}
		else if( found->second.value() + _newShipment->load().value() == _newShipment->origSize().value() )
		{
			// one complete shipment received. update stats
		    ++shipmentsReceived_;
		    // this calculation is not correct. Maybe we should consider time stamping the
		    // shipment, once for when the shipment is first injected and also whenever
		    // it arrives at a new location
		    totalLatency_ = totalLatency_.value() + _newShipment->timeShipped().value();
		    totalCost_ = totalCost_.value() + _newShipment->cost().value();
		    shipmentsPending_.erase( found );
		}
		else
		{
			// update the count for this package
			found->second = NumPackages( found->second.value() + _newShipment->load().value() );
		}
	}
	else
	{
		// initial injection
		Segment::Ptr _segment = nextSegment_[ _newShipment->destination()];
		_segment->shipmentIs( _newShipment );
	}
}

Customer::NotifieeConst::~NotifieeConst()
{
    if(notifier_ != NULL ) {
        notifier_->deleteNotifiee(this);
    }
    if(notifier_ != NULL &&isNonReferencing()) notifier_->newRef();
}

Location::NotifieeConst::~NotifieeConst()
{
    if(notifier_ != NULL ) {
        notifier_->deleteNotifiee(this);
    }
    if(notifier_ != NULL &&isNonReferencing()) notifier_->newRef();
}

void
Location::NotifieeConst::notifierIs(const Location::PtrConst& _notifier)
{
    Location::Ptr notifierSave(const_cast<Location*>(notifier_.ptr()));
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

Customer::Customer( const string& _name, Fwk::Ptr<Engine> _engine ) : 
	Location( _name, customer_), transferRate_(0), shipmentSize_(0), 
    shipmentsReceived_(0), totalLatency_(0), totalCost_(0) {
	engine_ = _engine;
	engine_->locationIs(this);
};
