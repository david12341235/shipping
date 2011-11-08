#ifndef ENGINE_H
#define ENGINE_H

#include <string>
#include <vector>
#include <map>

#include "fwk/Ptr.h"
#include "fwk/PtrInterface.h"
#include "fwk/NamedInterface.h"
#include "fwk/ListRaw.h"
#include "fwk/LinkedList.h"
#include "fwk/LinkedQueue.h"
#include "fwk/HashMap.h"
#include "Instance.h"
#include "Nominal.h"
#include "ShippingTypes.h"
#include "Segment.h"

namespace Shipping {
using namespace std;

class Engine;
class Location;

class Location : public Fwk::NamedInterface {
public:
	typedef Fwk::Ptr<Location const> PtrConst;
	typedef Fwk::Ptr<Location> Ptr;
    Fwk::String fwkKey() const { return this->name(); }
	Location const * fwkHmNext() const { return fwkHmNext_.ptr(); }
	Location * fwkHmNext() { return fwkHmNext_.ptr(); }
	Location const * fwkPtr() const { return this; }
	Location * fwkPtr() { return this; }
	void fwkHmNextIs(Location * _fwkHmNext) const {
		fwkHmNext_ = _fwkHmNext;
	}
	Location::PtrConst fwkValue() const { return this; }
	Location::Ptr fwkValue() { return this; }

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
	Type type() const { return type_; }
	virtual void typeIs( Type _type ) { type_ = _type; }
	Segment::PtrConst segment( Segment::SegmentId _segmentId ) const {
		return segment_.at(_segmentId);
	};
	virtual void segmentIs( Segment::PtrConst  _segment ) {
		segment_.push_back(_segment);
	};
	void segmentDel( Segment::PtrConst _segment );

	class NotifieeConst : public virtual Fwk::NamedInterface::NotifieeConst {
	public:
		typedef Fwk::Ptr<NotifieeConst const> PtrConst;
		typedef Fwk::Ptr<NotifieeConst> Ptr;
		string name() const { return notifier_->name(); }
		Location::PtrConst notifier() const { return notifier_; }
        static const AttributeId location__ = AttributeId(Fwk::NamedInterface::NotifieeConst::tacNextAttributeId__);
        static const AttributeId tacNextAttributeId__ = AttributeId(location__+1);
	    bool isNonReferencing() const { return isNonReferencing_; }
		NotifieeConst const * lrNext() const { return lrNext_; }
		NotifieeConst * lrNext() { return lrNext_; }
	
		~NotifieeConst();
		virtual void notifierIs(const Location::PtrConst& _notifier);
		void isNonReferencingIs(bool _isNonReferencing);
		void lrNextIs(NotifieeConst * _lrNext) {
			lrNext_ = _lrNext;
		}
		static NotifieeConst::Ptr NotifieeConstIs() {
			Ptr m = new NotifieeConst();
			m->referencesDec(1);
			return m;
		}
	protected:
		Location::PtrConst notifier_;
		bool isNonReferencing_;
		NotifieeConst * lrNext_;
		NotifieeConst(): Fwk::NamedInterface::NotifieeConst(),
			isNonReferencing_(false),
			lrNext_(0) {}
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
	~Location() {};
	
	static Location::Ptr LocationNew( const string& _name, Type _type, Fwk::Ptr<Engine> _engine ) {
		Ptr m = new Location( _name, _type, _engine );
		m->referencesDec(1);
		return m;
	}
    typedef NotifieeList::Iterator NotifieeIterator;
	NotifieeIterator notifieeIter() { return notifiee_.iterator(); }

protected:
	typedef vector<Segment::PtrConst > SegmentList;
    mutable Location::Ptr fwkHmNext_;
	Location( const Location& );
	Location( const string& _name, Type _type, Fwk::Ptr<Engine> _engine );
   void newNotifiee( Location::NotifieeConst * n ) const {
      Location* me = const_cast<Location*>(this);
      me->notifiee_.newMember(n);
   }
   void deleteNotifiee( Location::NotifieeConst * n ) const {
      Location* me = const_cast<Location*>(this);
      me->notifiee_.deleteMember(n);
   }
	Type type_;
	Fwk::Ptr<Engine> engine_;
	SegmentList segment_;
	NotifieeList notifiee_;
    void onZeroReferences();
};

class Customer : public Location {
public:
	typedef Fwk::Ptr<Customer const> PtrConst;
	typedef Fwk::Ptr<Customer> Ptr;

	Type type() const { return Location::truck(); }
	virtual void typeIs( Type v ) {}
//	virtual void segmentIs( Segment const* _segment );

	class NotifieeConst : public virtual Location::NotifieeConst {
	public:
		typedef Fwk::Ptr<NotifieeConst const> PtrConst;
		typedef Fwk::Ptr<NotifieeConst> Ptr;
		string name() const { return notifier_->name(); }
		Customer::PtrConst notifier() const { return dynamic_cast<Customer const *>(Location::NotifieeConst::notifier().ptr()); }
		NotifieeConst const * lrNext() const { return lrNext_; }
		NotifieeConst * lrNext() { return lrNext_; }
		void lrNextIs(NotifieeConst * _lrNext) {
			lrNext_ = _lrNext;
		}
	
		static NotifieeConst::Ptr NotifieeConstIs() {
			Ptr m = new NotifieeConst();
			m->referencesDec(1);
			return m;
		}
	protected:
		Customer::PtrConst notifier_;

		NotifieeConst* lrNext_;
		NotifieeConst(): Location::NotifieeConst(),
			lrNext_(0) { }
	};

	class Notifiee : public virtual NotifieeConst, public virtual Location::Notifiee {
	public:
		typedef Fwk::Ptr<Notifiee const> PtrConst;
		typedef Fwk::Ptr<Notifiee> Ptr;
		Customer::PtrConst notifier() const { return dynamic_cast<Customer const *>(Location::NotifieeConst::notifier().ptr()); }
		Customer::Ptr notifier() { return dynamic_cast<Customer * >(const_cast<Location *>(Location::NotifieeConst::notifier().ptr())); }

		static Notifiee::Ptr NotifieeIs() {
			Ptr m = new Notifiee();
			m->referencesDec(1);
			return m;
		}
	protected:
		Notifiee(): Location::Notifiee() { }
	};

	
	static Customer::Ptr CustomerNew( const string& _name, Fwk::Ptr<Engine> _engine ) {
		Ptr m = new Customer( _name, _engine );
		m->referencesDec(1);
		return m;
	}

protected:
	Customer( const Customer& );
	Customer( const string& _name, Fwk::Ptr<Engine> _engine ) : Location( _name, customer_, _engine ) {};
};

class Port : public Location {
public:
	typedef Fwk::Ptr<Port const> PtrConst;
	typedef Fwk::Ptr<Port> Ptr;

	Type type() const { return Location::truck(); }
	virtual void typeIs( Type v ) {}
//	virtual void segmentIs( Segment const* _segment );

	class NotifieeConst : public virtual Location::NotifieeConst {
	public:
		typedef Fwk::Ptr<NotifieeConst const> PtrConst;
		typedef Fwk::Ptr<NotifieeConst> Ptr;
		string name() const { return notifier_->name(); }
		Port::PtrConst notifier() const { return dynamic_cast<Port const *>(Location::NotifieeConst::notifier().ptr()); }
		NotifieeConst const * lrNext() const { return lrNext_; }
		NotifieeConst * lrNext() { return lrNext_; }
		void lrNextIs(NotifieeConst * _lrNext) {
			lrNext_ = _lrNext;
		}
	
		static NotifieeConst::Ptr NotifieeConstIs() {
			Ptr m = new NotifieeConst();
			m->referencesDec(1);
			return m;
		}
	protected:
		Port::PtrConst notifier_;

		NotifieeConst* lrNext_;
		NotifieeConst(): Location::NotifieeConst(),
			lrNext_(0) { }
	};

	class Notifiee : public virtual NotifieeConst, public virtual Location::Notifiee {
	public:
		typedef Fwk::Ptr<Notifiee const> PtrConst;
		typedef Fwk::Ptr<Notifiee> Ptr;
		Port::PtrConst notifier() const { return dynamic_cast<Port const *>(Location::NotifieeConst::notifier().ptr()); }
		Port::Ptr notifier() { return dynamic_cast<Port * >(const_cast<Location *>(Location::NotifieeConst::notifier().ptr())); }

		static Notifiee::Ptr NotifieeIs() {
			Ptr m = new Notifiee();
			m->referencesDec(1);
			return m;
		}
	protected:
		Notifiee(): Location::Notifiee() { }
	};

	static Port::Ptr PortNew( const string& _name, Fwk::Ptr<Engine> _engine ) {
		Ptr m = new Port( _name, _engine );
		m->referencesDec(1);
		return m;
	}

protected:
	Port( const Port& );
	Port( const string& _name, Fwk::Ptr<Engine> _engine ) : Location( _name, port_, _engine ) {};
};

class TruckLocation : public Location {
public:
	typedef Fwk::Ptr<TruckLocation const> PtrConst;
	typedef Fwk::Ptr<TruckLocation> Ptr;

	Type type() const { return Location::truck(); }
	virtual void typeIs( Type v ) {}
//	virtual void segmentIs( Segment const* _segment );

	class NotifieeConst : public virtual Location::NotifieeConst {
	public:
		typedef Fwk::Ptr<NotifieeConst const> PtrConst;
		typedef Fwk::Ptr<NotifieeConst> Ptr;
		string name() const { return notifier_->name(); }
		TruckLocation::PtrConst notifier() const { return dynamic_cast<TruckLocation const *>(Location::NotifieeConst::notifier().ptr()); }
		NotifieeConst const * lrNext() const { return lrNext_; }
		NotifieeConst * lrNext() { return lrNext_; }
		void lrNextIs(NotifieeConst * _lrNext) {
			lrNext_ = _lrNext;
		}
	
		static NotifieeConst::Ptr NotifieeConstIs() {
			Ptr m = new NotifieeConst();
			m->referencesDec(1);
			return m;
		}
	protected:
		TruckLocation::PtrConst notifier_;

		NotifieeConst* lrNext_;
		NotifieeConst(): Location::NotifieeConst(),
			lrNext_(0) { }
	};

	class Notifiee : public virtual NotifieeConst, public virtual Location::Notifiee {
	public:
		typedef Fwk::Ptr<Notifiee const> PtrConst;
		typedef Fwk::Ptr<Notifiee> Ptr;
		TruckLocation::PtrConst notifier() const { return dynamic_cast<TruckLocation const *>(Location::NotifieeConst::notifier().ptr()); }
		TruckLocation::Ptr notifier() { return dynamic_cast<TruckLocation * >(const_cast<Location *>(Location::NotifieeConst::notifier().ptr())); }

		static Notifiee::Ptr NotifieeIs() {
			Ptr m = new Notifiee();
			m->referencesDec(1);
			return m;
		}
	protected:
		Notifiee(): Location::Notifiee() { }
	};

	static TruckLocation::Ptr TruckLocationNew( const string& _name, Fwk::Ptr<Engine> _engine ) {
		Ptr m = new TruckLocation( _name, _engine );
		m->referencesDec(1);
		return m;
	}

protected:
	TruckLocation( const TruckLocation& );
	TruckLocation( const string& _name, Fwk::Ptr<Engine> _engine ) : Location( _name, truck_, _engine ) {};
};

class BoatLocation : public Location {
public:
	typedef Fwk::Ptr<BoatLocation const> PtrConst;
	typedef Fwk::Ptr<BoatLocation> Ptr;

	Type type() const { return Location::truck(); }
	virtual void typeIs( Type v ) {}
//	virtual void segmentIs( Segment const* _segment );

	class NotifieeConst : public virtual Location::NotifieeConst {
	public:
		typedef Fwk::Ptr<NotifieeConst const> PtrConst;
		typedef Fwk::Ptr<NotifieeConst> Ptr;
		string name() const { return notifier_->name(); }
		BoatLocation::PtrConst notifier() const { return dynamic_cast<BoatLocation const *>(Location::NotifieeConst::notifier().ptr()); }
		NotifieeConst const * lrNext() const { return lrNext_; }
		NotifieeConst * lrNext() { return lrNext_; }
		void lrNextIs(NotifieeConst * _lrNext) {
			lrNext_ = _lrNext;
		}
	
		static NotifieeConst::Ptr NotifieeConstIs() {
			Ptr m = new NotifieeConst();
			m->referencesDec(1);
			return m;
		}
	protected:
		BoatLocation::PtrConst notifier_;

		NotifieeConst* lrNext_;
		NotifieeConst(): Location::NotifieeConst(),
			lrNext_(0) { }
	};

	class Notifiee : public virtual NotifieeConst, public virtual Location::Notifiee {
	public:
		typedef Fwk::Ptr<Notifiee const> PtrConst;
		typedef Fwk::Ptr<Notifiee> Ptr;
		BoatLocation::PtrConst notifier() const { return dynamic_cast<BoatLocation const *>(Location::NotifieeConst::notifier().ptr()); }
		BoatLocation::Ptr notifier() { return dynamic_cast<BoatLocation * >(const_cast<Location *>(Location::NotifieeConst::notifier().ptr())); }

		static Notifiee::Ptr NotifieeIs() {
			Ptr m = new Notifiee();
			m->referencesDec(1);
			return m;
		}
	protected:
		Notifiee(): Location::Notifiee() { }
	};

	static BoatLocation::Ptr BoatLocationNew( const string& _name, Fwk::Ptr<Engine> _engine ) {
		Ptr m = new BoatLocation( _name, _engine );
		m->referencesDec(1);
		return m;
	}

protected:
	BoatLocation( const BoatLocation& );
	BoatLocation( const string& _name, Fwk::Ptr<Engine> _engine ) : Location( _name, boat_, _engine ) {};
};

class PlaneLocation : public Location {
public:
	typedef Fwk::Ptr<PlaneLocation const> PtrConst;
	typedef Fwk::Ptr<PlaneLocation> Ptr;

	Type type() const { return Location::truck(); }
	virtual void typeIs( Type v ) {}
//	virtual void segmentIs( Segment const* _segment );

	class NotifieeConst : public virtual Location::NotifieeConst {
	public:
		typedef Fwk::Ptr<NotifieeConst const> PtrConst;
		typedef Fwk::Ptr<NotifieeConst> Ptr;
		string name() const { return notifier_->name(); }
		PlaneLocation::PtrConst notifier() const { return dynamic_cast<PlaneLocation const *>(Location::NotifieeConst::notifier().ptr()); }
		NotifieeConst const * lrNext() const { return lrNext_; }
		NotifieeConst * lrNext() { return lrNext_; }
		void lrNextIs(NotifieeConst * _lrNext) {
			lrNext_ = _lrNext;
		}
	
		static NotifieeConst::Ptr NotifieeConstIs() {
			Ptr m = new NotifieeConst();
			m->referencesDec(1);
			return m;
		}
	protected:
		PlaneLocation::PtrConst notifier_;

		NotifieeConst* lrNext_;
		NotifieeConst(): Fwk::NamedInterface::NotifieeConst(),
			lrNext_(0) { }
	};

	class Notifiee : public virtual NotifieeConst, public virtual Location::Notifiee {
	public:
		typedef Fwk::Ptr<Notifiee const> PtrConst;
		typedef Fwk::Ptr<Notifiee> Ptr;
		PlaneLocation::PtrConst notifier() const { return dynamic_cast<PlaneLocation const *>(Location::NotifieeConst::notifier().ptr()); }
		PlaneLocation::Ptr notifier() { return dynamic_cast<PlaneLocation * >(const_cast<Location *>(Location::NotifieeConst::notifier().ptr())); }

		static Notifiee::Ptr NotifieeIs() {
			Ptr m = new Notifiee();
			m->referencesDec(1);
			return m;
		}
	protected:
		Notifiee(): Fwk::NamedInterface::Notifiee() { }
	};

	static PlaneLocation::Ptr PlaneLocationNew( const string& _name, Fwk::Ptr<Engine> _engine ) {
		Ptr m = new PlaneLocation( _name, _engine );
		m->referencesDec(1);
		return m;
	}

protected:
	PlaneLocation( const PlaneLocation& );
	PlaneLocation( const string& _name, Fwk::Ptr<Engine> _engine ) : Location( _name, plane_, _engine ) {};
};

class Fleet : public Fwk::NamedInterface {
public:
	typedef Fwk::Ptr<Fleet const> PtrConst;
	typedef Fwk::Ptr<Fleet> Ptr;

	enum Mode {
		truck_ = 0,
		boat_ = 1,
		plane_ = 2,
	};

	struct fleetInfo
	{
		Mph speed_;
		NumPackages capacity_;
		Dollar cost_;

		public:
			fleetInfo() : speed_(0.0), capacity_(0), cost_(0.0) {}
	};

	static inline Mode truck() { return truck_; }
	static inline Mode boat() { return boat_; }
	static inline Mode plane() { return plane_; }

	static Mode TypeInstance( Fwk::String );

	Mph speed( Mode m ) const { return fleet_.at(m).speed_; };
	void speedIs( Mode m, Mph _speed ) { fleet_[m].speed_ = _speed; }

	NumPackages capacity( Mode m ) const { return fleet_.at(m).capacity_; };
	void capacityIs( Mode m, NumPackages _capacity ) { fleet_[m].capacity_ = _capacity; }

	Dollar cost( Mode m ) const { return fleet_.at(m).cost_; };
	void costIs( Mode m, Dollar _cost ) { fleet_[m].cost_ = _cost; }
	
	Fwk::Ptr<Engine> engine() const { return engine_; };
	void engineIs(Fwk::Ptr<Engine> e) { engine_ = e; };

	class NotifieeConst : public virtual Fwk::NamedInterface::NotifieeConst {
	public:
		typedef Fwk::Ptr<NotifieeConst const> PtrConst;
		typedef Fwk::Ptr<NotifieeConst> Ptr;
		string name() const { return notifier_->name(); }
		Fleet::PtrConst notifier() const { return notifier_; }
		NotifieeConst const * lrNext() const { return lrNext_; }
		NotifieeConst * lrNext() { return lrNext_; }
		void lrNextIs(NotifieeConst * _lrNext) {
			lrNext_ = _lrNext;
		}
	
		~NotifieeConst();
		virtual void notifierIs(const Fleet::PtrConst& _notifier);
		virtual void onSpeed( Mode _mode ) {}
		virtual void onCapacity( Mode _mode ) {}
		virtual void onCost( Mode _mode ) {}

		static NotifieeConst::Ptr NotifieeConstIs() {
			Ptr m = new NotifieeConst();
			m->referencesDec(1);
			return m;
		}
	protected:
		Fleet::PtrConst notifier_;

		NotifieeConst* lrNext_;
		NotifieeConst(): Fwk::NamedInterface::NotifieeConst(),
			lrNext_(0) { }
	};

	class Notifiee : public virtual NotifieeConst, public virtual Fwk::NamedInterface::Notifiee {
	public:
		typedef Fwk::Ptr<Notifiee const> PtrConst;
		typedef Fwk::Ptr<Notifiee> Ptr;
		Fleet::PtrConst notifier() const { return NotifieeConst::notifier(); }
		Fleet::Ptr notifier() { return const_cast<Fleet *>(NotifieeConst::notifier().ptr()); }

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
	~Fleet() {};
	
	static Fleet::Ptr FleetNew( const string& _name, Fwk::Ptr<Engine> _engine ) {
		Ptr m = new Fleet( _name, _engine );
		m->referencesDec(1);
		return m;
	}

protected:
	Fleet( const Fleet& );
	Fleet( const string& _name, Fwk::Ptr<Engine> _engine ) :
	NamedInterface(_name), engine_(_engine) {
		fleet_[boat_];
		fleet_[truck_];
		fleet_[plane_];
	};
	map<Mode, fleetInfo> fleet_;
	NotifieeList notifiee_;
	Fwk::Ptr<Engine> engine_;
};

class Stats : public Fwk::NamedInterface {
public:
	typedef Fwk::Ptr<Stats const> PtrConst;
	typedef Fwk::Ptr<Stats> Ptr;

	U32 customer() const { return customer_; }
	void customerIs(U32 v) { customer_ = v; }

	U32 port() const { return port_; }
	void portIs(U32 v) { port_ = v; }

	U32 truckTerminal() const { return truckTerminal_; }
	void truckTerminalIs(U32 v) { truckTerminal_ = v; }

	U32 boatTerminal() const { return boatTerminal_; }
	void boatTerminalIs(U32 v) { boatTerminal_ = v; }

	U32 planeTerminal() const { return planeTerminal_; }
	void planeTerminalIs(U32 v) { planeTerminal_ = v; }

	U32 truckSegment() const { return truckSegment_; }
	void truckSegmentIs(U32 v) { truckSegment_ = v; }

	U32 boatSegment() const { return boatSegment_; }
	void boatSegmentIs(U32 v) { boatSegment_ = v; }

	U32 planeSegment() const { return planeSegment_; }
	void planeSegmentIs(U32 v) { planeSegment_ = v; }
	
	Percentage expedite() const 
	    { return 100.0 * (double) expediteNum() / (double) totalSegments(); };
	void expediteIs(Percentage v) {}

	U32 expediteNum() const { return expedite_; };
	void expediteNumIs(U32 v) { expedite_ = v; }
	
	U32 totalSegments() const { return boatSegment_ + truckSegment_ + planeSegment_; };

	Fwk::Ptr<Engine> engine() const { return engine_; };
	void engineIs(Fwk::Ptr<Engine> e) { engine_ = e; };

/*
	typedef Fwk::ListRaw<NotifieeConst> NotifieeList;
	typedef NotifieeList::IteratorConst NotifieeIteratorConst;
	NotifieeIteratorConst notifieeIterConst() const { return notifiee_.iterator(); }
	U32 notifiees() const { return notifiee_.members(); }*/
	~Stats();

	class SegmentExpediteReactor;
	class LocationSegmentReactor;
	
	static Stats::Ptr StatsNew( const string& _name, Fwk::Ptr<Engine> _engine ) {
		Ptr m = new Stats( _name, _engine );
		m->referencesDec(1);
		return m;
	}


protected:
	Stats( const Stats& );
	Stats( const string& _name, Fwk::Ptr<Engine> _engine);
	Fwk::Ptr<Engine> engine_;
	U32 customer_;
	U32 port_;
	U32 truckTerminal_;
	U32 boatTerminal_;
	U32 planeTerminal_;
	U32 boatSegment_;
	U32 truckSegment_;
	U32 planeSegment_;
	U32 expedite_;
	string name_;
};

class Conn;

class Engine : public Fwk::PtrInterface<Engine> {
public:
	typedef Fwk::Ptr<Engine> Ptr;
	typedef Fwk::Ptr<Engine const> PtrConst;

	Engine(Stats::Ptr s, Fwk::Ptr<Conn> c, Fleet::Ptr f);
	
    typedef Fwk::HashMap< Segment, Fwk::String, Segment, Segment::PtrConst, Segment::Ptr > SegmentMap;
	U32 segments() const { return segment_.members(); }
	U32 segmentVersion() const { return segment_.version(); }
	typedef SegmentMap::IteratorConst SegmentIteratorConst;
	SegmentIteratorConst segmentIterConst() const { return segment_.iterator(); }
	typedef SegmentMap::Iterator SegmentIterator;
	SegmentIterator segmentIter() { return segment_.iterator(); }

    typedef Fwk::HashMap< Location, Fwk::String, Location, Location::PtrConst, Location::Ptr > LocationMap;
	U32 locations() const { return location_.members(); }
	U32 locationVersion() const { return location_.version(); }
	typedef LocationMap::IteratorConst LocationIteratorConst;
	LocationIteratorConst locationIterConst() const { return location_.iterator(); }
	typedef LocationMap::Iterator LocationIterator;
	LocationIterator locationIter() { return location_.iterator(); }
	string name() const { return "engine"; }

	void segmentIs(Segment::Ptr s);
	void locationIs(Location::Ptr s);

	Stats::Ptr stats() const { return stats_; };
	void statsIs(Stats::Ptr p);
	Fleet::Ptr fleet() const { return fleet_; };
	void fleetIs(Fleet::Ptr p) { fleet_ = p; };
	Conn* conn() const { return conn_; };
	void connIs(Conn* p) { conn_ = p; };

	Location::Ptr location (const string& name) { return location_[name]; };
	Segment::Ptr segment (const string& name) { return segment_[name]; };

	class NotifieeConst : public virtual Fwk::NamedInterface::NotifieeConst {
	public:
		typedef Fwk::Ptr<NotifieeConst const> PtrConst;
		typedef Fwk::Ptr<NotifieeConst> Ptr;
		string name() const { return notifier_->name(); }
		Engine::PtrConst notifier() const { return notifier_; }
	    bool isNonReferencing() const { return isNonReferencing_; }
        static const AttributeId segment__ = AttributeId(Fwk::NamedInterface::NotifieeConst::tacNextAttributeId__);
        static const AttributeId location__ = AttributeId(Fwk::NamedInterface::NotifieeConst::tacNextAttributeId__+1);
        static const AttributeId tacNextAttributeId__ = AttributeId(location__+1);
        Fwk::String tacKeyForSegment() const { return tacKeyForSegment_; }
        U8 tacSegmentChanges() const { return tacSegmentChanges_; }
		NotifieeConst const * lrNext() const { return lrNext_; }
		NotifieeConst * lrNext() { return lrNext_; }
	
		~NotifieeConst();
		virtual void notifierIs(const Engine::PtrConst& _notifier);
		void isNonReferencingIs(bool _isNonReferencing);
		void lrNextIs(NotifieeConst * _lrNext) {
			lrNext_ = _lrNext;
		}
		virtual void onSegmentIs(Segment::Ptr s) {}
		virtual void onLocationIs(Location::Ptr l) {}

		static NotifieeConst::Ptr NotifieeConstIs() {
			Ptr m = new NotifieeConst();
			m->referencesDec(1);
			return m;
		}
	protected:
        Fwk::String tacKeyForSegment_;
		U8 tacSegmentChanges_;
		Engine::PtrConst notifier_;
		bool isNonReferencing_;

		NotifieeConst* lrNext_;
		NotifieeConst(): Fwk::NamedInterface::NotifieeConst(),
			lrNext_(0) { }
	};

	class Notifiee : public virtual NotifieeConst, public virtual Fwk::NamedInterface::Notifiee {
	public:
		typedef Fwk::Ptr<Notifiee const> PtrConst;
		typedef Fwk::Ptr<Notifiee> Ptr;
		Engine::PtrConst notifier() const { return NotifieeConst::notifier(); }
		Engine::Ptr notifier() { return const_cast<Engine *>(NotifieeConst::notifier().ptr()); }

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

	static Engine::Ptr EngineNew() {
		Ptr m = new Engine();
		m->referencesDec(1);
		return m;
	}
   typedef NotifieeList::Iterator NotifieeIterator;
   NotifieeIterator notifieeIter() { return notifiee_.iterator(); }

private:
	Engine() : expreactor_(NULL), slreactor_(NULL) {}
	Stats::Ptr stats_;
	Fleet::Ptr fleet_;
	Conn* conn_;
	NotifieeList notifiee_;
	SegmentMap segment_;
	LocationMap location_;
	Stats::LocationSegmentReactor* slreactor_;
	Stats::SegmentExpediteReactor* expreactor_;
	void newNotifiee( Engine::NotifieeConst * n ) const {
		Engine* me = const_cast<Engine*>(this);
		me->notifiee_.newMember(n);
	}
	void deleteNotifiee( Engine::NotifieeConst * n ) const {
		Engine* me = const_cast<Engine*>(this);
		me->notifiee_.deleteMember(n);
	}
};

class Stats::LocationSegmentReactor : public Engine::Notifiee {
public:
	virtual void onSegmentIs(Segment::Ptr s) {
		switch(s->mode()) {
		case Segment::truck_:
			stats_->truckSegmentIs(stats_->truckSegment() + 1);
			break;
		case Segment::boat_:
			stats_->boatSegmentIs(stats_->boatSegment() + 1);
			break;
		case Segment::plane_:
			stats_->planeSegmentIs(stats_->planeSegment() + 1);
			break;
		}

		if (s->expedite()) stats_->expediteNumIs(stats_->expediteNum() + 1);
	}
	
	virtual void onLocationIs(Location::Ptr l) {
		switch(l->type()) {
		case Location::customer_:
			stats_->customerIs(stats_->customer() + 1);
			break;
		case Location::port_:
			stats_->portIs(stats_->port() + 1);
			break;
		case Location::truck_:
			stats_->truckTerminalIs(stats_->truckTerminal() + 1);
			break;
		case Location::boat_:
			stats_->boatTerminalIs(stats_->boatTerminal() + 1);
			break;
		case Location::plane_:
			stats_->planeTerminalIs(stats_->planeTerminal() + 1);
			break;
		}
	}
	
   static LocationSegmentReactor * LocationSegmentReactorIs(Engine::Ptr p) {
      LocationSegmentReactor *m = new LocationSegmentReactor(p);
      return m;
   }
protected:
	LocationSegmentReactor(Engine::Ptr e) : stats_(e->stats()) {
		notifierIs(e);
	}
private:
	Stats::Ptr stats_;
};

class Stats::SegmentExpediteReactor : public Segment::Notifiee {
public:
	virtual void onExpedite(Segment::Ptr s, Segment::ExpVal old) {
		if (s->expedite() == old) return;

		if (s->expedite())
			stats_->expediteNumIs(stats_->expediteNum() + 1);
		else
			stats_->expediteNumIs(stats_->expediteNum() - 1);
	}
	
   static SegmentExpediteReactor * SegmentExpediteReactorIs(Segment::Ptr p, Engine::Ptr e) {
      SegmentExpediteReactor *m = new SegmentExpediteReactor(p, e);
      return m;
   }
protected:
	SegmentExpediteReactor(Segment::Ptr s, Engine::Ptr e) : stats_(e->stats()) {
		notifierIs(s);
	}
private:
	Stats::Ptr stats_;
};

} /* end namespace */

#endif
