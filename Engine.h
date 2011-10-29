#ifndef ENGINE_H
#define ENGINE_H

#include <string>

#include "Ptr.h"
#include "PtrInterface.h"
#include "Instance.h"

namespace Shipping {

class Segment : public Fwk::NamedInterface {
public:
	typedef Fwk::Ptr<Segment const> PtrConst;
	typedef Fwk::Ptr<Segment> Ptr;
	typedef int SegmentId;

	enum Mode {
		truck_ = 0;
		boat_ = 1;
		plane_ = 2;
	};

	enum ExpVal {
		expNo_ = 0;
		expYes_ = 1;
	};

	static inline Mode truck() { return truck_; }
	static inline Mode boat() { return boat_; }
	static inline Mode plane() { return plane_; }
	static inline ExpVal expNo() { return expNo_; }
	static inline ExpVal expYes() { return expYes_; }
	static SegmentId SegmentIdInstance ( int v );
	static Mode TypeInstance( Fwk::String );
	static ExpVal TypeInstance( Fwk::String );

	Mode mode() { return mode_; }
	virtual void modeIs( Mode v ){ mode_ = v }

	string source(){ return source_ }
	void sourceIs( const string& _source );

	Mile length(){ return length_ }
	void lengthIs( const Mile& _length ) { length_ = _length }

	string returnSegment(){ return returnSegment_ }
	void returnSegmentIs( const string& _returnSegment ); 

	Difficulty difficulty(){ return difficulty_ }
	void difficultyIs( const Difficulty& _difficulty ) { difficulty_ = _difficulty}

	ExpVal expedite() { return expedite_ }
	void expediteIs( ExpVal e ) { expedite_ = e }

	class NotifieeConst : public virtual Fwk::NamedInterface::NotifieeConst {
	public:
		typedef Fwk::Ptr<NotifieeConst const> PtrConst;
		typedef Fwk::Ptr<NotifieeConst> Ptr;
		string name() const { return notifier_->name(); }
		Segment::PtrConst notifier() const { return notifier_; }
		NotifieeConst const * lrNext() const { return lrNext_; }
		NotifieeConst * lrNext() { return lrNext_; }
	
		~NotifieeConst();
		virtual void notifierIs(const Segment::PtrConst& _notifier);
		virtual void onSource() {}
		virtual void onLength() {}
		virtual void onReturnSegment() {}
		virtual void onDifficulty() {}
		virtual void onExpedite() {}

		static NotifieeConst::Ptr NotifieeConstIs() {
			Ptr m = new NotifieeConst();
			m->referencesDec(1);
			return m;
		}
	protected:
		Segment::PtrConst notifier_;

		NotifieeConst* lrNext_;
		NotifieeConst(): Fwk::NamedInterface::NotifieeConst(),
			lrNext_(0) { }
	};

	class Notifiee : public virtual NotifieeConst, public virtual Fwk::NamedInterface::Notifiee {
	public:
		typedef Fwk::Ptr<Notifiee const> PtrConst;
		typedef Fwk::Ptr<Notifiee> Ptr;
		Segment::PtrConst notifier() const { return NotifieeConst::notifier(); }
		Segment::Ptr notifier() { return const_cast<Segment *>(NotifieeConst::notifier().ptr()); }

		static Notifiee::Ptr NotifieeIs() {
			Ptr m = new NotifieeIs();
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
	~Segment();
	
	static Segment::Ptr SegmentIs( const string& _name, Mode _mode, Engine* _engine ) {
		Ptr m = new Segment( _name, _type, _engine );
		m->referencesDec(1);
		return m;
	}

protected:
	Segment( const Segment& );
	Segment( const string& _name, Mode _mode, Engine* _engine );
	Mode mode_;
	string source_;
	Mile length_;
	Difficulty difficulty_;
	ExpVal expedite_;
};

class Location : public Fwk::NamedInterface {
public:
	typedef Fwk::Ptr<Location const> PtrConst;
	typedef Fwk::Ptr<Location> Ptr;
	enum Type {
		customer_ = 0;
		port_ = 1;
		truck_ = 2;
		boat_ = 3;
		plane_ = 4;
	};
	static inline Type customer() { return customer_; }
	static inline Type port() { return port_; }
	static inline Type truck() { return truck_; }
	static inline Type boat() { return boat_; }
	static inline Type plane() { return plane_; }

	static Type TypeInstance( Fwk::String );
	Type type() { return type_; }
	virtual void typeIs( Type _type ) { type_ = _type }

	string segment( Segment::SegmentId _segmentId );
	void segmentIs(); // does nothing

	class NotifieeConst : public virtual Fwk::NamedInterface::NotifieeConst {
	public:
		typedef Fwk::Ptr<NotifieeConst const> PtrConst;
		typedef Fwk::Ptr<NotifieeConst> Ptr;
		string name() const { return notifier_->name(); }
		Location::PtrConst notifier() const { return notifier_; }
		NotifieeConst const * lrNext() const { return lrNext_; }
		NotifieeConst * lrNext() { return lrNext_; }
	
		~NotifieeConst();
		virtual void notifierIs(const Location::PtrConst& _notifier);
		virtual void onSegmentNew( const string& _segment ) {}
		virtual void onSegmentDel( const string& _segment ) {}
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
	}

	class Notifiee : public virtual NotifieeConst, public virtual Fwk::NamedInterface::Notifiee {
	public:
		typedef Fwk::Ptr<Notifiee const> PtrConst;
		typedef Fwk::Ptr<Notifiee> Ptr;
		Location::PtrConst notifier() const { return NotifieeConst::notifier(); }
		Location::Ptr notifier() { return const_cast<Location *>(NotifieeConst::notifier().ptr()); }

		static Notifiee::Ptr NotifieeIs() {
			Ptr m = new NotifieeIs();
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
	vector< string > segment_;
};

class Fleet : public Fwk::NamedInterface {
public:
	typedef Fwk::Ptr<Fleet const> PtrConst;
	typedef Fwk::Ptr<Fleet> Ptr;

	enum Mode {
		truck_ = 0;
		boat_ = 1;
		plane_ = 2;
	};

	struct fleetInfo
	{
		Mph speed_;
		U32 capacity_;
		Dollars cost;
	}

	static inline Mode truck() { return truck_; }
	static inline Mode boat() { return boat_; }
	static inline Mode plane() { return plane_; }

	static Mode TypeInstance( Fwk::String );

	Mph speed( Mode m ) { return fleet_[m].speed_ }
	void speedIs( Mph _speed ) { fleet_[m].speed_ = _speed }

	U32 capacity( Mode m ) { return fleet_[m].capacity_ }
	void capacityIs( U32 _capacity ) { fleet_[m].capacity_ = _capacity }

	Dollars cost( Mode m ) { return fleet_[m].cost_ }
	void costIs( Dollars _cost ) { fleet_[m].cost_ = _cost }

	class NotifieeConst : public virtual Fwk::NamedInterface::NotifieeConst {
	public:
		typedef Fwk::Ptr<NotifieeConst const> PtrConst;
		typedef Fwk::Ptr<NotifieeConst> Ptr;
		string name() const { return notifier_->name(); }
		Fleet::PtrConst notifier() const { return notifier_; }
		NotifieeConst const * lrNext() const { return lrNext_; }
		NotifieeConst * lrNext() { return lrNext_; }
	
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
			Ptr m = new NotifieeIs();
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
	~Fleet();
	
	static Fleet::Ptr FleetIs( const string& _name, Engine* _engine ) {
		Ptr m = new Fleet( _name, _engine );
		m->referencesDec(1);
		return m;
	}

protected:
	Fleet( const Fleet& );
	Fleet( const string& _name, Engine* _engine );
	map<Mode, fleetInfo> fleet_;
};

class Stats : public Fwk::NamedInterface {
public:
	typedef Fwk::Ptr<Stats const> PtrConst;
	typedef Fwk::Ptr<Stats> Ptr;

	U32 customer() { return customer_ }
	U32 customerIs() {}

	U32 port() { return port_ }
	U32 portIs() {}

	U32 truckTerminal() { return truckTerminal_ }
	U32 truckTerminalIs() {}

	U32 boatTerminal() { return boatTerminal_ }
	U32 boatTerminalIs() {}

	U32 planeTerminal() { return planeTerminal_ }
	U32 planeTerminalIs() {}

	U32 truckSegment() { return truckSegment_ }
	U32 truckSegmentIs() {}

	U32 boatSegment() { return boatSegment_ }
	U32 boatSegmentIs() {}

	U32 planeSegment() { return planeSegment_ }
	U32 planeSegmentIs() {}

	Percentage expedite();
	Percentage expediteIs() {}

	typedef Fwk::ListRaw<NotifieeConst> NotifieeList;
	typedef NotifieeList::IteratorConst NotifieeIteratorConst;
	NotifieeIteratorConst notifieeIterConst() const { return notifiee_.iterator(); }
	U32 notifiees() const { return notifiee_.members(); }
	~Stats();
	
	static Stats::Ptr StatsIs( const string& _name, Engine* _engine ) {
		Ptr m = new Stats( _name, _engine );
		m->referencesDec(1);
		return m;
	}

protected:
	Stats( const Stats& );
	Stats( const string& _name, Engine* _engine );
	U32 customer_;
	U32 port_;
	U32 truckTerminal_;
	U32 boatTerminal_;
	U32 planeTerminal_;
	U32 truckSegment_;
	U32 boatSegment_;
	U32 planeSegment_;
	U32 expedite_;
};


} /* end namespace */

#endif
