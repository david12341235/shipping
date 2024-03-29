#ifndef CONN_H
#define CONN_H

#include <string>
#include "fwk/Ptr.h"
#include "fwk/NamedInterface.h"
#include "ShippingTypes.h"
#include "Engine.h"

using namespace std;

namespace Shipping
{

class Conn : public Fwk::NamedInterface
{
public:
    typedef Fwk::Ptr<Conn const> PtrConst;
    typedef Fwk::Ptr<Conn> Ptr;

    enum Type {
        explore_ = 0,
        connect_ = 1
    };
    
    enum Algorithm {
    		dijkstra_ = 0,
		bfs_ = 1
    };

    struct PathUnit {
        string output() const;

        Fwk::Ptr<Location const> location_;
        Fwk::Ptr<Segment const> segment_;
        Dollar cost_;
        Mile distance_;
        Hour time_;
        Segment::ExpVal expVal_;
        PathUnit() : location_(NULL), segment_(NULL) , cost_(0), distance_(0), time_(0), expVal_(Segment::expNo()) {}
    };

    static inline Type explore() {
        return explore_;
    }
    static inline Type connect() {
        return connect_;
    }
    static inline Algorithm dijkstra() {
    		return dijkstra_;
    }
    static inline Algorithm bfs() {
    		return bfs_;
    }
    static inline string exploreString() {
        return "explore";
    }
    static inline string connectString() {
        return "connect";
    }
    static inline string distanceString() {
        return "distance";
    }
    static inline string costString() {
        return "cost";
    }
    static inline string timeString() {
        return "time";
    }
    static inline string expeditedString() {
        return "expedited";
    }

    static Type TypeInstance( Fwk::String );

    Mile distance() const {
        return distance_;
    }
    void distanceIs( Mile _distance ) {
        distance_ = _distance;
    }

    Dollar cost() const {
        return cost_;
    }
    void costIs( Dollar _cost ) {
        cost_ = _cost;
    }

    Hour time() const {
        return time_;
    }
    void timeIs( Hour _time ) {
        time_ = _time;
    }

    Segment::ExpVal expedited() const {
        return expedited_;
    }
    void expeditedIs( Segment::ExpVal _expedited ) {
        expedited_ = _expedited;
    }

    Type queryType() const {
        return queryType_;
    }
    void queryTypeIs( Type _queryType ) {
        queryType_ = _queryType;
    }

    Fwk::Ptr<Location> startLocation() const {
        return startLocation_;
    }
    void startLocationIs(const Fwk::String& name );
    Fwk::Ptr<Location> endLocation() const {
        return endLocation_;
    }
    void endLocationIs(const Fwk::String& name );

	bool simulationStarted() { return simulationStarted_; }
	void simulationStartedIs( bool _simulationStarted );
    Algorithm algorithm() const { return algorithm_; }
    void algorithmIs( Algorithm _algorithm ) { algorithm_ = _algorithm; }

    string value();

    Fwk::Ptr<Engine> engine() const {
        return engine_;
    };
    void engineIs(Fwk::Ptr<Engine> e) {
        engine_ = e;
    };

    class NotifieeConst : public virtual Fwk::NamedInterface::NotifieeConst
    {
    public:
        typedef Fwk::Ptr<NotifieeConst const> PtrConst;
        typedef Fwk::Ptr<NotifieeConst> Ptr;
        string name() const {
            return notifier_->name();
        }
        Conn::PtrConst notifier() const {
            return notifier_;
        }
        NotifieeConst const * lrNext() const {
            return lrNext_;
        }
        NotifieeConst * lrNext() {
            return lrNext_;
        }
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

    class Notifiee : public virtual NotifieeConst, public virtual Fwk::NamedInterface::Notifiee
    {
    public:
        typedef Fwk::Ptr<Notifiee const> PtrConst;
        typedef Fwk::Ptr<Notifiee> Ptr;
        Conn::PtrConst notifier() const {
            return NotifieeConst::notifier();
        }
        Conn::Ptr notifier() {
            return const_cast<Conn *>(NotifieeConst::notifier().ptr());
        }

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
    NotifieeIteratorConst notifieeIterConst() const {
        return notifiee_.iterator();
    }
    U32 notifiees() const {
        return notifiee_.members();
    }
    ~Conn() {};

    static Conn::Ptr ConnNew( const string& _name, Fwk::Ptr<Engine> _engine ) {
        Ptr m = new Conn( _name, _engine );
        m->referencesDec(1);
        return m;
    }

protected:
    Conn( const Conn& );
    Conn( const string& _name);
    Conn( const string& _name, Fwk::Ptr<Engine> _engine );
    NotifieeList notifiee_;
    Fwk::Ptr<Engine> engine_;
    Mile distance_;
    Dollar cost_;
    Hour time_;
    bool simulationStarted_;
    Segment::ExpVal expedited_;
    Type queryType_;
    Fwk::Ptr<Location> startLocation_;
    Fwk::Ptr<Location> endLocation_;

private:
    void paths(Fwk::Ptr<Location const> cur, vector< vector<PathUnit> >& path, vector<PathUnit> workingPath, Segment::ExpVal _expVal);
    Algorithm algorithm_;

};

} // namespace Shipping

#endif
