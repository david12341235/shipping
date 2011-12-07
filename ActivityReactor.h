#ifndef __ACTIVITY_REACTOR_H__
#define __ACTIVITY_REACTOR_H__

#include "Engine.h"
#include "ActivityImpl.h"
    
namespace Shipping {
	
class InjectShipmentReactor : public Activity::Notifiee {
 public:
 InjectShipmentReactor(Fwk::Ptr<Activity::Manager> manager, Activity*
			 activity, double rate, Customer::Ptr source) 
     : Notifiee(activity), rate_(rate), activity_(activity), 
	 manager_(manager), source_(source) {}

    void onStatus();

 protected:
    double rate_;
    Activity::Ptr activity_;
    Fwk::Ptr<Activity::Manager> manager_;
	Customer::Ptr source_;
};      

class ForwardShipmentReactor : public Activity::Notifiee {
 public:
 ForwardShipmentReactor(Fwk::Ptr<Activity::Manager> manager, Activity*
			 activity, double rate, Segment::Ptr segment, 
			 ShipmentQueue shipments, NumVehicles numVehicles) 
     : Notifiee(activity), activity_(activity), 
	 manager_(manager), segment_(segment), numVehicles_(numVehicles), shipments_(shipments) {}

    void onStatus();

 protected:
    Activity::Ptr activity_;
    Fwk::Ptr<Activity::Manager> manager_;
	Segment::Ptr segment_;
	NumVehicles numVehicles_;
	ShipmentQueue shipments_;
};      

class ScheduledAttributeReactor : public Activity::Notifiee {
 public:
 ScheduledAttributeReactor(Fwk::Ptr<Activity::Manager> manager, Activity*
			 activity, Fwk::Ptr<Instance> instance,
			 string attributeName, string attributeValue) 
     : Notifiee(activity), activity_(activity), 
	 manager_(manager), instance_(instance),
	 attributeName_(attributeName), attributeValue_(attributeValue) {}

    void onStatus();

 protected:
    Activity::Ptr activity_;
    Fwk::Ptr<Activity::Manager> manager_;
	Fwk::Ptr<Instance> instance_;
	string attributeName_;
	string attributeValue_;
};      

} // namespace
#endif
