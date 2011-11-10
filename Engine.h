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
#include "Location.h"
#include "Conn.h"
#include "Fleet.h"
#include "Stats.h"

namespace Shipping {
using namespace std;

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
	void segmentDel(const string& s);
	void locationIs(Location::Ptr l);
	void locationDel(const string& l);

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
	Stats::SegmentExpediteReactor* expreactor_;
	Stats::LocationSegmentReactor* slreactor_;
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
