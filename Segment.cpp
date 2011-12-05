#include "Engine.h"
#include "Segment.h"
#include "Activity.h"
#include "ActivityReactor.h"

using namespace Shipping;

void Segment::sourceIs( Fwk::Ptr<Location> _source )
{
    if (source_ != NULL) source_->segmentDel( this );
    source_ = _source;
    source_->segmentIs( this );
}

Segment::Segment( const string& _name, Mode _mode, Fwk::Ptr<Engine> _engine ) :
    NamedInterface(_name), mode_(_mode), engine_(_engine),
    length_(0), difficulty_(1), expedite_(expNo_), shipmentsReceived_(0), shipmentsRefused_(0),
    shipmentsPending_(0), capacity_(10)
{
    engine_->segmentIs(this);
}

void Segment::shipmentIs( Shipment::Ptr _newShipment )
{
	if (capacity_ == 0) {
		shipmentQ_.push_back(_newShipment);
		++shipmentsRefused_;
	} else {
		readyForShipmentIs(true);
	}


	// must schedule a forwarding activity. Should be scheduled for a time
	// based on segment length, speed, and number of carriers it has, per
	// the assignment example. Shipment may consist of many packages
	// in which case several forwarding activities may have to be scheduled
	// for one shipment. Also, maybe good to throw an exception if this new
	// shipment causes overflow of the capacity, since this isn't supposed to
	// happen if the source location is following the protocol of queuing a
	// new shipment onto Segment only when Segment has the capacity to do so.
}

void TruckSegment::sourceIs( Fwk::Ptr<Location> _source )
{
    if (_source == NULL) {
        if (source_ != NULL)
            source_->segmentDel( this );
        source_ = NULL;
    } else if( _source->type() != Location::boat() && _source->type() != Location::plane()  ) {
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
    if( returnSegment_ == _returnSegment ||  (_returnSegment != NULL && (mode() != _returnSegment->mode())) ) {
        return;
    }

    if( returnSegment_  != NULL ) {
        returnSegment_->returnSegment_ = NULL;
    }

    if( _returnSegment != NULL ) {
        returnSegment_ = _returnSegment;
        if( returnSegment_->returnSegment() != this ) {
            returnSegment_->returnSegmentIs( this );
        }
    } else {
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
    if(notifiees()) for(NotifieeIterator n=notifieeIter(); n.ptr(); ++n) try {
                n->onExpedite(this, old);
                if( ver != notifiee_.version() ) goto retry;
            } catch(...) {
                n->onNotificationException(NotifieeConst::segment__);
            }
}

void Segment::capacityIs(NumVehicles v) {
	if (v == capacity_) return;
	NumVehicles old(capacity_);
	capacity_ = v;

	if (capacity_ > 0) {
		readyForShipmentIs(true);
	}

	if (capacity_ == old) return;
retry:
    U32 ver = notifiee_.version();
    if(notifiees()) for(NotifieeIterator n=notifieeIter(); n.ptr(); ++n) try {
                n->onCapacity(this);
                if( ver != notifiee_.version() ) goto retry;
            } catch(...) {
                n->onNotificationException(NotifieeConst::segment__);
            }
}

void Segment::readyForShipmentIs(bool b) {
	if (b == false) return;
	
	Activity::Manager::Ptr manager = activityManagerInstance();
	string name = "forward shipment #";
	ostringstream oss;
	oss << rand();
	name.append(oss.str());
	Activity::Ptr fwd = manager->activityNew(name);

	ShipmentQueue shipments;
	NumVehicles currentVehicles(capacity());
	NumPackages vehicleCapacity(engine_->fleet()->capacity(mode()).value());
	NumPackages totalCapacity(
		currentVehicles.value() * vehicleCapacity.value());
	NumPackages packageCount(0);

	NumVehicles vehicles(0);

	for (Shipment::Ptr s = shipmentQ_.front(); !shipmentQ_.empty() && 
			packageCount < totalCapacity; ) {
		NumPackages load = s->load();
		if (load.value() > totalCapacity.value()) { // split shipment
			s->loadIs(load.value() - totalCapacity.value());
			load = totalCapacity;
			shipmentQ_.push_front(
				Shipment::ShipmentNew(
					s->name(), 
					s->source(), 
					s->destination(), 
					load));
		}
		// now we're guaranteed to have at least one shipment at the
		// front of the queue that we can send off
		shipments.push_front(s);
		shipmentQ_.pop_front();
		packageCount = packageCount.value() + load.value();
		totalCapacity = totalCapacity.value() - load.value();
	}

	vehicles = packageCount.value() / vehicleCapacity.value() +
		packageCount.value() % vehicleCapacity.value();

	fwd->lastNotifieeIs(new ForwardShipmentReactor(manager,
								fwd.ptr(), 0, this, shipments, vehicles)); 
}

Segment::NotifieeConst::~NotifieeConst()
{
    if(notifier_ != NULL ) {
        notifier_->deleteNotifiee(this);
    }
    if(notifier_ != NULL &&isNonReferencing()) notifier_->newRef();
}

void
Segment::NotifieeConst::notifierIs(const Segment::PtrConst& _notifier)
{
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

