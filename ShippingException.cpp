#include "ShippingException.h"
#include <assert.h>
#include <iostream>
#include <signal.h>

Shipping::Exception::Id Shipping::Exception::IdInstance( U32 v ) {
   switch( v ) {
    case noException_ : return noException_;
    case unknownException_ : return unknownException_;
    case nameExistsException_ : return nameExistsException_;
    case unknownAttrException_ : return unknownAttrException_;
    case rangeException_ : return rangeException_;
    case locationTypeException_ : return locationTypeException_;
    case unknownTypeException_ : return unknownTypeException_;
    case initializationException_ : return initializationException_;
    case entityNotFoundException_ : return entityNotFoundException_;
    default : throw Shipping::RangeException( "Shipping::Exception::Id" );
   }
}

Shipping::Exception::~Exception() {
}


Shipping::Exception::Id
Shipping::Exception::id() {
   return unknownException_;
}

Shipping::Exception::Id
Shipping::NameExistsException::id() {
   return nameExistsException_;
}

Shipping::Exception::Id
Shipping::UnknownAttrException::id() {
   return unknownAttrException_;
}

Shipping::Exception::Id
Shipping::RangeException::id() {
   return rangeException_;
}

Shipping::Exception::Id
Shipping::LocationTypeException::id() {
   return locationTypeException_;
}

Shipping::Exception::Id
Shipping::UnknownTypeException::id() {
   return unknownTypeException_;
}

Shipping::Exception::Id
Shipping::InitializationException::id() {
   return initializationException_;
}
   
Shipping::Exception::Id
Shipping::EntityNotFoundException::id() {
   return entityNotFoundException_;

}

