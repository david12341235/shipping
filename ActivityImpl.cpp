#include <iostream>
#include <time.h>

#include "ShippingException.h"
#include "ActivityImpl.h"
#ifdef WIN32
#include <Windows.h>
	void sleep(long s) { Sleep(s); }
#else
#include <unistd.h>
//	void sleep(long s) { usleep(s); }
#endif

Fwk::Ptr<Activity::Manager> activityManagerInstance() {
    return ActivityImpl::ManagerImpl::activityManagerInstance();
}

Fwk::Ptr<Activity::RealTimeManager> realTimeManagerInstance() {
    return ActivityImpl::RealTimeManagerImpl::realTimeManagerInstance();
}

namespace ActivityImpl {
    //Definition of static member
    Fwk::Ptr<Activity::Manager> ManagerImpl::activityInstance_ = NULL;
    Fwk::Ptr<Activity::RealTimeManager> RealTimeManagerImpl::instance_ = NULL;
    
    //Gets the singleton instance of ManagerImpl
    Fwk::Ptr<Activity::Manager> ManagerImpl::activityManagerInstance() {
	
	if (activityInstance_ == NULL) {
	    activityInstance_ = new ManagerImpl();
	}
	
	return activityInstance_;
    }
    
    Activity::Ptr ManagerImpl::activityNew(const string& name) {
	Activity::Ptr activity = activities_[name];

	if (activity != NULL) {
	    throw Shipping::NameExistsException("Activity already exists!");
	    return NULL;
	}
	
	activity = new ActivityImpl(name, this);
	activities_[name] = activity;

	return activity;
    }

    Activity::Ptr ManagerImpl::activity(const string& name) const {
	map<string, Activity::Ptr>::const_iterator it = activities_.find(name);
	
	if(it != activities_.end() ) {
	    return (*it).second;
	}
	
	// dont throw an exception (accessor)
	return NULL; 
    }
    
    void ManagerImpl::activityDel(const string& name) {
	activities_.erase(name);
    }
    
    void ManagerImpl::lastActivityIs(Activity::Ptr activity) {
	scheduledActivities_.push(activity);
    }

    void ManagerImpl::nowIs(Time t) {
	//find the most recent activites to run and run them in order
	while (!scheduledActivities_.empty()) {
	    
	    //figure out the next activity to run
	    Activity::Ptr nextToRun = scheduledActivities_.top();

	    //if the next time is greater than the specified time, break
	    //the loop
	    if (nextToRun->nextTime() > t) {
		break;
	    }
	    
	    now_ = nextToRun->nextTime();

	    //run the minimum time activity and remove it from the queue
	    scheduledActivities_.pop();

	    nextToRun->statusIs(Activity::executing);
	    nextToRun->statusIs(Activity::free);

	}

	//synchronize the time
	now_ = t;
	}


RealTimeManagerImpl::RealTimeManagerImpl() {
	managerImp_ = activityManagerInstance();
}

Activity::Ptr RealTimeManagerImpl::activityNew(const string& name) {
	return managerImp_->activityNew(name);
}

Activity::Ptr RealTimeManagerImpl::activity(const string& name) const {
	return managerImp_->activity(name);
}

void RealTimeManagerImpl::activityDel(const string& name) {
	managerImp_->activityDel(name);
}
	
Time RealTimeManagerImpl::now() const {
	return managerImp_->now();
}

void RealTimeManagerImpl::nowIs(Time time) {
	managerImp_->nowIs(time);
}
	
void RealTimeManagerImpl::lastActivityIs(Activity::Ptr activity) {
	managerImp_->lastActivityIs(activity);
}

Fwk::Ptr<Activity::RealTimeManager> RealTimeManagerImpl::realTimeManagerInstance() {
	if (instance_ == NULL) {
	    instance_ = new RealTimeManagerImpl();
	}
	
	return instance_;
}

void RealTimeManagerImpl::realTimePassedIs(Time time) {
	long msPerHour = 100; // 0.1 second advance per hour
	while (time >= 1.0) {
		Time currTime = managerImp_->now();

		managerImp_->nowIs(currTime.value() + 1);
	    //sleep 100ms
	    sleep(msPerHour);
		time = time.value() - 1;
	}
}

} //end namespace ActivityImpl
