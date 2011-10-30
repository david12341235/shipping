#ifndef SHIPPINGTYPES
#define SHIPPINGTYPES

namespace Shipping {

class Mile : public Ordinal<Mile, unsigned int> {
public:
	Mile( unsigned int num ) : Ordinal<Mile, unsigned int>(num) {}
};

class Difficulty : public Ordinal<Difficulty, double> {
public:
	Difficulty( double num ) : Ordinal<Difficulty, double>(num) {}
};

class Percentage : public Ordinal<Percentage, double> {
public:
	Percentage( double num ) : Ordinal<Percentage, double>(num) {}
};

class Mph : public Ordinal<Mph, double> {
public:
	Mph( double num ) : Ordinal<Mph, double>(num) {}
};

class Dollar : public Ordinal<Dollar, double> {
public:
	Dollar( double num ) : Ordinal<Dollar, double>(num) {}
};

class Hour : public Ordinal<Hour, double> {
public:
	Hour( double num ) : Ordinal<Hour, double>(num) {}
};

} /* end namespace */

#endif
