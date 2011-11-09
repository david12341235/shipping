#ifndef SHIPPINGTYPES
#define SHIPPINGTYPES

#include <limits.h>
#include <float.h>
#include <sstream>

namespace Shipping {

class Mile : public Ordinal<Mile, unsigned int> {
public:
	Mile( unsigned int num ) : Ordinal<Mile, unsigned int>(num) {}
	operator string() const { std::ostringstream oss; oss << value(); return oss.str(); };
	static Mile max() { Mile m( UINT_MAX ); return m; }
};

class Difficulty : public Ordinal<Difficulty, double> {
public:
	Difficulty( double num ) : Ordinal<Difficulty, double>(num) {
		if (num < 0.0) throw Fwk::RangeException("Difficulty must be non-negative");
	}
	operator string() const { std::ostringstream oss; oss << value(); return oss.str(); };
};

class NumPackages : public Ordinal<NumPackages, unsigned int> {
public:
	NumPackages( unsigned int num ) : Ordinal<NumPackages, unsigned int>(num) {
		if (num < 0.0) throw Fwk::RangeException("NumPackages must be non-negative");
	}
	operator string() const { std::ostringstream oss; oss << value(); return oss.str(); };
};

class Percentage : public Ordinal<Percentage, double> {
public:
	Percentage( double num ) : Ordinal<Percentage, double>(num) {
		if (num < 0.0 || num > 100.0) throw Fwk::RangeException("Percentage must between 0 and 100.");
	}
	operator string() const { std::ostringstream oss; oss << value(); return oss.str(); };
};

class Mph : public Ordinal<Mph, double> {
public:
	Mph( double num ) : Ordinal<Mph, double>(num) {
		if (num < 0.0) throw Fwk::RangeException("Mph must be non-negative");
	}
	operator string() const { std::ostringstream oss; oss << value(); return oss.str(); };
};

class Dollar : public Ordinal<Dollar, double> {
public:
	Dollar( double num ) : Ordinal<Dollar, double>(num) {
		if (num < 0.0) throw Fwk::RangeException("Dollar value must be non-negative");
	}
	operator string() const { std::ostringstream oss; oss << value(); return oss.str(); };
	static Dollar max() { Dollar m( DBL_MAX ); return m; }
};

class Hour : public Ordinal<Hour, double > {
public:
	Hour( double num ) : Ordinal<Hour, double>(num) {
		if (num < 0.0) throw Fwk::RangeException("Hour must be non-negative.");
	}
	operator string() const { std::ostringstream oss; oss << value(); return oss.str(); };
	static Hour max() { Hour m( DBL_MAX ); return m; }
};

} /* end namespace */

#endif
