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
	typedef Fwk::Ptr<LocationRep const> PtrConst;
	typedef Fwk::Ptr<LocationRep> Ptr;

    // Instance method
	string attribute(const string& name);

    // Instance method
	void attributeIs(const string& name, const string& v);

protected:
    LocationRep(const string& name, ManagerImpl* manager) :
        Instance(name), manager_(manager)
    {
        // Nothing else to do.
    }
    Fwk::Ptr<ManagerImpl> manager_;
    Segment::SegmentId segmentNumber(const string& name);
	Location::Ptr location_;
};
                                                                                                  
class CustomerRep : public LocationRep {
public:
	static LocationRep::Ptr CustomerRepNew( const string& _name, ManagerImpl* manager) {
		Ptr m = new CustomerRep(_name, manager);
		m->referencesDec(1);
		return m;
	}
protected:
    CustomerRep(const string& name, ManagerImpl *manager) :
        LocationRep(name, manager)
    {
		manager->engine()->locationIs(Customer::CustomerNew(name, manager->engine()));
    }
};

class PortRep : public LocationRep {
public:
	static LocationRep::Ptr PortRepNew( const string& _name, ManagerImpl* manager) {
		Ptr m = new PortRep(_name, manager);
		m->referencesDec(1);
		return m;
	}
protected:
    PortRep(const string& name, ManagerImpl *manager) :
        LocationRep(name, manager)
    {
		manager->engine()->locationIs(Port::PortNew(name, manager->engine()));
    }
};

class TruckTerminalRep : public LocationRep {
public:
	static LocationRep::Ptr TruckTerminalRepNew( const string& _name, ManagerImpl* manager) {
		Ptr m = new TruckTerminalRep(_name, manager);
		m->referencesDec(1);
		return m;
	}
protected:
    TruckTerminalRep(const string& name, ManagerImpl *manager) :
        LocationRep(name, manager)
    {
		manager->engine()->locationIs(TruckLocation::TruckLocationNew(name, manager->engine()));
    }
};

class BoatTerminalRep : public LocationRep {
public:
	static LocationRep::Ptr BoatTerminalRepNew( const string& _name, ManagerImpl* manager) {
		Ptr m = new BoatTerminalRep(_name, manager);
		m->referencesDec(1);
		return m;
	}
protected:
    BoatTerminalRep(const string& name, ManagerImpl *manager) :
        LocationRep(name, manager)
    {
		manager->engine()->locationIs(BoatLocation::BoatLocationNew(name, manager->engine()));
    }
};

class PlaneTerminalRep : public LocationRep {
public:
	static LocationRep::Ptr PlaneTerminalRepNew( const string& _name, ManagerImpl* manager) {
		Ptr m = new PlaneTerminalRep(_name, manager);
		m->referencesDec(1);
		return m;
	}
protected:
    PlaneTerminalRep(const string& name, ManagerImpl *manager) :
        LocationRep(name, manager)
    {
		manager->engine()->locationIs(PlaneLocation::PlaneLocationNew(name, manager->engine()));
    }
};

class SegmentRep : public Instance {
public:
	typedef Fwk::Ptr<SegmentRep const> PtrConst;
	typedef Fwk::Ptr<SegmentRep> Ptr;

    // Instance method
	string attribute(const string& name) { return ""; };

    // Instance method
	void attributeIs(const string& name, const string& v) {};

protected:
    SegmentRep(const string& name, ManagerImpl* manager) :
        Instance(name), manager_(manager) {}

    Segment::Ptr segment_;
    Fwk::Ptr<ManagerImpl> manager_;
};

class TruckSegmentRep : public SegmentRep {
public:
	static SegmentRep::Ptr TruckSegmentRepNew( const string& _name, ManagerImpl* manager) {
		Ptr m = new TruckSegmentRep(_name, manager);
		m->referencesDec(1);
		return m;
	}

protected:
    TruckSegmentRep(const string& name, ManagerImpl *manager) :
        SegmentRep(name, manager) {}
};

class BoatSegmentRep : public SegmentRep {
public:
	static SegmentRep::Ptr BoatSegmentRepNew( const string& _name, ManagerImpl* manager) {
		Ptr m = new BoatSegmentRep(_name, manager);
		m->referencesDec(1);
		return m;
	}

private:
    BoatSegmentRep(const string& name, ManagerImpl *manager) :
        SegmentRep(name, manager) {}

};

class PlaneSegmentRep : public SegmentRep {
public:
	static SegmentRep::Ptr PlaneSegmentRepNew( const string& _name, ManagerImpl* manager) {
		Ptr m = new PlaneSegmentRep(_name, manager);
		m->referencesDec(1);
		return m;
	}

protected:
    PlaneSegmentRep(const string& name, ManagerImpl *manager) :
        SegmentRep(name, manager) {}
};

class FleetRep : public Instance {
public:
	typedef Fwk::Ptr<FleetRep const> PtrConst;
	typedef Fwk::Ptr<FleetRep> Ptr;

	static FleetRep::Ptr FleetRepNew( const string& _name, ManagerImpl* manager) {
		Ptr m = new FleetRep(_name, manager);
		m->referencesDec(1);
		return m;
	}

    // Instance method
	string attribute(const string& name) { return ""; };

    // Instance method
	void attributeIs(const string& name, const string& v) {};

protected:
    FleetRep(const string& name, ManagerImpl* manager) :
        Instance(name), manager_(manager)
    {
        // Nothing else to do.
    }
    Fwk::Ptr<ManagerImpl> manager_;
	Fleet::Ptr fleet_;
};

class ConnRep : public Instance {
public:
	typedef Fwk::Ptr<ConnRep const> PtrConst;
	typedef Fwk::Ptr<ConnRep> Ptr;

	static ConnRep::Ptr ConnRepNew( const string& _name, ManagerImpl* manager) {
		Ptr m = new ConnRep(_name, manager);
		m->referencesDec(1);
		return m;
	}

    // Instance method
	string attribute(const string& name) { return ""; };

    // Instance method
	void attributeIs(const string& name, const string& v) {};

protected:
    ConnRep(const string& name, ManagerImpl* manager) :
        Instance(name), manager_(manager)
    {
        // Nothing else to do.
    }
    Fwk::Ptr<ManagerImpl> manager_;
	Conn::Ptr conn_;
};

class StatsRep : public Instance {
public:
	typedef Fwk::Ptr<StatsRep const> PtrConst;
	typedef Fwk::Ptr<StatsRep> Ptr;

	static StatsRep::Ptr StatsRepNew( const string& _name, ManagerImpl* manager) {
		Ptr m = new StatsRep(_name, manager);
		m->referencesDec(1);
		return m;
	}

    // Instance method
	string attribute(const string& name) { return ""; };

    // Instance method
	void attributeIs(const string& name, const string& v) {};

protected:
    StatsRep(const string& name, ManagerImpl* manager) :
	  Instance(name), manager_(manager)
    {
		//stats_ = Stats::StatsNew(name, manager_->engine());
    }
    Fwk::Ptr<ManagerImpl> manager_;
	Stats::Ptr stats_;
};

ManagerImpl::ManagerImpl() {
}

Ptr<Instance> ManagerImpl::instanceNew(const string& name, const string& type) {
	// Return null if an instance for this name already exists
	
	if( instance_.find( name ) != instance_.end() )
	{
		return NULL;
	}
	
    if (type == "Truck terminal") {
        LocationRep::Ptr t = TruckTerminalRep::TruckTerminalRepNew(name, this);
        instance_[name] = t;
        return t;
    } else if (type == "Boat terminal") {
        LocationRep::Ptr t = BoatTerminalRep::BoatTerminalRepNew(name, this);
        instance_[name] = t;
        return t;
    } else if (type == "Plane terminal") {
        LocationRep::Ptr t = PlaneTerminalRep::PlaneTerminalRepNew(name, this);
        instance_[name] = t;
        return t;
    } else if (type == "Customer") {
        LocationRep::Ptr t = CustomerRep::CustomerRepNew(name, this);
        instance_[name] = t;
        return t;
    } else if (type == "Port") {
        LocationRep::Ptr t = PortRep::PortRepNew(name, this);
        instance_[name] = t;
        return t;
    } else if (type == "Truck segment") {
	   SegmentRep::Ptr t = TruckSegmentRep::TruckSegmentRepNew(name, this);
        instance_[name] = t;
        return t;
    } else if (type == "Boat segment") {
	   SegmentRep::Ptr t = BoatSegmentRep::BoatSegmentRepNew(name, this);
        instance_[name] = t;
        return t;
    } else if (type == "Plane segment") {
	   SegmentRep::Ptr t = PlaneSegmentRep::PlaneSegmentRepNew(name, this);
        instance_[name] = t;
        return t;
    } else if (type == "Stats") {
	   StatsRep::Ptr t = StatsRep::StatsRepNew(name, this);
        instance_[name] = t;
        return t;
    } else if (type == "Conn") {
	   ConnRep::Ptr t = ConnRep::ConnRepNew(name, this);
        instance_[name] = t;
        return t;
    } else if (type == "Fleet") {
	   FleetRep::Ptr t = FleetRep::FleetRepNew(name, this);
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
