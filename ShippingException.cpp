// Copyright (c) 2005-2006_2007 David R. Cheriton.  All rights reserved.

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

