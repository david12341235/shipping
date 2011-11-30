// Copyright (c) 2005-2006_2007 David R. Cheriton.  All rights reserved.

#include "ShippingException.h"
#include "fwk/Exception.h"
#include <assert.h>
#include <iostream>
#include <signal.h>

using namespace Shipping;

Exception::Id Exception::IdInstance( U32 v ) {
   switch( v ) {
    case noException_ : return noException_;
    case unknownException_ : return unknownException_;
    default : throw Fwk::RangeException( "Fwk::Exception::Id" );
   }
}

Exception::~Exception() {
}

Exception::Id
Exception::id() {
   return unknownException_;
}

Exception::Id
UnknownCommandException::id() {
   return unknownCommandException_;
}

