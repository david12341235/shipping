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
	Difficulty( double num ) : Ordinal<Difficulty, double>(num) {}
	operator string() const { std::ostringstream oss; oss << value(); return oss.str(); };
};

class NumPackages : public Ordinal<NumPackages, double> {
public:
	NumPackages( double num ) : Ordinal<NumPackages, double>(num) {}
	operator string() const { std::ostringstream oss; oss << value(); return oss.str(); };
};

class Percentage : public Ordinal<Percentage, double> {
public:
	Percentage( double num ) : Ordinal<Percentage, double>(num) {}
	operator string() const { std::ostringstream oss; oss << value(); return oss.str(); };
};

class Mph : public Ordinal<Mph, double> {
public:
	Mph( double num ) : Ordinal<Mph, double>(num) {}
	operator string() const { std::ostringstream oss; oss << value(); return oss.str(); };
};

class Dollar : public Ordinal<Dollar, unsigned int> {
public:
	Dollar( unsigned int num ) : Ordinal<Dollar, unsigned int>(num) {}
	operator string() const { std::ostringstream oss; oss << value(); return oss.str(); };
	static Dollar max() { Dollar m( UINT_MAX ); return m; }
};

class Hour : public Ordinal<Hour, unsigned int > {
public:
	Hour( unsigned int num ) : Ordinal<Hour, unsigned int>(num) {}
	operator string() const { std::ostringstream oss; oss << value(); return oss.str(); };
	static Hour max() { Hour m( UINT_MAX ); return m; }
};

} /* end namespace */

#endif
