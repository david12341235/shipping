#ifndef FLEET_H
#define FLEET_H

#include <string>
#include "fwk/Ptr.h"
#include "fwk/NamedInterface.h"
#include "ShippingTypes.h"
#include "Engine.h"

using namespace std;

namespace Shipping {

class Engine;

class Fleet : public Fwk::NamedInterface {
public:
	typedef Fwk::Ptr<Fleet const> PtrConst;
	typedef Fwk::Ptr<Fleet> Ptr;

	struct fleetInfo
	{
		Mph speed_;
		NumPackages capacity_;
		Dollar cost_;

		public:
			fleetInfo() : speed_(1.0), capacity_(1), cost_(1.0) {}
	};

	static Segment::Mode TypeInstance( Fwk::String );

	Mph speed( Segment::Mode m ) const { return fleet_.at(m).speed_; };
	void speedIs( Segment::Mode m, Mph _speed ) { fleet_[m].speed_ = _speed; }

	NumPackages capacity( Segment::Mode m ) const { return fleet_.at(m).capacity_; };
	void capacityIs( Segment::Mode m, NumPackages _capacity ) { fleet_[m].capacity_ = _capacity; }

	Dollar cost( Segment::Mode m ) const { return fleet_.at(m).cost_; };
	void costIs( Segment::Mode m, Dollar _cost ) { fleet_[m].cost_ = _cost; }
	
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
		virtual void onSpeed( Segment::Mode _mode ) {}
		virtual void onCapacity( Segment::Mode _mode ) {}
		virtual void onCost( Segment::Mode _mode ) {}

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
		fleet_[Segment::boat()] = fleetInfo();
		fleet_[Segment::truck()] = fleetInfo();
		fleet_[Segment::plane()] = fleetInfo();
	};
	map<Segment::Mode, fleetInfo> fleet_;
	NotifieeList notifiee_;
	Fwk::Ptr<Engine> engine_;
};

} // namespace

#endif
