#include <stdlib.h>
#include <limits.h>
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "Instance.h"
#include "Engine.h"
#include "ShippingException.h"
#include "fwk/ListRaw.h"
#include "fwk/NamedInterface.h"

namespace Shipping
{

using namespace std;
using std::string;

//
// Rep layer classes
//

class ManagerImpl : public Instance::Manager
{
public:
    ManagerImpl();

    // Manager method
    Ptr<Instance> instanceNew(const string& name, const string& type);

    // Manager method
    Ptr<Instance> instance(const string& name);

    // Manager method
    void instanceDel(const string& name);

    //void printTables();

    Engine::Ptr engine();

private:
    map<string,Ptr<Instance> > instance_;
    Engine::Ptr engine_;
};


class LocationRep : public Instance
{
public:
    typedef Fwk::Ptr<LocationRep const> PtrConst;
    typedef Fwk::Ptr<LocationRep> Ptr;

    // Instance method
    virtual string attribute(const string& name);

    // Instance method
    virtual void attributeIs(const string& name, const string& v);

protected:
    LocationRep(const string& name, ManagerImpl* manager) :
        Instance(name), manager_(manager) {
        // Nothing else to do.
    }
    Fwk::Ptr<ManagerImpl> manager_;
    Segment::SegmentId segmentNumber(const string& name);
    Location::Ptr location_;
};

class CustomerRep : public LocationRep
{
public:
    virtual string attribute(const string& name);
    virtual void attributeIs(const string& name, const string& v);

    static LocationRep::Ptr CustomerRepNew( const string& _name, ManagerImpl* manager) {
        Ptr m = new CustomerRep(_name, manager);
        m->referencesDec(1);
        return m;
    }
protected:
    CustomerRep(const string& name, ManagerImpl *manager) :
        LocationRep(name, manager) {
        try {
            location_ = Customer::CustomerNew(name, manager->engine());
        } catch (Fwk::NameInUseException ex) {
		    throw Shipping::NameExistsException("Location name" + name + " already exists!");
        }
    }
};

class PortRep : public LocationRep
{
public:
    static LocationRep::Ptr PortRepNew( const string& _name, ManagerImpl* manager) {
        Ptr m = new PortRep(_name, manager);
        m->referencesDec(1);
        return m;
    }
protected:
    PortRep(const string& name, ManagerImpl *manager) :
        LocationRep(name, manager) {
        try {
            location_ = Port::PortNew(name, manager->engine());
        } catch (Fwk::NameInUseException ex) {
		    throw Shipping::NameExistsException("Location name" + name + " already exists!");
        }
    }
};

class TruckTerminalRep : public LocationRep
{
public:
    static LocationRep::Ptr TruckTerminalRepNew( const string& _name, ManagerImpl* manager) {
        Ptr m = new TruckTerminalRep(_name, manager);
        m->referencesDec(1);
        return m;
    }
protected:
    TruckTerminalRep(const string& name, ManagerImpl *manager) :
        LocationRep(name, manager) {
        try {
            location_ = TruckLocation::TruckLocationNew(name, manager->engine());
        } catch (Fwk::NameInUseException ex) {
		    throw Shipping::NameExistsException("Location name" + name + " already exists!");
        }
    }
};

class BoatTerminalRep : public LocationRep
{
public:
    static LocationRep::Ptr BoatTerminalRepNew( const string& _name, ManagerImpl* manager) {
        Ptr m = new BoatTerminalRep(_name, manager);
        m->referencesDec(1);
        return m;
    }
protected:
    BoatTerminalRep(const string& name, ManagerImpl *manager) :
        LocationRep(name, manager) {
        try {
            location_ = BoatLocation::BoatLocationNew(name, manager->engine());
        } catch (Fwk::NameInUseException ex) {
		    throw Shipping::NameExistsException("Location name" + name + " already exists!");
        }
    }
};

class PlaneTerminalRep : public LocationRep
{
public:
    static LocationRep::Ptr PlaneTerminalRepNew( const string& _name, ManagerImpl* manager) {
        Ptr m = new PlaneTerminalRep(_name, manager);
        m->referencesDec(1);
        return m;
    }
protected:
    PlaneTerminalRep(const string& name, ManagerImpl *manager) :
        LocationRep(name, manager) {
        try {
            location_ = PlaneLocation::PlaneLocationNew(name, manager->engine());
        } catch (Fwk::NameInUseException ex) {
		    throw Shipping::NameExistsException("Location name" + name + " already exists!");
        }
    }
};

class SegmentRep : public Instance
{
public:
    typedef Fwk::Ptr<SegmentRep const> PtrConst;
    typedef Fwk::Ptr<SegmentRep> Ptr;

    // Instance method
    string attribute(const string& name);

    // Instance method
    void attributeIs(const string& name, const string& v);

protected:
    SegmentRep(const string& name, ManagerImpl* manager) :
        Instance(name), manager_(manager) {}
    Segment::Ptr segment_;
    Fwk::Ptr<ManagerImpl> manager_;
    string miles( Mile _length);
    string difficulty( Difficulty _difficulty );
    string expVal( Segment::ExpVal _expVal );
};

class TruckSegmentRep : public SegmentRep
{
public:
    static SegmentRep::Ptr TruckSegmentRepNew( const string& _name, ManagerImpl* manager) {
        Ptr m = new TruckSegmentRep(_name, manager);
        m->referencesDec(1);
        return m;
    }

protected:
    TruckSegmentRep(const string& name, ManagerImpl *manager) :
        SegmentRep(name, manager) {
        try {
            segment_ = TruckSegment::TruckSegmentNew(name, manager->engine());
        } catch (Fwk::NameInUseException ex) {
		    throw Shipping::NameExistsException("Location name" + name + " already exists!");
        }
    }
};

class BoatSegmentRep : public SegmentRep
{
public:
    static SegmentRep::Ptr BoatSegmentRepNew( const string& _name, ManagerImpl* manager) {
        Ptr m = new BoatSegmentRep(_name, manager);
        m->referencesDec(1);
        return m;
    }

private:
    BoatSegmentRep(const string& name, ManagerImpl *manager) :
        SegmentRep(name, manager) {
        try {
            segment_ = BoatSegment::BoatSegmentNew(name, manager->engine());
        } catch (Fwk::NameInUseException ex) {
		    throw Shipping::NameExistsException("Location name" + name + " already exists!");
        }
    }

};

class PlaneSegmentRep : public SegmentRep
{
public:
    static SegmentRep::Ptr PlaneSegmentRepNew( const string& _name, ManagerImpl* manager) {
        Ptr m = new PlaneSegmentRep(_name, manager);
        m->referencesDec(1);
        return m;
    }

protected:
    PlaneSegmentRep(const string& name, ManagerImpl *manager) :
        SegmentRep(name, manager) {
        try {
            segment_ = PlaneSegment::PlaneSegmentNew(name, manager->engine());
        } catch (Fwk::NameInUseException ex) {
		    throw Shipping::NameExistsException("Location name" + name + " already exists!");
        }
    }
};

class FleetRep : public Instance
{
public:
    typedef Fwk::Ptr<FleetRep const> PtrConst;
    typedef Fwk::Ptr<FleetRep> Ptr;

    static FleetRep::Ptr FleetRepNew( const string& _name, ManagerImpl* manager) {
        Ptr m = new FleetRep(_name, manager);
        m->referencesDec(1);
        return m;
    }

    // Instance method
    string attribute(const string& name) {
        istringstream iss(name);
        string sub;
        iss >> sub;
        Segment::Mode m;
        if (sub.find("Boat") != string::npos) {
            m = Segment::boat_;
        } else if (sub.find("Plane") != string::npos) {
            m = Segment::plane_;
        } else if (sub.find("Truck") != string::npos) {
            m = Segment::truck_;
        } else {
		    throw Shipping::UnknownAttrException("Unsupported attribute: " + name);
        }

        iss >> sub;
        if (sub == "speed") {
            return fleet_->speed(m);
        } else if (sub == "cost") {
            return fleet_->cost(m);
        } else if (sub == "capacity") {
            return fleet_->capacity(m);
        } else {
		    throw Shipping::UnknownAttrException("Unsupported attribute: " + name);
        }
        return "";
    };

    // Instance method
    void attributeIs(const string& name, const string& v) {
        stringstream ss(name);
        string sub;
        ss >> sub;
        Segment::Mode m;
        if (sub.find("Boat") != string::npos) {
            m = Segment::boat();
        } else if (sub.find("Plane") != string::npos) {
            m = Segment::plane();
        } else if (sub.find("Truck") != string::npos) {
            m = Segment::truck();
        } else {
		    throw Shipping::UnknownAttrException("Unsupported attribute: " + name);
        }

        try {
            ss >> sub;
            stringstream ss2(v);
            if (sub == "speed") {
                double val;
                ss2 >> val;
                fleet_->speedIs(m, val);
            } else if (sub == "cost") {
                double val;
                ss2 >> val;
                fleet_->costIs(m, val);
            } else if (sub == "capacity") {
                unsigned int val;
                ss2 >> val;
                fleet_->capacityIs(m, val);
            } else {
			    throw Shipping::UnknownAttrException("Unsupported attribute: " + name);
            }
        } catch (Fwk::RangeException ex) {
            cerr << "Error processing \"" << name << " = "
                 << v << "\": " << ex.what() << endl;
        }
    };

protected:
    FleetRep(const string& name, ManagerImpl* manager) :
        Instance(name), manager_(manager) {
        fleet_ = Fleet::FleetNew(name, manager_->engine());
        manager_->engine()->fleetIs( fleet_ );
    }
    Fwk::Ptr<ManagerImpl> manager_;
    Fleet::Ptr fleet_;
};

class ConnRep : public Instance
{
public:
    typedef Fwk::Ptr<ConnRep const> PtrConst;
    typedef Fwk::Ptr<ConnRep> Ptr;

    static ConnRep::Ptr ConnRepNew( const string& _name, ManagerImpl* manager) {
        Ptr m = new ConnRep(_name, manager);
        m->referencesDec(1);
        return m;
    }

    // Instance method
    string attribute(const string& name);

    // Instance method
    void attributeIs(const string& name, const string& v);

protected:
    ConnRep(const string& name, ManagerImpl* manager) :
        Instance(name), manager_(manager) {
        conn_ = Conn::ConnNew(name, manager_->engine());
    }
    Fwk::Ptr<ManagerImpl> manager_;
    Conn::Ptr conn_;
};

class StatsRep : public Instance
{
public:
    typedef Fwk::Ptr<StatsRep const> PtrConst;
    typedef Fwk::Ptr<StatsRep> Ptr;

    static StatsRep::Ptr StatsRepNew( const string& _name, ManagerImpl* manager) {
        Ptr m = new StatsRep(_name, manager);
        m->referencesDec(1);
        return m;
    }

    // Instance method
    string attribute(const string& name) {
        U32 val;
        if (name == "Customer") {
            val = stats_->customer();
        } else if (name == "Port") {
            val = stats_->port();
        } else if (name == "Plane terminal") {
            val = stats_->planeTerminal();
        } else if (name == "Boat terminal") {
            val = stats_->boatTerminal();
        } else if (name == "Truck terminal") {
            val = stats_->truckTerminal();
        } else if (name == "Truck segment") {
            val = stats_->truckSegment();
        } else if (name == "Boat segment") {
            val = stats_->boatSegment();
        } else if (name == "Plane segment") {
            val = stats_->planeSegment();
        } else if (name == "expedite percentage") {
            return stats_->expedite();
        } else {
		    throw Shipping::UnknownAttrException("Unsupported attribute: " + name);
        }

        stringstream ss;
        ss << val;
        return ss.str();
    };

    // Instance method
    void attributeIs(const string& name, const string& v) {};

protected:
    StatsRep(const string& name, ManagerImpl* manager) :
        Instance(name), manager_(manager) {
        stats_ = Stats::StatsNew(name, manager_->engine());
    }
    Fwk::Ptr<ManagerImpl> manager_;
    Stats::Ptr stats_;
};

ManagerImpl::ManagerImpl()
{
    engine_ = Engine::EngineNew();
}

Ptr<Instance> ManagerImpl::instanceNew(const string& name, const string& type)
{
    // Return null if an instance for this name already exists

    if( instance_.find( name ) != instance_.end() ) {
        cerr << "Error: name in use: " << name << endl;
        return NULL;
    }

    static StatsRep::Ptr stats;
    static ConnRep::Ptr conn;
    static FleetRep::Ptr fleet;

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
        if (stats != NULL ) return stats;
        StatsRep::Ptr t = StatsRep::StatsRepNew(name, this);

        stats = t;
        instance_[name] = t;
        return t;
    } else if (type == "Conn") {
        if (conn != NULL ) return conn;
        ConnRep::Ptr t = ConnRep::ConnRepNew(name, this);

        conn = t;
        instance_[name] = t;
        return t;
    } else if (type == "Fleet") {
        if (fleet != NULL ) return fleet;
        FleetRep::Ptr t = FleetRep::FleetRepNew(name, this);

        fleet = t;
        instance_[name] = t;
        return t;
    } else {
        throw UnknownTypeException("Error: unsupported Shipping object: " + type);
    }

    return NULL;
}

Ptr<Instance> ManagerImpl::instance(const string& name)
{
    map<string,Ptr<Instance> >::const_iterator t = instance_.find(name);

    if( t == instance_.end() ) return NULL;
    else return (*t).second;
    //return t == instance_.end() ? NULL : (*t).second;
}

void ManagerImpl::instanceDel(const string& name)
{
    try {
        map<string,Ptr<Instance> >::const_iterator t = instance_.find(name);

        if( t != instance_.end() ) {
            if (dynamic_cast<SegmentRep*>(t->second.ptr()))
                engine_->segmentDel(name);
            else if (dynamic_cast<LocationRep*>(t->second.ptr()))
                engine_->locationDel(name);

            instance_.erase(name);
        }
    } catch (...) {}
}

/*
void ManagerImpl::printTables()
{
	for( Engine::LocationIterator iter = engine_->locationIter(); iter.ptr(); ++iter )
	{
		cout << (*iter)->name() << "'s routing table:" << endl;
		for( Engine::LocationIterator i = engine_->locationIter(); i.ptr(); ++i )
		{
			if( (*i)->name() != (*iter)->name() )
			{
				Segment::Ptr nextSeg = (*iter)->nextSegment( (*i)->name() );
				if( nextSeg != NULL )
				{
					cout << (*i)->name() << ": " << nextSeg->name() << endl;
				}
			}
		}
		cout  << endl;
	}
}
*/

string LocationRep::attribute(const string& name)
{
    int i = segmentNumber(name);
    if (i != 0) {
        try {
            Segment::PtrConst p = location_->segment(i);
            if (p != NULL )
                return p->name();
            else
                throw RangeException("Error: Location has no segment # " + name);
        } catch (...) {
            throw RangeException("Error: Location has no segment # " + name);
        }
        return "";
    } else {
        throw RangeException("Error: Location has no segment # " + name);
    }
}


void LocationRep::attributeIs(const string& name, const string& v)
{
    //nothing to do
}


string CustomerRep::attribute(const string& name)
{
    if (name == "Transfer Rate") {
		Shipping::Customer* c = dynamic_cast<Shipping::Customer*>(this->location_.ptr());
		if (c != NULL)
			return string(c->transferRate());
	} else if (name == "Shipment Size") {
		Shipping::Customer* c = dynamic_cast<Shipping::Customer*>(this->location_.ptr());
		if (c != NULL)
			return string(c->shipmentSize());
	} else if (name == "Destination") {
		Shipping::Customer* c = dynamic_cast<Shipping::Customer*>(this->location_.ptr());
		if (c != NULL)
			return c->destination();
	} else {
		return LocationRep::attribute(name);
	}

	return "";
}


void CustomerRep::attributeIs(const string& name, const string& v)
{
    if (name == "Transfer Rate") {
		Shipping::Customer* c = dynamic_cast<Shipping::Customer*>(this->location_.ptr());
		if (c != NULL) {
			istringstream iss(v);
			ShipmentsPerDay spd(0);
			iss >> spd;
			c->transferRateIs(spd);
		}
	} else if (name == "Shipment Size") {
		Shipping::Customer* c = dynamic_cast<Shipping::Customer*>(this->location_.ptr());
		if (c != NULL) {
			istringstream iss(v);
			NumPackages np(0);
			iss >> np;
			c->shipmentSizeIs(np);
		}
	} else if (name == "Destination") {
		Shipping::Customer* c = dynamic_cast<Shipping::Customer*>(this->location_.ptr());
		if (c != NULL)
			c->destinationIs(v);
	} else {
		LocationRep::attributeIs(name, v);
	}
}

static const string segmentStr = "segment";
static const int segmentStrlen = segmentStr.length();

Segment::SegmentId LocationRep::segmentNumber(const string& name)
{
    if (name.substr(0, segmentStrlen) == segmentStr) {
        const char* t = name.c_str() + segmentStrlen;
        return Segment::SegmentIdInstance( atoi(t) );
    }
    return 0;
}

string SegmentRep::attribute(const string& name)
{
    if( name == "source" ) {
        Location::Ptr src = segment_->source();
        if( src  != NULL ) {
            return src->name();
        }
    } else if( name == "length" ) {
        return miles( segment_->length() );
    } else if( name == "return segment" ) {

        Segment::PtrConst _returnSeg = segment_->returnSegment();
        if( _returnSeg  != NULL ) {
            return _returnSeg->name();
        }

    } else if( name == "difficulty" ) {
        return difficulty( segment_->difficulty() );
    } else if( name == "expedite support" ) {
        return expVal( segment_->expedite() );
    } else {
        throw UnknownAttrException("Unknown segment attribute: " + name);
    }
    return "";
}

void SegmentRep::attributeIs(const string& name, const string& v)
{
    if( name == "source" ) {
        Location::Ptr l = manager_->engine()->location( v );
        segment_->sourceIs(l);
    } else if( name == "length" ) {
        Mile m( atoi( v.c_str() ) );
        segment_->lengthIs( m );
    } else if( name == "return segment" ) {
        segment_->returnSegmentIs( manager_->engine()->segment( v ) );
    } else if( name == "difficulty" ) {
        Difficulty d( atoi( v.c_str() ) );
        segment_->difficultyIs( d );
    } else if( name == "expedite support" ) {
        segment_->expediteIs( Segment::ExpValInstance( v ) );
    } else {
        throw UnknownAttrException("Unknown segment attribute: " + name);
    }
}

string SegmentRep::miles( Mile _length )
{
    stringstream oss;
    oss << _length.value();
    return oss.str();
}

string SegmentRep::difficulty( Difficulty _difficulty )
{
    stringstream oss;
    oss << _difficulty.value();
    return oss.str();
}

string SegmentRep::expVal( Segment::ExpVal _expVal )
{
    stringstream oss;
    oss << _expVal;
    return oss.str();
}

string ConnRep::attribute(const string& name )
{
    char* q = new char[name.length()+1];
    strcpy(q, name.c_str());
    char* tok = strtok( q, " ");

    // default attributes values
    conn_->distanceIs( Mile::max() );
    conn_->costIs( Dollar::max() );
    conn_->timeIs( Hour::max() );
    conn_->expeditedIs( Segment::expNo() );
    conn_->startLocationIs( "" );
    conn_->endLocationIs( "" );

    if( tok && Conn::exploreString().compare(tok) == 0 ) {
        conn_->queryTypeIs( Conn::explore() );
        if( !(tok = strtok(NULL, " :") ) ) return "";

        // enforce Customer start location
        if( manager_->engine()->location(tok) == NULL || manager_->engine()->location(tok)->type() != Location::customer() ) {
            return "";
        }

        conn_->startLocationIs( tok );
        vector<string> used;

        while( ( tok = strtok(NULL, " :") ) ) {
            if( Conn::distanceString().compare(tok) == 0 ) {
                for( vector<string>::iterator i = used.begin(); i != used.end(); ++i ) {
                    if( Conn::distanceString().compare(*i) == 0 ) return "";
                }
                used.push_back( Conn::distanceString() );

                if( !(tok = strtok(NULL, " ") ) ) return "";

                Mile m( atoi(tok) );
                conn_->distanceIs( m );

            } else if( Conn::costString().compare(tok) == 0 ) {
                for( vector<string>::iterator i = used.begin(); i != used.end(); ++i ) {
                    if( Conn::costString().compare(*i) == 0 ) return "";
                }
                used.push_back( Conn::costString() );

                if( !(tok = strtok(NULL, " ") ) ) return "";
                double num;
                istringstream s(tok);
                s >> num;

                Dollar d( num );
                conn_->costIs( d );
            } else if( Conn::timeString().compare(tok) == 0 ) {
                for( vector<string>::iterator i = used.begin(); i != used.end(); ++i ) {
                    if( Conn::timeString().compare(*i) == 0 ) return "";
                }
                used.push_back( Conn::timeString() );

                if( !(tok = strtok(NULL, " ") ) ) return "";
                double num;
                istringstream s(tok);
                s >> num;

                Hour t( num );
                conn_->timeIs( t );
            } else if( Conn::expeditedString().compare(tok) == 0 ) {
                for( vector<string>::iterator i = used.begin(); i != used.end(); ++i ) {
                    if( Conn::expeditedString().compare(*i) == 0 ) return "";
                }
                used.push_back( Conn::expeditedString() );
                conn_->expeditedIs( Segment::expYes() );
            } else return "";
        }
    }

    else if( tok && Conn::connectString().compare(tok) == 0 ) {
        conn_->queryTypeIs( Conn::connect() );
        if( !(tok = strtok(NULL, " :") ) ) return "";

        // enforce Customer start location
        if( manager_->engine()->location(tok) == NULL || manager_->engine()->location(tok)->type() != Location::customer() ) {
            return "";
        }

        conn_->startLocationIs( tok );
        if( !(tok = strtok(NULL, " :") ) ) return "";

        // enforce Customer end location
        if( manager_->engine()->location(tok) == NULL || manager_->engine()->location(tok)->type() != Location::customer() ) {
            return "";
        }
        conn_->endLocationIs( tok );
    }
    return conn_->value();
}

void ConnRep::attributeIs(const string& name, const string& v)
{
	if(name == "routing algorithm")
	{
		if( v == "Dijkstra" )
		{
			conn_->algorithmIs( Conn::dijkstra() );
		}
		else if( v == "BFS" )
		{
			conn_->algorithmIs( Conn::bfs() );
		}
	} else if (name == "simulation started") { // temporary
		conn_->simulationStartedIs(true);
	} else {
        throw UnknownAttrException("Unknown Conn attribute: " + name);
	}
}

}

/*
 * This is the entry point for your library.
 * The client program will call this function to get a handle
 * on the Instance::Manager object, and from there will use
 * that object to interact with the middle layer (which will
 * in turn interact with the engine layer).
 */
Ptr<Instance::Manager> shippingInstanceManager()
{
    return new Shipping::ManagerImpl();
}

Shipping::Engine::Ptr Shipping::ManagerImpl::engine()
{
    return engine_;
}
