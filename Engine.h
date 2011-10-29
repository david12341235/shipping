#ifndef ENGINE_H
#define ENGINE_H

#include <string>
#include <vector>

#include "fwk/Ptr.h"
#include "fwk/PtrInterface.h"
#include "fwk/NamedInterface.h"
#include "fwk/ListRaw.h"
#include "fwk/LinkedList.h"
#include "Instance.h"

namespace Shipping {
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
		virtual void onSource( Segment::Ptr _segment ) {}
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
	std::vector< Segment::Ptr > segment_;
	NotifieeList notifiee_;
};

class Segment : public Fwk::NamedInterface {
public:
	typedef Fwk::Ptr<Segment const> PtrConst;
	typedef Fwk::Ptr<Segment> Ptr;
	typedef int SegmentId;
	typedef int Length;
	typedef bool ExpediteSupport;

	enum Mode {
		truck_ = 0,
		boat_ = 1,
		plane_ = 2,
	};
	static inline Mode truck() { return truck_; }
	static inline Mode boat() { return boat_; }
	static inline Mode plane() { return plane_; }
	static SegmentId SegmentIdInstance ( int v );
	
	Location::Ptr source();
	void sourceIs(Location::Ptr l);

	Length length();
	void lengthIs(Length l);

	Segment::Ptr returnSegment();
	void returnSegmentIs(Segment::Ptr p);

	ExpediteSupport expediteSupport();
	void expediteSupportIs(ExpediteSupport e);
};

class Stats;
class Conn;
class Fleet;

class SegmentReactor : public Segment::Notifiee {
public:
	SegmentReactor(Engine* e) : engine_(e) {}
	// maybe not necessary?
/*	virtual void onSourceIs( Segment::Ptr _segment ) {
		Location::Ptr l = engine_->location(_segment->source());
		// update location
	}*/
private:
	Engine::Ptr engine_;
};

class Engine : public Fwk::PtrInterface<Engine> {
public:
	typedef Fwk::Ptr<Engine> Ptr;
	typedef Fwk::Ptr<Engine const> PtrConst;

	Engine(Stats* s, Conn* c, Fleet* f);
	
	// add a new segment
	void segmentIs(Segment s);

	// add a new location
	void locationIs(Location s);

	// change to Stats::Ptr etc when the classes are defined
	Stats* stats();
	Stats* fleet();
	Stats* conn();
	
	Fwk::LinkedList<Location::Ptr> locations();
	Fwk::LinkedList<Segment::Ptr> segments();

	Location::Ptr location(const string& name);
	Segment::Ptr segment(const string& name);
};

} /* end namespace */

#endif
