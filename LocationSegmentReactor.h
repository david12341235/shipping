#ifndef LOCATIONSEGMENTREACTOR_H
#define LOCATIONSEGMENTREACTOR_H

#include "Engine.h"
#include "Stats.h"

namespace Shipping {

class Stats::LocationSegmentReactor : public Engine::Notifiee
{
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

    virtual void onSegmentDel(Segment::Ptr s) {
        switch(s->mode()) {
        case Segment::truck_:
            stats_->truckSegmentIs(stats_->truckSegment() - 1);
            break;
        case Segment::boat_:
            stats_->boatSegmentIs(stats_->boatSegment() - 1);
            break;
        case Segment::plane_:
            stats_->planeSegmentIs(stats_->planeSegment() - 1);
            break;
        }

        if (s->expedite()) stats_->expediteNumIs(stats_->expediteNum() - 1);
    }

    virtual void onLocationDel(Location::Ptr l) {
        switch(l->type()) {
        case Location::customer_:
            stats_->customerIs(stats_->customer() - 1);
            break;
        case Location::port_:
            stats_->portIs(stats_->port() - 1);
            break;
        case Location::truck_:
            stats_->truckTerminalIs(stats_->truckTerminal() - 1);
            break;
        case Location::boat_:
            stats_->boatTerminalIs(stats_->boatTerminal() - 1);
            break;
        case Location::plane_:
            stats_->planeTerminalIs(stats_->planeTerminal() - 1);
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

class Stats::SegmentExpediteReactor : public Segment::Notifiee
{
public:
    virtual void onExpedite(Segment::ExpVal old) {
		Segment::Ptr s = notifier();
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

class SendingShipmentsReactor : public Customer::NotifieeConst
{
public:
    virtual void onSendingShipmentsIs(Customer::Ptr c) {
		Activity::Manager::Ptr manager = activityManagerInstance();

		if (c->sendingShipments()) {
			Activity::Ptr ship = manager->activityNew(c->name().append(" shipment"));
    
			ship->lastNotifieeIs(new InjectShipmentReactor(manager,
					ship.ptr(), 24.0, c));
		} else {
			manager->activityDel(c->name().append(" shipment"));
		}
    }

    static SendingShipmentsReactor * SendingShipmentsReactorIs(Engine::Ptr e) {
        SendingShipmentsReactor *m = new SendingShipmentsReactor(e);
        return m;
    }
protected:
    SendingShipmentsReactor(Engine::Ptr e) : engine_(e) {
    }
private:
    Engine::Ptr engine_;
};

}

#endif