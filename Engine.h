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
#include "Instance.h"
#include "Nominal.h"
#include "ShippingTypes.h"

namespace Shipping {
using namespace std;

class Engine;
class Location;

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

	enum ExpVal {
		expNo_ = 0,
		expYes_ = 1,
	};

	static inline Mode truck() { return truck_; }
	static inline Mode boat() { return boat_; }
	static inline Mode plane() { return plane_; }
	static inline ExpVal expNo() { return expNo_; }
	static inline ExpVal expYes() { return expYes_; }
	static SegmentId SegmentIdInstance ( int v );
	static inline Mode ModeInstance( const Fwk::String );
	static inline ExpVal ExpValInstance( const Fwk::String v ) { return v == "Yes" ? expYes() : expNo(); }

	Mode mode() const { return mode_; }
	virtual void modeIs( Mode v ){ mode_ = v; }

	Fwk::Ptr<Location> source() const { return source_; }
	virtual void sourceIs( Fwk::Ptr<Location> _source );

	Mile length() const { return length_; }
	void lengthIs( const Mile& _length ) { length_ = _length; }

	PtrConst returnSegment() const { return returnSegment_; }
	void returnSegmentIs( Segment::Ptr _returnSegment ); 

	Difficulty difficulty() const { return difficulty_; }
	void difficultyIs( const Difficulty& _difficulty ) { difficulty_ = _difficulty; }

	ExpVal expedite() const { return expedite_; }
	void expediteIs( ExpVal e ) { expedite_ = e; }

	class NotifieeConst : public virtual Fwk::NamedInterface::NotifieeConst {
	public:
		typedef Fwk::Ptr<NotifieeConst const> PtrConst;
		typedef Fwk::Ptr<NotifieeConst> Ptr;
		string name() const { return notifier_->name(); }
		Segment::PtrConst notifier() const { return notifier_; }
		NotifieeConst const * lrNext() const { return lrNext_; }
		NotifieeConst * lrNext() { return lrNext_; }
		void lrNextIs(NotifieeConst * _lrNext) {
			lrNext_ = _lrNext;
		}
	
		~NotifieeConst();
		virtual void notifierIs(const Segment::PtrConst& _notifier);
		virtual void onSource() {}
		virtual void onLength() {}
		virtual void onReturnSegment() {}
		virtual void onDifficulty() {}
		virtual void onExpedite(Segment::Ptr s) {}

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
	~Segment() {};
	
	static Segment::Ptr SegmentNew( const string& _name, Mode _mode, Fwk::Ptr<Engine> _engine ) {
		Ptr m = new Segment( _name, _mode, _engine );
		m->referencesDec(1);
		return m;
	}

protected:
	Segment( const Segment& );
	Segment( const string& _name, Mode _mode, Fwk::Ptr<Engine> _engine );
	Mode mode_;
	Fwk::Ptr<Engine> engine_;
	Fwk::Ptr<Location> source_;
	Mile length_;
	Difficulty difficulty_;
	ExpVal expedite_;
	Ptr returnSegment_;
	NotifieeList notifiee_;
};

class TruckSegment : public Segment {
public:
	typedef Fwk::Ptr<TruckSegment const> PtrConst;
	typedef Fwk::Ptr<TruckSegment> Ptr;

	Mode mode() const { return Segment::truck(); }
	virtual void modeIs( Mode v ) {}
	virtual void sourceIs( Fwk::Ptr<Location> _source ) {};

	class NotifieeConst : public virtual Segment::NotifieeConst {
	public:
		typedef Fwk::Ptr<NotifieeConst const> PtrConst;
		typedef Fwk::Ptr<NotifieeConst> Ptr;
		string name() const { return notifier_->name(); }
		TruckSegment::PtrConst notifier() const { return dynamic_cast<TruckSegment const *>(Segment::NotifieeConst::notifier().ptr()); }
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
		TruckSegment::PtrConst notifier_;

		NotifieeConst* lrNext_;
		NotifieeConst(): Fwk::NamedInterface::NotifieeConst(),
			lrNext_(0) { }
	};

	class Notifiee : public virtual NotifieeConst, public virtual Segment::Notifiee {
	public:
		typedef Fwk::Ptr<Notifiee const> PtrConst;
		typedef Fwk::Ptr<Notifiee> Ptr;
		TruckSegment::PtrConst notifier() const { return dynamic_cast<TruckSegment const *>(Segment::NotifieeConst::notifier().ptr()); }
		TruckSegment::Ptr notifier() { return dynamic_cast<TruckSegment * >(const_cast<Segment *>(Segment::NotifieeConst::notifier().ptr())); }

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
	
	static TruckSegment::Ptr TruckSegmentNew( const string& _name, Fwk::Ptr<Engine> _engine ) {
		Ptr m = new TruckSegment( _name, _engine );
		m->referencesDec(1);
		return m;
	}

protected:
	TruckSegment( const TruckSegment& );
	TruckSegment( const string& _name, Fwk::Ptr<Engine> _engine ) : 
		Segment( _name, mode(), _engine ) {};
	NotifieeList notifiee_;
};

class BoatSegment : public Segment {
public:
	typedef Fwk::Ptr<BoatSegment const> PtrConst;
	typedef Fwk::Ptr<BoatSegment> Ptr;

	Mode mode() const { return Segment::truck(); }
	virtual void modeIs( Mode v ) {}
	virtual void sourceIs( Fwk::Ptr<Location> _source ) {};

	class NotifieeConst : public virtual Segment::NotifieeConst {
	public:
		typedef Fwk::Ptr<NotifieeConst const> PtrConst;
		typedef Fwk::Ptr<NotifieeConst> Ptr;
		string name() const { return notifier_->name(); }
		BoatSegment::PtrConst notifier() const { return dynamic_cast<BoatSegment const *>(Segment::NotifieeConst::notifier().ptr()); }
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
		BoatSegment::PtrConst notifier_;

		NotifieeConst* lrNext_;
		NotifieeConst(): Fwk::NamedInterface::NotifieeConst(),
			lrNext_(0) { }
	};

	class Notifiee : public virtual NotifieeConst, public virtual Segment::Notifiee {
	public:
		typedef Fwk::Ptr<Notifiee const> PtrConst;
		typedef Fwk::Ptr<Notifiee> Ptr;
		BoatSegment::PtrConst notifier() const { return dynamic_cast<BoatSegment const *>(Segment::NotifieeConst::notifier().ptr()); }
		BoatSegment::Ptr notifier() { return dynamic_cast<BoatSegment * >(const_cast<Segment *>(Segment::NotifieeConst::notifier().ptr())); }

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
	
	static BoatSegment::Ptr BoatSegmentNew( const string& _name, Fwk::Ptr<Engine> _engine ) {
		Ptr m = new BoatSegment( _name, _engine );
		m->referencesDec(1);
		return m;
	}

protected:
	BoatSegment( const BoatSegment& );
	BoatSegment( const string& _name, Fwk::Ptr<Engine> _engine ) : Segment( _name, mode(), _engine ) {};
	NotifieeList notifiee_;
};

class PlaneSegment : public Segment {
public:
	typedef Fwk::Ptr<PlaneSegment const> PtrConst;
	typedef Fwk::Ptr<PlaneSegment> Ptr;

	Mode mode() const { return Segment::truck(); }
	virtual void modeIs( Mode v ) {}
	virtual void sourceIs( Fwk::Ptr<Location> _source ) {};

	class NotifieeConst : public virtual Segment::NotifieeConst {
	public:
		typedef Fwk::Ptr<NotifieeConst const> PtrConst;
		typedef Fwk::Ptr<NotifieeConst> Ptr;
		string name() const { return notifier_->name(); }
		PlaneSegment::PtrConst notifier() const { return dynamic_cast<PlaneSegment const *>(Segment::NotifieeConst::notifier().ptr()); }
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
		PlaneSegment::PtrConst notifier_;

		NotifieeConst* lrNext_;
		NotifieeConst(): Fwk::NamedInterface::NotifieeConst(),
			lrNext_(0) { }
	};

	class Notifiee : public virtual NotifieeConst, public virtual Segment::Notifiee {
	public:
		typedef Fwk::Ptr<Notifiee const> PtrConst;
		typedef Fwk::Ptr<Notifiee> Ptr;
		PlaneSegment::PtrConst notifier() const { return dynamic_cast<PlaneSegment const *>(Segment::NotifieeConst::notifier().ptr()); }
		PlaneSegment::Ptr notifier() { return dynamic_cast<PlaneSegment * >(const_cast<Segment *>(Segment::NotifieeConst::notifier().ptr())); }

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
	
	static PlaneSegment::Ptr PlaneSegmentNew( const string& _name, Fwk::Ptr<Engine> _engine ) {
		Ptr m = new PlaneSegment( _name, _engine );
		m->referencesDec(1);
		return m;
	}

protected:
	PlaneSegment( const PlaneSegment& );
	PlaneSegment( const string& _name, Fwk::Ptr<Engine> _engine ) : Segment( _name, mode(), _engine ) {};
	NotifieeList notifiee_;
};


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
		NotifieeConst(): Fwk::NamedInterface::NotifieeConst(),
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
		Notifiee(): Fwk::NamedInterface::Notifiee() { }
	};

	typedef Fwk::ListRaw<NotifieeConst> NotifieeList;
	typedef NotifieeList::IteratorConst NotifieeIteratorConst;
	NotifieeIteratorConst notifieeIterConst() const { return notifiee_.iterator(); }
	U32 notifiees() const { return notifiee_.members(); }
	
	static Customer::Ptr CustomerNew( const string& _name, Fwk::Ptr<Engine> _engine ) {
		Ptr m = new Customer( _name, _engine );
		m->referencesDec(1);
		return m;
	}

protected:
	Customer( const Customer& );
	Customer( const string& _name, Fwk::Ptr<Engine> _engine ) : Location( _name, type(), _engine ) {};
	NotifieeList notifiee_;
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
		NotifieeConst(): Fwk::NamedInterface::NotifieeConst(),
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
		Notifiee(): Fwk::NamedInterface::Notifiee() { }
	};

	typedef Fwk::ListRaw<NotifieeConst> NotifieeList;
	typedef NotifieeList::IteratorConst NotifieeIteratorConst;
	NotifieeIteratorConst notifieeIterConst() const { return notifiee_.iterator(); }
	U32 notifiees() const { return notifiee_.members(); }
	
	static Port::Ptr PortNew( const string& _name, Fwk::Ptr<Engine> _engine ) {
		Ptr m = new Port( _name, _engine );
		m->referencesDec(1);
		return m;
	}

protected:
	Port( const Port& );
	Port( const string& _name, Fwk::Ptr<Engine> _engine ) : Location( _name, type(), _engine ) {};
	NotifieeList notifiee_;
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
		NotifieeConst(): Fwk::NamedInterface::NotifieeConst(),
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
		Notifiee(): Fwk::NamedInterface::Notifiee() { }
	};

	typedef Fwk::ListRaw<NotifieeConst> NotifieeList;
	typedef NotifieeList::IteratorConst NotifieeIteratorConst;
	NotifieeIteratorConst notifieeIterConst() const { return notifiee_.iterator(); }
	U32 notifiees() const { return notifiee_.members(); }
	
	static TruckLocation::Ptr TruckLocationNew( const string& _name, Fwk::Ptr<Engine> _engine ) {
		Ptr m = new TruckLocation( _name, _engine );
		m->referencesDec(1);
		return m;
	}

protected:
	TruckLocation( const TruckLocation& );
	TruckLocation( const string& _name, Fwk::Ptr<Engine> _engine ) : Location( _name, type(), _engine ) {};
	NotifieeList notifiee_;
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
		NotifieeConst(): Fwk::NamedInterface::NotifieeConst(),
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
		Notifiee(): Fwk::NamedInterface::Notifiee() { }
	};

	typedef Fwk::ListRaw<NotifieeConst> NotifieeList;
	typedef NotifieeList::IteratorConst NotifieeIteratorConst;
	NotifieeIteratorConst notifieeIterConst() const { return notifiee_.iterator(); }
	U32 notifiees() const { return notifiee_.members(); }
	
	static BoatLocation::Ptr BoatLocationNew( const string& _name, Fwk::Ptr<Engine> _engine ) {
		Ptr m = new BoatLocation( _name, _engine );
		m->referencesDec(1);
		return m;
	}

protected:
	BoatLocation( const BoatLocation& );
	BoatLocation( const string& _name, Fwk::Ptr<Engine> _engine ) : Location( _name, type(), _engine ) {};
	NotifieeList notifiee_;
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

	typedef Fwk::ListRaw<NotifieeConst> NotifieeList;
	typedef NotifieeList::IteratorConst NotifieeIteratorConst;
	NotifieeIteratorConst notifieeIterConst() const { return notifiee_.iterator(); }
	U32 notifiees() const { return notifiee_.members(); }
	
	static PlaneLocation::Ptr PlaneLocationNew( const string& _name, Fwk::Ptr<Engine> _engine ) {
		Ptr m = new PlaneLocation( _name, _engine );
		m->referencesDec(1);
		return m;
	}

protected:
	PlaneLocation( const PlaneLocation& );
	PlaneLocation( const string& _name, Fwk::Ptr<Engine> _engine ) : Location( _name, type(), _engine ) {};
	NotifieeList notifiee_;
};

class Conn : public Fwk::NamedInterface {
public:
	typedef Fwk::Ptr<Conn const> PtrConst;
	typedef Fwk::Ptr<Conn> Ptr;

	enum Type{
		explore_ = 0,
		connect_ = 1
	};

	static inline Type explore() { return explore_; }
	static inline Type connect() { return connect_; }

	static Type TypeInstance( Fwk::String );

	Mile distance() const { return distance_; }
	void distanceIs( Mile _distance ) { distance_ = _distance; }

	Dollar cost() const { return cost_; }
	void costIs( Dollar _cost ) { cost_ = _cost; }

	Hour time() const { return time_; }
	void timeIs( Hour _time ) { time_ = _time; }

	Segment::ExpVal expedited() const { return expedited_; }
	void expeditedIs( Segment::ExpVal _expedited ) { expedited_ = _expedited; }

	string value();
	
	Fwk::Ptr<Engine> engine() const { return engine_; };
	void engineIs(Fwk::Ptr<Engine> e) { engine_ = e; };

	class NotifieeConst : public virtual Fwk::NamedInterface::NotifieeConst {
	public:
		typedef Fwk::Ptr<NotifieeConst const> PtrConst;
		typedef Fwk::Ptr<NotifieeConst> Ptr;
		string name() const { return notifier_->name(); }
		Conn::PtrConst notifier() const { return notifier_; }
		NotifieeConst const * lrNext() const { return lrNext_; }
		NotifieeConst * lrNext() { return lrNext_; }
		void lrNextIs(NotifieeConst * _lrNext) {
			lrNext_ = _lrNext;
		}
	
		~NotifieeConst();

		static NotifieeConst::Ptr NotifieeConstIs() {
			Ptr m = new NotifieeConst();
			m->referencesDec(1);
			return m;
		}
	protected:
		Conn::PtrConst notifier_;

		NotifieeConst* lrNext_;
		NotifieeConst(): Fwk::NamedInterface::NotifieeConst(),
			lrNext_(0) { }
	};

	class Notifiee : public virtual NotifieeConst, public virtual Fwk::NamedInterface::Notifiee {
	public:
		typedef Fwk::Ptr<Notifiee const> PtrConst;
		typedef Fwk::Ptr<Notifiee> Ptr;
		Conn::PtrConst notifier() const { return NotifieeConst::notifier(); }
		Conn::Ptr notifier() { return const_cast<Conn *>(NotifieeConst::notifier().ptr()); }

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
	~Conn() {};
	
	static Conn::Ptr ConnNew( const string& _name, Fwk::Ptr<Engine> _engine ) {
		Ptr m = new Conn( _name, _engine );
		m->referencesDec(1);
		return m;
	}

protected:
	Conn( const Conn& );
	Conn( const string& _name);
	Conn( const string& _name, Fwk::Ptr<Engine> _engine ) :
	    NamedInterface(_name), engine_(_engine), 
		distance_(0), cost_(0), time_(0) {};
	NotifieeList notifiee_;
	Fwk::Ptr<Engine> engine_;
	Mile distance_;
	Dollar cost_;
	Hour time_;
	Segment::ExpVal expedited_;
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
	void customerIs(U32 v) {}

	U32 port() const { return port_; }
	void portIs(U32 v) {}

	U32 truckTerminal() const { return truckTerminal_; }
	void truckTerminalIs(U32 v) {}

	U32 boatTerminal() const { return boatTerminal_; }
	void boatTerminalIs(U32 v) {}

	U32 planeTerminal() const { return planeTerminal_; }
	void planeTerminalIs(U32 v) {}

	U32 truckSegment() const { return truckSegment_; }
	void truckSegmentIs(U32 v) {}

	U32 boatSegment() const { return boatSegment_; }
	void boatSegmentIs(U32 v) {}

	U32 planeSegment() const { return planeSegment_; }
	void planeSegmentIs(U32 v) {}
	
	Percentage expedite() const {return (double) expediteNum() / (double) totalSegments(); };
	void expediteIs(Percentage v) {}

	U32 expediteNum() const { return expedite_; };
	void expediteNumIs(U32 v) {}
	
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
	Stats( const string& _name, Fwk::Ptr<Engine> _engine) :
	NamedInterface(_name), engine_(_engine), customer_(0), 
	port_(0), truckTerminal_(0), boatTerminal_(0),
	planeTerminal_(0), boatSegment_(0), truckSegment_(0), 
	planeSegment_(0), expedite_(0) {};
	U32 customer_;
	U32 port_;
	U32 truckTerminal_;
	U32 boatTerminal_;
	U32 planeTerminal_;
	U32 truckSegment_;
	U32 boatSegment_;
	U32 planeSegment_;
	U32 expedite_;
	Fwk::Ptr<Engine> engine_;
	string name_;
};


class Engine : public Fwk::PtrInterface<Engine> {
public:
	typedef Fwk::Ptr<Engine> Ptr;
	typedef Fwk::Ptr<Engine const> PtrConst;

	Engine(Stats::Ptr s, Conn::Ptr c, Fleet::Ptr f);
	
	void segmentIs(Segment::Ptr s) {};

	void locationIs(Location::Ptr s) {};

	Stats::Ptr stats() const;
	Fleet::Ptr fleet() const;
	Conn::Ptr conn() const;
	
	Fwk::LinkedList<Location::Ptr> locations() const;
	Fwk::LinkedList<Segment::Ptr> segments() const;

	Location::Ptr location (const string& name) const { return NULL; };
	Segment::Ptr segment (const string& name) const { return NULL; };

	class NotifieeConst : public virtual Fwk::NamedInterface::NotifieeConst {
	public:
		typedef Fwk::Ptr<NotifieeConst const> PtrConst;
		typedef Fwk::Ptr<NotifieeConst> Ptr;
		string name() const { return notifier_->name(); }
		Segment::PtrConst notifier() const { return notifier_; }
		NotifieeConst const * lrNext() const { return lrNext_; }
		NotifieeConst * lrNext() { return lrNext_; }
		void lrNextIs(NotifieeConst * _lrNext) {
			lrNext_ = _lrNext;
		}
	
		~NotifieeConst();
		virtual void notifierIs(const Segment::PtrConst& _notifier);
		virtual void onSegmentIs(Segment::Ptr s) {}
		virtual void onLocationIs(Location::Ptr l) {}

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

private:
	Engine() {}
	NotifieeList notifiee_;
};

class Stats::LocationSegmentReactor : public Engine::Notifiee {
public:
	LocationSegmentReactor(Stats* e) : stats_(e) {}
	
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
private:
	Stats::Ptr stats_;
};

class Stats::SegmentExpediteReactor : public Segment::Notifiee {
public:
	SegmentExpediteReactor(Stats* e) : stats_(e) {}
	virtual void onExpedite(Segment::Ptr s) {
		if (s->expedite())
			stats_->expediteNumIs(stats_->expediteNum() + 1);
		else
			stats_->expediteNumIs(stats_->expediteNum() - 1);
	}
private:
	Stats::Ptr stats_;
};

} /* end namespace */

#endif
