#ifndef __EXCEPTIONS_H__
#define __EXCEPTIONS_H__

#include <string>
#include "fwk/Types.h"

namespace Shipping {

class Exception {
public:   
    enum Id { // Enum for remote designation
      noException_ = 0,
      unknownException_ = 1,
      unknownCommandException_ = 2
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

class UnknownCommandException : public Exception {
public:
   UnknownCommandException( std::string what )  : Exception(what) {}
   virtual Id id();
};

} // namespace Shipping

#endif
