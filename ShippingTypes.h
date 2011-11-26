#ifndef SHIPPINGTYPES
#define SHIPPINGTYPES

#include <limits.h>
#include <float.h>
#include <sstream>
#include <iomanip>

namespace Shipping
{

class Mile : public Ordinal<Mile, double>
{
public:
    Mile( double num ) : Ordinal<Mile, double>(num) {
        if (num < 0.0) throw Fwk::RangeException("Miles must be non-negative.");
    }
    operator string() const {
        std::ostringstream oss;
        oss << std::fixed;
        oss << std::setprecision (2) << value();
        return oss.str();
    }

    friend std::ostream& operator<< (std::ostream& out, Mile val) {
        out << string(val);
        return out;
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
    operator string() const {
        std::ostringstream oss;
        oss << std::fixed;
        oss << std::setprecision (2) << value();
        return oss.str();
    }

    friend std::ostream& operator<< (std::ostream& out, Difficulty val) {
        out << string(val);
        return out;
    }
};

class NumPackages : public Ordinal<NumPackages, unsigned int>
{
public:
    NumPackages( unsigned int num ) : Ordinal<NumPackages, unsigned int>(num) {
        if (num < 0.0) throw Fwk::RangeException("NumPackages must be non-negative");
    }
    operator string() const {
        std::ostringstream oss;
        oss << value();
        return oss.str();
    }

    friend std::ostream& operator<< (std::ostream& out, NumPackages val) {
        out << string(val);
        return out;
    }
};

class Percentage : public Ordinal<Percentage, double>
{
public:
    Percentage( double num ) : Ordinal<Percentage, double>(num) {
        if (num < 0.0 || num > 100.0) throw Fwk::RangeException("Percentage must between 0 and 100.");
    }
    operator string() const {
        std::ostringstream oss;
        oss << std::fixed;
        oss << std::setprecision (2) << value();
        return oss.str();
    }

    friend std::ostream& operator<< (std::ostream& out, Percentage val) {
        out << string(val);
        return out;
    }
};

class Mph : public Ordinal<Mph, double>
{
public:
    Mph( double num ) : Ordinal<Mph, double>(num) {
        if (num < 0.0) throw Fwk::RangeException("Mph must be non-negative");
    }
    operator string() const {
        std::ostringstream oss;
        oss << std::fixed;
        oss << std::setprecision (2) << value();
        return oss.str();
    }

    friend std::ostream& operator<< (std::ostream& out, Mph val) {
        out << string(val);
        return out;
    }
};

class ShipmentsPerDay : public Ordinal<ShipmentsPerDay, unsigned int>
{
public:
    ShipmentsPerDay( unsigned int num ) : Ordinal<ShipmentsPerDay, unsigned int>(num) {}
    operator string() const {
        std::ostringstream oss;
        oss << value();
        return oss.str();
    }

    friend std::ostream& operator<< (std::ostream& out, ShipmentsPerDay val) {
        out << string(val);
        return out;
    }
};

class Dollar : public Ordinal<Dollar, double>
{
public:
    Dollar( double num ) : Ordinal<Dollar, double>(num) {
        if (num < 0.0) throw Fwk::RangeException("Dollar value must be non-negative");
    }
    operator string() const {
        std::ostringstream oss;
        oss << std::fixed;
        oss << std::setprecision (2) << value();
        return oss.str();
    }

    friend std::ostream& operator<< (std::ostream& out, Dollar val) {
        out << string(val);
        return out;
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
    operator string() const {
        std::ostringstream oss;
        oss << std::fixed;
        oss << std::setprecision (2) << value();
        return oss.str();
    }

    friend std::ostream& operator<< (std::ostream& out, Hour val) {
        out << string(val);
        return out;
    }
    static Hour max() {
        Hour m( DBL_MAX );
        return m;
    }
};

} /* end namespace */

#endif
