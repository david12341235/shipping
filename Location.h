#ifndef LOCATION_H
#define LOCATION_H

#include <string>
#include <queue>
#include "fwk/Ptr.h"
#include "fwk/NamedInterface.h"
#include "ShippingTypes.h"
#include "Engine.h"

using namespace std;

namespace Shipping
{

class Engine;

class Location : public Fwk::NamedInterface
{
public:
    typedef Fwk::Ptr<Location const> PtrConst;
    typedef Fwk::Ptr<Location> Ptr;

    Fwk::String fwkKey() const {
        return this->name();
    }
    Location const * fwkHmNext() const {
        return fwkHmNext_.ptr();
    }
    Location * fwkHmNext() {
        return fwkHmNext_.ptr();
    }
    Location const * fwkPtr() const {
        return this;
    }
    Location * fwkPtr() {
        return this;
    }
    void fwkHmNextIs(Location * _fwkHmNext) const {
        fwkHmNext_ = _fwkHmNext;
    }
    Location::PtrConst fwkValue() const {
        return this;
    }
    Location::Ptr fwkValue() {
        return this;
    }

    enum Type {
        customer_ = 0,
        port_ = 1,
        truck_ = 2,
        boat_ = 3,
        plane_ = 4,
    };
    static inline Type customer() {
        return customer_;
    }
    static inline Type port() {
        return port_;
    }
    static inline Type truck() {
        return truck_;
    }
    static inline Type boat() {
        return boat_;
    }
    static inline Type plane() {
        return plane_;
    }

    static Type TypeInstance( Fwk::String );
    Type type() const {
        return type_;
    }
    virtual void typeIs( Type _type ) {
        type_ = _type;
    }
    Segment::PtrConst segment( Segment::SegmentId _segmentId ) const {
        return _segmentId > (int)segment_.size() ? Segment::PtrConst(NULL) : segment_.at(_segmentId-1);
    };
    virtual void segmentIs( Segment::PtrConst  _segment ) {
        segment_.push_back(_segment);
    };
    void segmentDel( Segment::PtrConst _segment );
	virtual void shipmentIs(Shipment::Ptr _newShipment);

    void nextSegmentIs( string _destination, Segment::Ptr _nextSeg ) { nextSegment_[_destination] = _nextSeg; }

	Segment::Ptr nextSegment( string _destination )
	{
		// will return a pointer to the next segment
		return nextSegment_[_destination];
	}

    class NotifieeConst : public virtual Fwk::NamedInterface::NotifieeConst
    {
    public:
        typedef Fwk::Ptr<NotifieeConst const> PtrConst;
        typedef Fwk::Ptr<NotifieeConst> Ptr;
        string name() const {
            return notifier_->name();
        }
        Location::PtrConst notifier() const {
            return notifier_;
        }
        static const AttributeId location__ = AttributeId(Fwk::NamedInterface::NotifieeConst::tacNextAttributeId__);
        static const AttributeId tacNextAttributeId__ = AttributeId(location__+1);
        bool isNonReferencing() const {
            return isNonReferencing_;
        }
        NotifieeConst const * lrNext() const {
            return lrNext_;
        }
        NotifieeConst * lrNext() {
            return lrNext_;
        }

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

    class Notifiee : public virtual NotifieeConst, public virtual Fwk::NamedInterface::Notifiee
    {
    public:
        typedef Fwk::Ptr<Notifiee const> PtrConst;
        typedef Fwk::Ptr<Notifiee> Ptr;
        Location::Ptr notifier() {
            return const_cast<Location *>(NotifieeConst::notifier().ptr());
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
    ~Location() {};

    static Location::Ptr LocationNew( const string& _name, Type _type, Fwk::Ptr<Engine> _engine ) {
        Ptr m = new Location( _name, _type, _engine );
        m->referencesDec(1);
        return m;
    }
    typedef NotifieeList::Iterator NotifieeIterator;
    NotifieeIterator notifieeIter() {
        return notifiee_.iterator();
    }
    virtual void newNotifiee( Location::NotifieeConst * n ) const {
        Location* me = const_cast<Location*>(this);
        me->notifiee_.newMember(n);
    }
    virtual void deleteNotifiee( Location::NotifieeConst * n ) const {
        Location* me = const_cast<Location*>(this);
        me->notifiee_.deleteMember(n);
    }

protected:
    typedef vector<Segment::PtrConst > SegmentList;
    typedef map<string, Segment::Ptr > routeTable;
    mutable Location::Ptr fwkHmNext_;
    Location( const Location& );
    Location( const string& _name, Type _type, Fwk::Ptr<Engine> _engine );
    Location( const string& _name, Type _type);
    Type type_;
    Fwk::Ptr<Engine> engine_;
    SegmentList segment_;
    NotifieeList notifiee_;
    void onZeroReferences();
    routeTable nextSegment_;

};

class Customer : public Location
{
public:
    typedef Fwk::Ptr<Customer const> PtrConst;
    typedef Fwk::Ptr<Customer> Ptr;

    Type type() const {
        return Location::customer();
    }
    virtual void typeIs( Type v ) {}
	
	virtual ShipmentsPerDay transferRate() const { return transferRate_; }
	virtual void transferRateIs(ShipmentsPerDay _transferRate);

	virtual NumPackages shipmentSize() const { return shipmentSize_; }
	virtual void shipmentSizeIs(NumPackages _shipmentSize);

	virtual string destination() const { return destination_; }
	virtual void destinationIs(string _destination);
	
	virtual bool sendingShipments() const { return sendingShipments_; }
	virtual void sendingShipmentsIs(bool _sendingShipments);
    
	virtual NumPackages shipmentsReceived() const { return shipmentsReceived_; }
	virtual Hour averageLatency() const { return totalLatency_.value() / (1.0) * shipmentsReceived().value(); }
	virtual Dollar totalCost() const { return totalCost_; }

	virtual void shipmentIs(Shipment::Ptr _newShipment);

    class NotifieeConst : public Location::NotifieeConst, public virtual Fwk::NamedInterface::NotifieeConst
    {
    public:
        typedef Fwk::Ptr<NotifieeConst const> PtrConst;
        typedef Fwk::Ptr<NotifieeConst> Ptr;
        string name() const {
            return notifier_->name();
        }
        Customer::PtrConst notifier() const {
            return notifier_;
        }
        static const AttributeId customer__ = AttributeId(Fwk::NamedInterface::NotifieeConst::tacNextAttributeId__);
        static const AttributeId tacNextAttributeId__ = AttributeId(customer__+1);
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
        virtual void notifierIs(const Customer::PtrConst& _notifier);
        void isNonReferencingIs(bool _isNonReferencing) {
            isNonReferencing_ = _isNonReferencing;
        };
        virtual void onSendingShipmentsIs(Customer::Ptr c) {}

        static NotifieeConst::Ptr NotifieeConstIs() {
            Ptr m = new NotifieeConst();
            m->referencesDec(1);
            return m;
        }
    protected:
        Customer::PtrConst notifier_;

        bool isNonReferencing_;
        NotifieeConst* lrNext_;
        NotifieeConst(): Fwk::NamedInterface::NotifieeConst(),
            lrNext_(0) { }
    };
	
    class Notifiee : public virtual Location::NotifieeConst, public virtual Fwk::NamedInterface::Notifiee
    {
    public:
        typedef Fwk::Ptr<Notifiee const> PtrConst;
        typedef Fwk::Ptr<Notifiee> Ptr;
        Customer::Ptr notifier() {
            return const_cast<Customer*>(Notifiee::notifier().ptr());
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

    virtual void newNotifiee( Customer::NotifieeConst * n ) const {
        Customer* me = const_cast<Customer*>(this);
        me->notifiee_.newMember(n);
    }
    virtual void deleteNotifiee( Customer::NotifieeConst * n ) const {
        Customer* me = const_cast<Customer*>(this);
        me->notifiee_.deleteMember(n);
    }

    static Customer::Ptr CustomerNew( const string& _name, Fwk::Ptr<Engine> _engine ) {
        Ptr m = new Customer( _name, _engine );
        m->referencesDec(1);
        return m;
    }

protected:
    Customer( const Customer& );
    Customer( const string& _name, Fwk::Ptr<Engine> _engine );
	ShipmentsPerDay transferRate_;
	NumPackages shipmentSize_;
	NumPackages shipmentsReceived_;
	string destination_;
	bool sendingShipments_;
    Hour totalLatency_;
    Dollar totalCost_;
    map< string, NumPackages > shipmentsPending_;
    NotifieeList notifiee_;
};

class Port : public Location
{
public:
    typedef Fwk::Ptr<Port const> PtrConst;
    typedef Fwk::Ptr<Port> Ptr;

    Type type() const {
        return Location::port();
    }
    virtual void typeIs( Type v ) {}
//	virtual void segmentIs( Segment const* _segment );

    class NotifieeConst : public virtual Location::NotifieeConst
    {
    public:
        typedef Fwk::Ptr<NotifieeConst const> PtrConst;
        typedef Fwk::Ptr<NotifieeConst> Ptr;
        string name() const {
            return notifier_->name();
        }
        Port::PtrConst notifier() const {
            return dynamic_cast<Port const *>(Location::NotifieeConst::notifier().ptr());
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
        Port::PtrConst notifier_;

        NotifieeConst* lrNext_;
        NotifieeConst(): Location::NotifieeConst(),
            lrNext_(0) { }
    };

    class Notifiee : public virtual NotifieeConst, public virtual Location::Notifiee
    {
    public:
        typedef Fwk::Ptr<Notifiee const> PtrConst;
        typedef Fwk::Ptr<Notifiee> Ptr;
        Port::PtrConst notifier() const {
            return dynamic_cast<Port const *>(Location::NotifieeConst::notifier().ptr());
        }
        Port::Ptr notifier() {
            return dynamic_cast<Port * >(const_cast<Location *>(Location::NotifieeConst::notifier().ptr()));
        }

        static Notifiee::Ptr NotifieeIs() {
            Ptr m = new Notifiee();
            m->referencesDec(1);
            return m;
        }
    protected:
        Notifiee(): Location::Notifiee() { }
    };

    static Port::Ptr PortNew( const string& _name, Fwk::Ptr<Engine> _engine ) {
        Ptr m = new Port( _name, _engine );
        m->referencesDec(1);
        return m;
    }

protected:
    Port( const Port& );
    Port( const string& _name, Fwk::Ptr<Engine> _engine ) : Location( _name, port_, _engine ) {};
};

class TruckLocation : public Location
{
public:
    typedef Fwk::Ptr<TruckLocation const> PtrConst;
    typedef Fwk::Ptr<TruckLocation> Ptr;

    Type type() const {
        return Location::truck();
    }
    virtual void typeIs( Type v ) {}
//	virtual void segmentIs( Segment const* _segment );

    class NotifieeConst : public virtual Location::NotifieeConst
    {
    public:
        typedef Fwk::Ptr<NotifieeConst const> PtrConst;
        typedef Fwk::Ptr<NotifieeConst> Ptr;
        string name() const {
            return notifier_->name();
        }
        TruckLocation::PtrConst notifier() const {
            return dynamic_cast<TruckLocation const *>(Location::NotifieeConst::notifier().ptr());
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
        TruckLocation::PtrConst notifier_;

        NotifieeConst* lrNext_;
        NotifieeConst(): Location::NotifieeConst(),
            lrNext_(0) { }
    };

    class Notifiee : public virtual NotifieeConst, public virtual Location::Notifiee
    {
    public:
        typedef Fwk::Ptr<Notifiee const> PtrConst;
        typedef Fwk::Ptr<Notifiee> Ptr;
        TruckLocation::PtrConst notifier() const {
            return dynamic_cast<TruckLocation const *>(Location::NotifieeConst::notifier().ptr());
        }
        TruckLocation::Ptr notifier() {
            return dynamic_cast<TruckLocation * >(const_cast<Location *>(Location::NotifieeConst::notifier().ptr()));
        }

        static Notifiee::Ptr NotifieeIs() {
            Ptr m = new Notifiee();
            m->referencesDec(1);
            return m;
        }
    protected:
        Notifiee(): Location::Notifiee() { }
    };

    static TruckLocation::Ptr TruckLocationNew( const string& _name, Fwk::Ptr<Engine> _engine ) {
        Ptr m = new TruckLocation( _name, _engine );
        m->referencesDec(1);
        return m;
    }

protected:
    TruckLocation( const TruckLocation& );
    TruckLocation( const string& _name, Fwk::Ptr<Engine> _engine ) : Location( _name, truck_, _engine ) {};
};

class BoatLocation : public Location
{
public:
    typedef Fwk::Ptr<BoatLocation const> PtrConst;
    typedef Fwk::Ptr<BoatLocation> Ptr;

    Type type() const {
        return Location::boat();
    }
    virtual void typeIs( Type v ) {}
//	virtual void segmentIs( Segment const* _segment );

    class NotifieeConst : public virtual Location::NotifieeConst
    {
    public:
        typedef Fwk::Ptr<NotifieeConst const> PtrConst;
        typedef Fwk::Ptr<NotifieeConst> Ptr;
        string name() const {
            return notifier_->name();
        }
        BoatLocation::PtrConst notifier() const {
            return dynamic_cast<BoatLocation const *>(Location::NotifieeConst::notifier().ptr());
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
        BoatLocation::PtrConst notifier_;

        NotifieeConst* lrNext_;
        NotifieeConst(): Location::NotifieeConst(),
            lrNext_(0) { }
    };

    class Notifiee : public virtual NotifieeConst, public virtual Location::Notifiee
    {
    public:
        typedef Fwk::Ptr<Notifiee const> PtrConst;
        typedef Fwk::Ptr<Notifiee> Ptr;
        BoatLocation::PtrConst notifier() const {
            return dynamic_cast<BoatLocation const *>(Location::NotifieeConst::notifier().ptr());
        }
        BoatLocation::Ptr notifier() {
            return dynamic_cast<BoatLocation * >(const_cast<Location *>(Location::NotifieeConst::notifier().ptr()));
        }

        static Notifiee::Ptr NotifieeIs() {
            Ptr m = new Notifiee();
            m->referencesDec(1);
            return m;
        }
    protected:
        Notifiee(): Location::Notifiee() { }
    };

    static BoatLocation::Ptr BoatLocationNew( const string& _name, Fwk::Ptr<Engine> _engine ) {
        Ptr m = new BoatLocation( _name, _engine );
        m->referencesDec(1);
        return m;
    }

protected:
    BoatLocation( const BoatLocation& );
    BoatLocation( const string& _name, Fwk::Ptr<Engine> _engine ) : Location( _name, boat_, _engine ) {};
};

class PlaneLocation : public Location
{
public:
    typedef Fwk::Ptr<PlaneLocation const> PtrConst;
    typedef Fwk::Ptr<PlaneLocation> Ptr;

    Type type() const {
        return Location::plane();
    }
    virtual void typeIs( Type v ) {}
//	virtual void segmentIs( Segment const* _segment );

    class NotifieeConst : public virtual Location::NotifieeConst
    {
    public:
        typedef Fwk::Ptr<NotifieeConst const> PtrConst;
        typedef Fwk::Ptr<NotifieeConst> Ptr;
        string name() const {
            return notifier_->name();
        }
        PlaneLocation::PtrConst notifier() const {
            return dynamic_cast<PlaneLocation const *>(Location::NotifieeConst::notifier().ptr());
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
        PlaneLocation::PtrConst notifier_;

        NotifieeConst* lrNext_;
        NotifieeConst(): Fwk::NamedInterface::NotifieeConst(),
            lrNext_(0) { }
    };

    class Notifiee : public virtual NotifieeConst, public virtual Location::Notifiee
    {
    public:
        typedef Fwk::Ptr<Notifiee const> PtrConst;
        typedef Fwk::Ptr<Notifiee> Ptr;
        PlaneLocation::PtrConst notifier() const {
            return dynamic_cast<PlaneLocation const *>(Location::NotifieeConst::notifier().ptr());
        }
        PlaneLocation::Ptr notifier() {
            return dynamic_cast<PlaneLocation * >(const_cast<Location *>(Location::NotifieeConst::notifier().ptr()));
        }

        static Notifiee::Ptr NotifieeIs() {
            Ptr m = new Notifiee();
            m->referencesDec(1);
            return m;
        }
    protected:
        Notifiee(): Fwk::NamedInterface::Notifiee() { }
    };

    static PlaneLocation::Ptr PlaneLocationNew( const string& _name, Fwk::Ptr<Engine> _engine ) {
        Ptr m = new PlaneLocation( _name, _engine );
        m->referencesDec(1);
        return m;
    }

protected:
    PlaneLocation( const PlaneLocation& );
    PlaneLocation( const string& _name, Fwk::Ptr<Engine> _engine ) : Location( _name, plane_, _engine ) {};
};

} // namespace

#endif
