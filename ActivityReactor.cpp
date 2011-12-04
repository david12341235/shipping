#include "ActivityReactor.h"
#include "ShippingTypes.h"

using namespace Shipping;
static int num = 0;

void InjectShipmentReactor::onStatus() {
    ActivityImpl::ManagerImpl::Ptr managerImpl = Fwk::ptr_cast<ActivityImpl::ManagerImpl>(manager_);
    switch (activity_->status()) {
	
    case Activity::executing:
	//I am executing now
		source_->shipmentIs(
			Shipment::ShipmentNew(
				"x", 
				source_->name(), 
				source_->destination(), 
				source_->shipmentSize()));
	break;
	
    case Activity::free:
	//when done, automatically enqueue myself for next execution
	activity_->nextTimeIs(Time(activity_->nextTime().value() + rate_));
	activity_->statusIs(Activity::nextTimeScheduled);
	break;

    case Activity::nextTimeScheduled:
	//add myself to be scheduled
	manager_->lastActivityIs(activity_);
	break;
	
    default:
	break;
    }

}

void ForwardShipmentReactor::onStatus() {
    ActivityImpl::ManagerImpl::Ptr managerImpl = Fwk::ptr_cast<ActivityImpl::ManagerImpl>(manager_);
    switch (activity_->status()) {
	
    case Activity::executing:
	//I am executing now
		for (Shipment::Ptr p = shipments_.front(); shipments_.size() > 0; shipments_.pop())
			segment_->returnSegment()->source()->shipmentIs(p);

		segment_->capacityIs(segment_->capacity().value() + numVehicles_.value());
	break;
	
    case Activity::free:
	//when done, automatically enqueue myself for next execution
	activity_->nextTimeIs(Time(activity_->nextTime().value() + rate_));
	activity_->statusIs(Activity::nextTimeScheduled);
	break;

    case Activity::nextTimeScheduled:
	//add myself to be scheduled
	manager_->lastActivityIs(activity_);
	break;
	
    default:
	break;
    }

}
