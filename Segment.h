#ifndef SEGMENT_H
#define SEGMENT_H

#include <string>
#include "fwk/Ptr.h"
#include "fwk/NamedInterface.h"
#include "ShippingTypes.h"
#include "Engine.h"

using namespace std;

namespace Shipping
{

class Location;
class Engine;

class Segment : public Fwk::NamedInterface
{
public:
    typedef Fwk::Ptr<Segment const> PtrConst;
    typedef Fwk::Ptr<Segment> Ptr;
    Fwk::String fwkKey() const {
        return this->name();
    }
    Segment const * fwkHmNext() const {
        return fwkHmNext_.ptr();
    }
    Segment * fwkHmNext() {
        return fwkHmNext_.ptr();
    }
    Segment const * fwkPtr() const {
        return this;
    }
    Segment * fwkPtr() {
        return this;
    }
    void fwkHmNextIs(Segment * _fwkHmNext) const {
        fwkHmNext_ = _fwkHmNext;
    }
    Segment::PtrConst fwkValue() const {
        return this;
    }
    Segment::Ptr fwkValue() {
        return this;
    }
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

    static inline Mode truck() {
        return truck_;
    }
    static inline Mode boat() {
        return boat_;
    }
    static inline Mode plane() {
        return plane_;
    }
    static inline ExpVal expNo() {
        return expNo_;
    }
    static inline ExpVal expYes() {
        return expYes_;
    }
    static inline SegmentId SegmentIdInstance ( int v ) {
        return v > 0 ? (Segment::SegmentId)v : 0;
    }
    static inline Mode ModeInstance( const Fwk::String );
    static inline ExpVal ExpValInstance( const Fwk::String v ) {
        return v == "yes" ? expYes() : expNo();
    }

    Mode mode() const {
        return mode_;
    }
    virtual void modeIs( Mode v ) {
        mode_ = v;
    }

    Fwk::Ptr<Location> source() const {
        return source_;
    }
    virtual void sourceIs( Fwk::Ptr<Location> _source );

    Mile length() const {
        return length_;
    }
    void lengthIs( const Mile& _length ) {
        length_ = _length;
    }

    Ptr returnSegment() const {
        return returnSegment_;
    }
    void returnSegmentIs( Segment::Ptr _returnSegment );

    Difficulty difficulty() const {
        return difficulty_;
    }
    void difficultyIs( const Difficulty& _difficulty ) {
        difficulty_ = _difficulty;
    }

    ExpVal expedite() const {
        return expedite_;
    }
    void expediteIs( ExpVal e );
    NumPackages shipmentsReceived() { return shipmentsReceived_; }
    NumPackages shipmentsRefused() { return shipmentsRefused_; }
    NumPackages shipmentsPending() { return shipmentsPending_; }
    NumPackages capacity() { return capacity_; }
    void capacityIs( NumPackages _capacity ) { capacity_ = _capacity; }

    virtual void shipmentIs( Shipment::Ptr _newShipment );

    class NotifieeConst : public virtual Fwk::NamedInterface::NotifieeConst
    {
    public:
        typedef Fwk::Ptr<NotifieeConst const> PtrConst;
        typedef Fwk::Ptr<NotifieeConst> Ptr;
        string name() const {
            return notifier_->name();
        }
        Segment::PtrConst notifier() const {
            return notifier_;
        }
        static const AttributeId segment__ = AttributeId(Fwk::NamedInterface::NotifieeConst::tacNextAttributeId__);
        static const AttributeId tacNextAttributeId__ = AttributeId(segment__+1);
        bool isNonReferencing() const {
            return isNonReferencing_;
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
        virtual void notifierIs(const Segment::PtrConst& _notifier);
        void isNonReferencingIs(bool _isNonReferencing) {
            isNonReferencing_ = _isNonReferencing;
        };
        virtual void onSource() {}
        virtual void onLength() {}
        virtual void onReturnSegment() {}
        virtual void onDifficulty() {}
        virtual void onExpedite(Segment::Ptr s, ExpVal old) {}

        static NotifieeConst::Ptr NotifieeConstIs() {
            Ptr m = new NotifieeConst();
            m->referencesDec(1);
            return m;
        }
    protected:
        Segment::PtrConst notifier_;

        bool isNonReferencing_;
        NotifieeConst* lrNext_;
        NotifieeConst(): Fwk::NamedInterface::NotifieeConst(),
            lrNext_(0) { }
    };

    class Notifiee : public virtual NotifieeConst, public virtual Fwk::NamedInterface::Notifiee
    {
    public:
        typedef Fwk::Ptr<Notifiee const> PtrConst;
        typedef Fwk::Ptr<Notifiee> Ptr;
        Segment::PtrConst notifier() const {
            return NotifieeConst::notifier();
        }
        Segment::Ptr notifier() {
            return const_cast<Segment *>(NotifieeConst::notifier().ptr());
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
    typedef NotifieeList::Iterator NotifieeIterator;
    NotifieeIteratorConst notifieeIterConst() const {
        return notifiee_.iterator();
    }
    NotifieeIterator notifieeIter() {
        return notifiee_.iterator();
    }
    U32 notifiees() const {
        return notifiee_.members();
    }
    ~Segment() {}

    static Segment::Ptr SegmentNew( const string& _name, Mode _mode, Fwk::Ptr<Engine> _engine ) {
        Ptr m = new Segment( _name, _mode, _engine );
        m->referencesDec(1);
        return m;
    }

    void newNotifiee( Segment::NotifieeConst * n ) const {
        Segment* me = const_cast<Segment*>(this);
        me->notifiee_.newMember(n);
    }
    void deleteNotifiee( Segment::NotifieeConst * n ) const {
        Segment* me = const_cast<Segment*>(this);
        me->notifiee_.deleteMember(n);
    }

protected:
    Segment( const Segment& );
    Segment( const string& _name, Mode _mode, Fwk::Ptr<Engine> _engine );
    mutable Segment::Ptr fwkHmNext_;
    Mode mode_;
    Fwk::Ptr<Engine> engine_;
    Fwk::Ptr<Location> source_;
    Mile length_;
    Difficulty difficulty_;
    ExpVal expedite_;
    Ptr returnSegment_;
    NotifieeList notifiee_;
    NumPackages shipmentsReceived_;
    NumPackages shipmentsRefused_;
    NumPackages shipmentsPending_;
    NumPackages capacity_;
};

class TruckSegment : public Segment
{
public:
    typedef Fwk::Ptr<TruckSegment const> PtrConst;
    typedef Fwk::Ptr<TruckSegment> Ptr;

    Mode mode() const {
        return Segment::truck();
    }
    virtual void modeIs( Mode v ) {}
    virtual void sourceIs( Fwk::Ptr<Location> _source );

    class NotifieeConst : public virtual Segment::NotifieeConst
    {
    public:
        typedef Fwk::Ptr<NotifieeConst const> PtrConst;
        typedef Fwk::Ptr<NotifieeConst> Ptr;
        string name() const {
            return notifier_->name();
        }
        TruckSegment::PtrConst notifier() const {
            return dynamic_cast<TruckSegment const *>(Segment::NotifieeConst::notifier().ptr());
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

        static NotifieeConst::Ptr NotifieeConstIs() {
            Ptr m = new NotifieeConst();
            m->referencesDec(1);
            return m;
        }
    protected:
        TruckSegment::PtrConst notifier_;

        NotifieeConst* lrNext_;
        NotifieeConst(): Segment::NotifieeConst(),
            lrNext_(0) { }
    };

    class Notifiee : public virtual NotifieeConst, public virtual Segment::Notifiee
    {
    public:
        typedef Fwk::Ptr<Notifiee const> PtrConst;
        typedef Fwk::Ptr<Notifiee> Ptr;
        TruckSegment::PtrConst notifier() const {
            return dynamic_cast<TruckSegment const *>(Segment::NotifieeConst::notifier().ptr());
        }
        TruckSegment::Ptr notifier() {
            return dynamic_cast<TruckSegment * >(const_cast<Segment *>(Segment::NotifieeConst::notifier().ptr()));
        }

        static Notifiee::Ptr NotifieeIs() {
            Ptr m = new Notifiee();
            m->referencesDec(1);
            return m;
        }
    protected:
        Notifiee(): Segment::Notifiee() { }
    };

    static TruckSegment::Ptr TruckSegmentNew( const string& _name, Fwk::Ptr<Engine> _engine ) {
        Ptr m = new TruckSegment( _name, _engine );
        m->referencesDec(1);
        return m;
    }

protected:
    TruckSegment( const TruckSegment& );
    TruckSegment( const string& _name, Fwk::Ptr<Engine> _engine ) :
        Segment( _name, truck_, _engine ) {};
};

class BoatSegment : public Segment
{
public:
    typedef Fwk::Ptr<BoatSegment const> PtrConst;
    typedef Fwk::Ptr<BoatSegment> Ptr;

    Mode mode() const {
        return Segment::truck();
    }
    virtual void modeIs( Mode v ) {}
    virtual void sourceIs( Fwk::Ptr<Location> _source );

    class NotifieeConst : public virtual Segment::NotifieeConst
    {
    public:
        typedef Fwk::Ptr<NotifieeConst const> PtrConst;
        typedef Fwk::Ptr<NotifieeConst> Ptr;
        string name() const {
            return notifier_->name();
        }
        BoatSegment::PtrConst notifier() const {
            return dynamic_cast<BoatSegment const *>(Segment::NotifieeConst::notifier().ptr());
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

        static NotifieeConst::Ptr NotifieeConstIs() {
            Ptr m = new NotifieeConst();
            m->referencesDec(1);
            return m;
        }
    protected:
        BoatSegment::PtrConst notifier_;

        NotifieeConst* lrNext_;
        NotifieeConst(): Segment::NotifieeConst(),
            lrNext_(0) { }
    };

    class Notifiee : public virtual NotifieeConst, public virtual Segment::Notifiee
    {
    public:
        typedef Fwk::Ptr<Notifiee const> PtrConst;
        typedef Fwk::Ptr<Notifiee> Ptr;
        BoatSegment::PtrConst notifier() const {
            return dynamic_cast<BoatSegment const *>(Segment::NotifieeConst::notifier().ptr());
        }
        BoatSegment::Ptr notifier() {
            return dynamic_cast<BoatSegment * >(const_cast<Segment *>(Segment::NotifieeConst::notifier().ptr()));
        }

        static Notifiee::Ptr NotifieeIs() {
            Ptr m = new Notifiee();
            m->referencesDec(1);
            return m;
        }
    protected:
        Notifiee(): Segment::Notifiee() { }
    };

    static BoatSegment::Ptr BoatSegmentNew( const string& _name, Fwk::Ptr<Engine> _engine ) {
        Ptr m = new BoatSegment( _name, _engine );
        m->referencesDec(1);
        return m;
    }

protected:
    BoatSegment( const BoatSegment& );
    BoatSegment( const string& _name, Fwk::Ptr<Engine> _engine ) : Segment( _name, boat_, _engine ) {}
};

class PlaneSegment : public Segment
{
public:
    typedef Fwk::Ptr<PlaneSegment const> PtrConst;
    typedef Fwk::Ptr<PlaneSegment> Ptr;

    Mode mode() const {
        return Segment::truck();
    }
    virtual void modeIs( Mode v ) {}
    virtual void sourceIs( Fwk::Ptr<Location> _source );

    class NotifieeConst : public virtual Segment::NotifieeConst
    {
    public:
        typedef Fwk::Ptr<NotifieeConst const> PtrConst;
        typedef Fwk::Ptr<NotifieeConst> Ptr;
        string name() const {
            return notifier_->name();
        }
        PlaneSegment::PtrConst notifier() const {
            return dynamic_cast<PlaneSegment const *>(Segment::NotifieeConst::notifier().ptr());
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

        static NotifieeConst::Ptr NotifieeConstIs() {
            Ptr m = new NotifieeConst();
            m->referencesDec(1);
            return m;
        }
    protected:
        PlaneSegment::PtrConst notifier_;

        NotifieeConst* lrNext_;
        NotifieeConst(): Segment::NotifieeConst(),
            lrNext_(0) { }
    };

    class Notifiee : public virtual NotifieeConst, public virtual Segment::Notifiee
    {
    public:
        typedef Fwk::Ptr<Notifiee const> PtrConst;
        typedef Fwk::Ptr<Notifiee> Ptr;
        PlaneSegment::PtrConst notifier() const {
            return dynamic_cast<PlaneSegment const *>(Segment::NotifieeConst::notifier().ptr());
        }
        PlaneSegment::Ptr notifier() {
            return dynamic_cast<PlaneSegment * >(const_cast<Segment *>(Segment::NotifieeConst::notifier().ptr()));
        }

        static Notifiee::Ptr NotifieeIs() {
            Ptr m = new Notifiee();
            m->referencesDec(1);
            return m;
        }
    protected:
        Notifiee(): Segment::Notifiee() { }
    };

    static PlaneSegment::Ptr PlaneSegmentNew( const string& _name, Fwk::Ptr<Engine> _engine ) {
        Ptr m = new PlaneSegment( _name, _engine );
        m->referencesDec(1);
        return m;
    }

protected:
    PlaneSegment( const PlaneSegment& );
    PlaneSegment( const string& _name, Fwk::Ptr<Engine> _engine ) : Segment( _name, plane_, _engine ) {}
};

} // namespace Shipping

#endif
