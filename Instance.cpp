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

class Segment : public Fwk::NamedInterface {
public:
	typedef Fwk::Ptr<Segment const> PtrConst;
	typedef Fwk::Ptr<Segment> Ptr;
	typedef int SegmentId;
	enum Mode {
		truck_ = 0,
		boat_ = 1,
		plane_ = 2,
	};
	static inline Mode truck() { return truck_; }
	static inline Mode boat() { return boat_; }
	static inline Mode plane() { return plane_; }
	static SegmentId SegmentIdInstance ( int v );
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

};
                                                                                                  
class CustomerRep : public LocationRep {
public:

    CustomerRep(const string& name, ManagerImpl *manager) :
        LocationRep(name, manager)
    {
        // Nothing else to do.
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
    string attribute(const string& name);

    // Instance method
    void attributeIs(const string& name, const string& v);

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
    string attribute(const string& name);

    // Instance method
    void attributeIs(const string& name, const string& v);

private:
    Ptr<ManagerImpl> manager_;

};

class ConnRep : public Instance {
public:

    ConnRep(const string& name, ManagerImpl* manager) :
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

};

class StatsRep : public Instance {
public:

    StatsRep(const string& name, ManagerImpl* manager) :
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

};

ManagerImpl::ManagerImpl() {
}

Ptr<Instance> ManagerImpl::instanceNew(const string& name, const string& type) {
    if (type == "Truck terminal") {
        Ptr<TruckTerminalRep> t = new TruckTerminalRep(name, this);
        instance_[name] = t;
        return t;
    }

    return NULL;
}

Ptr<Instance> ManagerImpl::instance(const string& name) {
    map<string,Ptr<Instance> >::const_iterator t = instance_.find(name);

    return t == instance_.end() ? NULL : (*t).second;
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

Segment::SegmentId Segment::SegmentIdInstance ( int v ) {
	// TODO: implement
	return 0;
}

class Location : public Fwk::NamedInterface {
public:
	typedef Fwk::Ptr<Location const> PtrConst;
	typedef Fwk::Ptr<Location> Ptr;
	enum Type {
		customer_ = 0,
		port_ = 1,
		truck_ = 2,
		boat_ = 3,
		plane_ = 4,
	};
	static inline Type customer() { return customer_; }
	static inline Type port() { return port_; }
	static inline Type truck() { return truck_; }
	static inline Type boat() { return boat_; }
	static inline Type plane() { return plane_; }

	static Type TypeInstance( Fwk::String );
	Type type() { return type_; };

	Segment::Ptr segment( Segment::SegmentId _segmentId );
	void segmentIs(); // does nothing

	class NotifieeConst : public virtual Fwk::NamedInterface::NotifieeConst {
	public:
		typedef Fwk::Ptr<NotifieeConst const> PtrConst;
		typedef Fwk::Ptr<NotifieeConst> Ptr;
		string name() const { return notifier_->name(); }
		Location::PtrConst notifier() const { return notifier_; }
		NotifieeConst const * lrNext() const { return lrNext_; }
		NotifieeConst * lrNext() { return lrNext_; }
		void lrNextIs(NotifieeConst * _lrNext) {
			lrNext_ = _lrNext;
		}
	
		~NotifieeConst();
		virtual void notifierIs(const Location::PtrConst& _notifier);
		virtual void onSegmentNew( Segment::Ptr _segment ) {}
		virtual void onSegmentDel( Segment::Ptr _segment ) {}
		static NotifieeConst::Ptr NotifieeConstIs() {
			Ptr m = new NotifieeConst();
			m->referencesDec(1);
			return m;
		}
	protected:
		Location::PtrConst notifier_;

		NotifieeConst* lrNext_;
		NotifieeConst(): Fwk::NamedInterface::NotifieeConst(),
			lrNext_(0) { }
	};

	class Notifiee : public virtual NotifieeConst, public virtual Fwk::NamedInterface::Notifiee {
	public:
		typedef Fwk::Ptr<Notifiee const> PtrConst;
		typedef Fwk::Ptr<Notifiee> Ptr;
		Location::PtrConst notifier() const { return NotifieeConst::notifier(); }
		Location::Ptr notifier() { return const_cast<Location *>(NotifieeConst::notifier().ptr()); }

		static Notifiee::Ptr NotifieeIs() {
			Ptr m = new Notifiee();
			m->referencesDec(1);
			return m;
		}
	protected:
		Notifiee(): Fwk::NamedInterface::Notifiee() { }
	};

	typedef Fwk::ListRaw<NotifieeConst> NotifieeList;
	typedef NotifieeList::IteratorConst NotifieeIteratorConst;
	NotifieeIteratorConst notifieeIterConst() const { return notifiee_.iterator(); }
	U32 notifiees() const { return notifiee_.members(); }
	~Location();
	
	static Location::Ptr LocationIs( const string& _name, Type _type, Engine* _engine ) {
		Ptr m = new Location( _name, _type, _engine );
		m->referencesDec(1);
		return m;
	}

protected:
	Location( const Location& );
	Location( const string& _name, Type _type, Engine* _engine );
	Type type_;
	vector< Segment::Ptr > segment_;
	NotifieeList notifiee_;
};


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