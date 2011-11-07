#include <stdlib.h>
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "Instance.h"
#include "Engine.h"
#include "fwk/ListRaw.h"
#include "fwk/NamedInterface.h"

namespace Shipping {
	
using namespace std;
using std::string;

//
// Rep layer classes
//

class ManagerImpl : public Instance::Manager {
public:
    ManagerImpl();

    // Manager method
    Ptr<Instance> instanceNew(const string& name, const string& type);

    // Manager method
    Ptr<Instance> instance(const string& name);

    // Manager method
    void instanceDel(const string& name);

    Engine::Ptr engine();

private:
    map<string,Ptr<Instance> > instance_;
    Engine::Ptr engine_;
};


class LocationRep : public Instance {
public:

    LocationRep(const string& name, ManagerImpl* manager) :
        Instance(name), manager_(manager)
    {
        // Nothing else to do.
    }

    // Instance method
	string attribute(const string& name);

    // Instance method
	void attributeIs(const string& name, const string& v);

private:
    Ptr<ManagerImpl> manager_;
    Segment::SegmentId segmentNumber(const string& name);
	Location::Ptr location_;
};
                                                                                                  
class CustomerRep : public LocationRep {
public:

    CustomerRep(const string& name, ManagerImpl *manager) :
        LocationRep(name, manager)
    {
		manager->engine()->locationIs(Customer::CustomerNew(name, manager->engine()));
    }

};

class PortRep : public LocationRep {
public:

    PortRep(const string& name, ManagerImpl *manager) :
        LocationRep(name, manager)
    {
        // Nothing else to do.
    }

};

class TruckTerminalRep : public LocationRep {
public:

    TruckTerminalRep(const string& name, ManagerImpl *manager) :
        LocationRep(name, manager)
    {
        // Nothing else to do.
    }

};

class BoatTerminalRep : public LocationRep {
public:

    BoatTerminalRep(const string& name, ManagerImpl *manager) :
        LocationRep(name, manager)
    {
        // Nothing else to do.
    }

};

class PlaneTerminalRep : public LocationRep {
public:

    PlaneTerminalRep(const string& name, ManagerImpl *manager) :
        LocationRep(name, manager)
    {
        // Nothing else to do.
    }

};

class SegmentRep : public Instance {
public:

    SegmentRep(const string& name, ManagerImpl* manager) :
        Instance(name), manager_(manager)
    {
        // Nothing else to do.
    }

    // Instance method
	string attribute(const string& name) { return ""; };

    // Instance method
	void attributeIs(const string& name, const string& v) {};

protected:
	Segment::Ptr segment_;

private:
    Ptr<ManagerImpl> manager_;
};

class TruckSegmentRep : public SegmentRep {
public:

    TruckSegmentRep(const string& name, ManagerImpl *manager) :
        SegmentRep(name, manager)
    {
        // Nothing else to do.
    }

};

class BoatSegmentRep : public SegmentRep {
public:

    BoatSegmentRep(const string& name, ManagerImpl *manager) :
        SegmentRep(name, manager)
    {
        // Nothing else to do.
    }

};

class PlaneSegmentRep : public SegmentRep {
public:

    PlaneSegmentRep(const string& name, ManagerImpl *manager) :
        SegmentRep(name, manager)
    {
        // Nothing else to do.
    }

};

class FleetRep : public Instance {
public:

    FleetRep(const string& name, ManagerImpl* manager) :
        Instance(name), manager_(manager)
    {
        // Nothing else to do.
    }

    // Instance method
	string attribute(const string& name) { return ""; };

    // Instance method
	void attributeIs(const string& name, const string& v) {};

private:
    Ptr<ManagerImpl> manager_;
	Fleet::Ptr fleet_;
};

class ConnRep : public Instance {
public:

    ConnRep(const string& name, ManagerImpl* manager) :
        Instance(name), manager_(manager)
    {
        // Nothing else to do.
    }

    // Instance method
	string attribute(const string& name) { return ""; };

    // Instance method
	void attributeIs(const string& name, const string& v) {};

private:
    Ptr<ManagerImpl> manager_;
	Conn::Ptr conn_;
};

class StatsRep : public Instance {
public:

    StatsRep(const string& name, ManagerImpl* manager) :
	  Instance(name), manager_(manager)
    {
		//stats_ = Stats::StatsNew(name, manager_->engine());
    }

    // Instance method
	string attribute(const string& name) { return ""; };

    // Instance method
	void attributeIs(const string& name, const string& v) {};

private:
    Ptr<ManagerImpl> manager_;
	Stats::Ptr stats_;
};

ManagerImpl::ManagerImpl() {
}

Ptr<Instance> ManagerImpl::instanceNew(const string& name, const string& type) {
    if (type == "Truck terminal") {
        Ptr<TruckTerminalRep> t = new TruckTerminalRep(name, this);
        instance_[name] = t;
        return t;
    } else if (type == "Boat terminal") {
        Ptr<BoatTerminalRep> t = new BoatTerminalRep(name, this);
        instance_[name] = t;
        return t;
    } else if (type == "Plane terminal") {
        Ptr<PlaneTerminalRep> t = new PlaneTerminalRep(name, this);
        instance_[name] = t;
        return t;
    } else if (type == "Customer") {
        Ptr<CustomerRep> t = new CustomerRep(name, this);
        instance_[name] = t;
        return t;
    } else if (type == "Port") {
        Ptr<PortRep> t = new PortRep(name, this);
        instance_[name] = t;
        return t;
    } else if (type == "Truck segment") {
        Ptr<TruckSegmentRep> t = new TruckSegmentRep(name, this);
        instance_[name] = t;
        return t;
    } else if (type == "Boat segment") {
        Ptr<BoatSegmentRep> t = new BoatSegmentRep(name, this);
        instance_[name] = t;
        return t;
    } else if (type == "Plane segment") {
        Ptr<PlaneSegmentRep> t = new PlaneSegmentRep(name, this);
        instance_[name] = t;
        return t;
    } else if (type == "Stats") {
        Ptr<StatsRep> t = new StatsRep(name, this);
        instance_[name] = t;
        return t;
    } else if (type == "Conn") {
        Ptr<ConnRep> t = new ConnRep(name, this);
        instance_[name] = t;
        return t;
    } else if (type == "Fleet") {
        Ptr<FleetRep> t = new FleetRep(name, this);
        instance_[name] = t;
        return t;
    }

    return NULL;
}

Ptr<Instance> ManagerImpl::instance(const string& name) {
    map<string,Ptr<Instance> >::const_iterator t = instance_.find(name);

	if( t == instance_.end() ) return NULL;
	else return (*t).second;
    //return t == instance_.end() ? NULL : (*t).second;
}

void ManagerImpl::instanceDel(const string& name) {
}


string LocationRep::attribute(const string& name) {
    int i = segmentNumber(name);
    if (i != 0) {
        cout << "Tried to read interface " << i;
    }
    return "";
}


void LocationRep::attributeIs(const string& name, const string& v) {
    //nothing to do
}

static const string segmentStr = "segment";
static const int segmentStrlen = segmentStr.length();

Segment::SegmentId LocationRep::segmentNumber(const string& name) {
    if (name.substr(0, segmentStrlen) == segmentStr) {
        const char* t = name.c_str() + segmentStrlen;
        return Segment::SegmentIdInstance( atoi(t) );
    }
    return 0;
}

}


/*
 * This is the entry point for your library.
 * The client program will call this function to get a handle
 * on the Instance::Manager object, and from there will use
 * that object to interact with the middle layer (which will
 * in turn interact with the engine layer).
 */
Ptr<Instance::Manager> shippingInstanceManager() {
    return new Shipping::ManagerImpl();
}

Shipping::Engine::Ptr Shipping::ManagerImpl::engine() {
	return NULL;
}
