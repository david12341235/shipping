#ifndef STATS_H
#define STATS_H

#include <string>
#include "fwk/Ptr.h"
#include "fwk/NamedInterface.h"
#include "ShippingTypes.h"
#include "Engine.h"

using namespace std;

namespace Shipping {

class Engine;

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


} // namespace

#endif
