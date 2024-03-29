#ifndef SHIPPINGTYPES
#define SHIPPINGTYPES

#include <limits.h>
#include <float.h>
#include <sstream>
#include <iomanip>
#include <queue>
#include <string>
#include "Nominal.h"
#include "Activity.h"

namespace Shipping
{

class Mile : public Ordinal<Mile, double>
{
public:
    Mile( double num ) : Ordinal<Mile, double>(num) {
        if (num < 0.0) throw Fwk::RangeException("Miles must be non-negative.");
    }
    operator std::string() const {
        std::ostringstream oss;
        oss << std::fixed;
        oss << std::setprecision (2) << value();
        return oss.str();
    }

    friend std::ostream& operator<< (std::ostream& out, Mile val) {
        out << std::string(val);
        return out;
    }
    friend std::istream& operator>> (std::istream& in, Mile& val) {
		double d;
        in >> d;
		val.value_ = d;
        return in;
    }
    static Mile max() {
        Mile m( DBL_MAX );
        return m;
    }
};

class Difficulty : public Ordinal<Difficulty, double>
{
public:
    Difficulty( double num ) : Ordinal<Difficulty, double>(num) {
        if (num < 1.0 || num > 5.0) throw Fwk::RangeException("Difficulty must be between 1 and 5.");
    }
    operator std::string() const {
        std::ostringstream oss;
        oss << std::fixed;
        oss << std::setprecision (2) << value();
        return oss.str();
    }

    friend std::ostream& operator<< (std::ostream& out, Difficulty val) {
        out << std::string(val);
        return out;
    }
    friend std::istream& operator>> (std::istream& in, Difficulty& val) {
		double d;
        in >> d;
		val.value_ = d;
        return in;
    }
};

class NumPackages : public Ordinal<NumPackages, unsigned int>
{
public:
    NumPackages( unsigned int num ) : Ordinal<NumPackages, unsigned int>(num) {
        if (num < 0.0) throw Fwk::RangeException("NumPackages must be non-negative");
    }
    operator std::string() const {
        std::ostringstream oss;
        oss << value();
        return oss.str();
    }

    friend std::ostream& operator<< (std::ostream& out, NumPackages val) {
        out << std::string(val);
        return out;
    }

    friend std::istream& operator>> (std::istream& in, NumPackages& val) {
		unsigned int ui;
        in >> ui;
		val.value_ = ui;
        return in;
    }
};

class NumVehicles : public Ordinal<NumVehicles, unsigned int>
{
public:
    NumVehicles( unsigned int num ) : Ordinal<NumVehicles, unsigned int>(num) {
        if (num < 0.0) throw Fwk::RangeException("NumPackages must be non-negative");
    }
    operator std::string() const {
        std::ostringstream oss;
        oss << value();
        return oss.str();
    }

    friend std::ostream& operator<< (std::ostream& out, NumVehicles val) {
        out << std::string(val);
        return out;
    }

    friend std::istream& operator>> (std::istream& in, NumVehicles& val) {
		unsigned int ui;
        in >> ui;
		val.value_ = ui;
        return in;
    }
};

class Percentage : public Ordinal<Percentage, double>
{
public:
    Percentage( double num ) : Ordinal<Percentage, double>(num) {
        if (num < 0.0 || num > 100.0) throw Fwk::RangeException("Percentage must between 0 and 100.");
    }
    operator std::string() const {
        std::ostringstream oss;
        oss << std::fixed;
        oss << std::setprecision (2) << value();
        return oss.str();
    }

    friend std::ostream& operator<< (std::ostream& out, Percentage val) {
        out << std::string(val);
        return out;
    }
    friend std::istream& operator>> (std::istream& in, Percentage& val) {
		double d;
        in >> d;
		val.value_ = d;
        return in;
    }
};

class Mph : public Ordinal<Mph, double>
{
public:
    Mph( double num ) : Ordinal<Mph, double>(num) {
        if (num < 0.0) throw Fwk::RangeException("Mph must be non-negative");
    }
    operator std::string() const {
        std::ostringstream oss;
        oss << std::fixed;
        oss << std::setprecision (2) << value();
        return oss.str();
    }

    friend std::ostream& operator<< (std::ostream& out, Mph val) {
        out << std::string(val);
        return out;
    }
    friend std::istream& operator>> (std::istream& in, Mph& val) {
		double d;
        in >> d;
		val.value_ = d;
        return in;
    }
};

class ShipmentsPerDay : public Ordinal<ShipmentsPerDay, unsigned int>
{
public:
    ShipmentsPerDay( unsigned int num ) : Ordinal<ShipmentsPerDay, unsigned int>(num) {}
    operator std::string() const {
        std::ostringstream oss;
        oss << value();
        return oss.str();
    }

    friend std::ostream& operator<< (std::ostream& out, ShipmentsPerDay val) {
        out << std::string(val);
        return out;
    }

    friend std::istream& operator>> (std::istream& in, ShipmentsPerDay& val) {
		unsigned int ui;
        in >> ui;
		val.value_ = ui;
        return in;
    }
};

class Dollar : public Ordinal<Dollar, double>
{
public:
    Dollar( double num ) : Ordinal<Dollar, double>(num) {
        if (num < 0.0) throw Fwk::RangeException("Dollar value must be non-negative");
    }
    operator std::string() const {
        std::ostringstream oss;
        oss << std::fixed;
        oss << std::setprecision (2) << value();
        return oss.str();
    }

    friend std::ostream& operator<< (std::ostream& out, Dollar val) {
        out << std::string(val);
        return out;
    }
    friend std::istream& operator>> (std::istream& in, Dollar& val) {
		double d;
        in >> d;
		val.value_ = d;
        return in;
    }
    static Dollar max() {
        Dollar m( DBL_MAX );
        return m;
    }
};

class Hour : public Ordinal<Hour, double >
{
public:
    Hour( double num ) : Ordinal<Hour, double>(num) {
        if (num < 0.0) throw Fwk::RangeException("Hour must be non-negative.");
    }
    operator std::string() const {
        std::ostringstream oss;
        oss << std::fixed;
        oss << std::setprecision (2) << value();
        return oss.str();
    }

    friend std::ostream& operator<< (std::ostream& out, Hour val) {
        out << std::string(val);
        return out;
    }
    friend std::istream& operator>> (std::istream& in, Hour& val) {
		double d;
        in >> d;
		val.value_ = d;
        return in;
    }
    static Hour max() {
        Hour m( DBL_MAX );
        return m;
    }
};

class Shipment : public Fwk::NamedInterface
{
public:
    typedef Fwk::Ptr<Shipment const> PtrConst;
    typedef Fwk::Ptr<Shipment> Ptr;
    
    static Shipment::Ptr ShipmentNew(const std::string& name, 
			const std::string& sourceName, 
			const std::string& destinationName, NumPackages origSize,
			NumPackages load, Time timeShipped) {
        Ptr m = new Shipment(name, sourceName, destinationName, origSize, load, timeShipped);
        m->referencesDec(1);
        return m;
    }
            
    std::string source() { return source_; }
    void sourceIs(const std::string& source) { source_ = source; }

    std::string destination() { return destination_; }
    void destinationIs(const std::string& destination) { destination_ = destination; }

    NumPackages load() { return load_; }
    void loadIs(NumPackages load) { load_ = load; }

    NumPackages origSize() { return origSize_; }
    
    Dollar cost() { return cost_; }
    void costIs(Dollar cost) { cost_ = cost; }

    Time timeShipped() { return timeShipped_; }

protected:
    Shipment(const std::string& name, const std::string& sourceName, 
		const std::string& destinationName, NumPackages origSize, NumPackages load, Time timeShipped ) :
            Fwk::NamedInterface(name), origSize_(origSize), load_(load), source_(sourceName), 
            destination_(destinationName), cost_(0), timeShipped_( timeShipped ) {}
    Shipment(const Shipment&);

    NumPackages origSize_;
    NumPackages load_;
    std::string source_;
    std::string destination_;
    Dollar cost_;
    Time timeShipped_;
};

typedef std::deque<Shipment::Ptr> ShipmentQueue;

} /* end namespace */

#endif
