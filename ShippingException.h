// Framework Exception types
// Copyright(c) 1993-2006_2007, David R. Cheriton, all rights reserved.

#ifndef SHIPPING_EXCEPTION_H
#define SHIPPING_EXCEPTION_H

#include <string.h>
#include "String.h"
#include "fwk/Ptr.h"
#include "fwk/PtrInterface.h"

#ifdef _MSC_VER // Don't want to see strerror warnings, assume we won't get buffer overflowed
  #pragma warning(disable: 4996)
#endif

namespace Shipping {

class Exception {
public:

   enum Id { // Enum for remote designation
      noException_ = 0,
      unknownException_ = 1,
      nameExistsException_ = 2,
      unknownAttrException_ = 3,
      rangeException_ = 4,
      locationTypeException_ = 5,
      unknownTypeException_ = 6,
   };

   static Id IdInstance( U32 v );

   std::string what() const { return what_; }
   virtual ~Exception();
   // Providing a virtual destructor enables us to catch an Exception, and
   // then dynamic_cast it to a derived exception type or fetch its typeid, etc.
   virtual Id id();
protected:
   Exception( char const * str ) : what_(str) {}
   Exception( std::string str ) : what_(str) {}
private:
   std::string what_;
};

std::ostream & operator<<( std::ostream &, Exception const & );

class NameExistsException : public Exception {
public:
   NameExistsException( std::string what )  : Exception(what) {}
   virtual Id id();
};

class UnknownAttrException : public Exception {
public:
   UnknownAttrException( std::string what )  : Exception(what) {}
   virtual Id id();
};

class UnknownDelimiterException : public Exception {
public:
   UnknownDelimiterException( std::string what )  : Exception(what) {}
   virtual Id id();
};

class RangeException : public Exception {
public:
   RangeException( std::string what )  : Exception(what) {}
   virtual Id id();
};

class LocationTypeException : public Exception {
public:
   LocationTypeException( std::string what )  : Exception(what) {}
   virtual Id id();
};

class UnknownTypeException : public Exception {
public:
   UnknownTypeException( std::string what )  : Exception(what) {}
   virtual Id id();
};

}

#endif /* EXCEPTION_H */
