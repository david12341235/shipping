#include "Engine.h"
#include "LocationSegmentReactor.h"

using namespace Shipping;

void Engine::locationIs(Location::Ptr l)
{
    string name = l->name();
    Location::Ptr m = location_[name];
    if(m != NULL ) {
        throw Fwk::NameInUseException(name);
    } else {
        m = l;
        location_.newMember(m);

		if (l->type() == Location::customer()) {
			if (!sshipreactor_)
				sshipreactor_ = SendingShipmentsReactor::SendingShipmentsReactorIs(this);
			Customer *c = dynamic_cast<Customer*>(l.ptr());
			if (c)
				c->newNotifiee(sshipreactor_);
		}
    }
retrycell:
    U32 ver = notifiee_.version();
    if(notifiees()) for(NotifieeIterator n=notifieeIter(); n.ptr(); ++n) try {
                n->onLocationIs(l);
                if( ver != notifiee_.version() ) goto retrycell;
            } catch(...) {
                n->onNotificationException(NotifieeConst::location__);
            }
}

void Engine::locationDel(const string& l)
{
    try {
        Location::Ptr p = location_[l];
        int i = 1;
        Segment::PtrConst s = p->segment(i);
        while(s != NULL ) {
            segment_[s->name()]->sourceIs(NULL);
            s = p->segment(++i);
        }
        location_.memberDel(l);

retrycell:
        U32 ver = notifiee_.version();
        if(notifiees()) for(NotifieeIterator n=notifieeIter(); n.ptr(); ++n) try {
                    n->onLocationDel(p);
                    if( ver != notifiee_.version() ) goto retrycell;
                } catch(...) {
                    n->onNotificationException(NotifieeConst::location__);
                }
    } catch (...) {}
}

void Engine::segmentIs(Segment::Ptr s)
{
    string name = s->name();
    Segment::Ptr m = segment_[name];
    if(m != NULL ) {
        throw Fwk::NameInUseException(name);
    } else {
        m = s;
        segment_.newMember(m);
        if (stats_ != NULL) {
            if (!expreactor_)
                expreactor_ = Stats::SegmentExpediteReactor::SegmentExpediteReactorIs(s, this);
            s->newNotifiee(expreactor_);
        }
    }
retrycell:
    U32 ver = notifiee_.version();
    if(notifiees()) for(NotifieeIterator n=notifieeIter(); n.ptr(); ++n) try {
                n->onSegmentIs(s);
                if( ver != notifiee_.version() ) goto retrycell;
            } catch(...) {
                n->onNotificationException(NotifieeConst::segment__);
            }
}

void Engine::segmentDel(const string& s)
{
    try {
        Segment::Ptr p = segment_[s];
        p->returnSegment()->returnSegmentIs(NULL);
        segment_.memberDel(s);

retrycell:
        U32 ver = notifiee_.version();
        if(notifiees()) for(NotifieeIterator n=notifieeIter(); n.ptr(); ++n) try {
                    n->onSegmentDel(p);
                    if( ver != notifiee_.version() ) goto retrycell;
                } catch(...) {
                    n->onNotificationException(NotifieeConst::location__);
                }
    } catch (...) {}
}

Engine::NotifieeConst::~NotifieeConst()
{
    if(notifier_ != NULL ) {
        notifier_->deleteNotifiee(this);
    }
    if(notifier_ != NULL &&isNonReferencing()) notifier_->newRef();
}

void
Engine::NotifieeConst::notifierIs(const Engine::PtrConst& _notifier)
{
    Engine::Ptr notifierSave(const_cast<Engine *>(notifier_.ptr()));
    if(_notifier==notifier_) return;
    notifier_ = _notifier;
    if(notifierSave != NULL ) {
        notifierSave->deleteNotifiee(this);
    }
    if(_notifier != NULL ) {
        _notifier->newNotifiee(this);
    }
    if(isNonReferencing_) {
        if(notifierSave != NULL ) notifierSave->newRef();
        if(notifier_ != NULL ) notifier_->deleteRef();
    }
}

void
Engine::NotifieeConst::isNonReferencingIs(bool _isNonReferencing)
{
    if(_isNonReferencing==isNonReferencing_) return;
    isNonReferencing_ = _isNonReferencing;
    if(notifier_ != NULL ) {
        if(_isNonReferencing) notifier_->deleteRef();
        else notifier_->newRef();
    }
}

void Engine::statsIs(Stats::Ptr s)
{
    stats_ = s;
    if (stats_ != NULL)
        slreactor_ = Stats::LocationSegmentReactor::LocationSegmentReactorIs(this);
}

Fwk::String valueToStrep(string s)
{
    return s;
}

Engine::Engine() : expreactor_(NULL), slreactor_(NULL), sshipreactor_(NULL), 
		conn_(NULL), fleet_(NULL), stats_(NULL) {
}

Stats::~Stats()
{
}

Stats::Stats( const string& _name, Fwk::Ptr<Engine> _engine) :
    NamedInterface(_name), engine_(_engine), customer_(0),
    port_(0), truckTerminal_(0), boatTerminal_(0),
    planeTerminal_(0), boatSegment_(0), truckSegment_(0),
    planeSegment_(0), expedite_(0)
{
	if (engine_)
		engine_->statsIs(this);
}

Fleet::Fleet( const string& _name, Fwk::Ptr<Engine> _engine ) :
        NamedInterface(_name), engine_(_engine) {
		if (engine_)
			engine_->fleetIs(this);
        fleet_[Segment::boat()] = fleetInfo();
        fleet_[Segment::truck()] = fleetInfo();
        fleet_[Segment::plane()] = fleetInfo();
}
