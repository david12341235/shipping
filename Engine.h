#ifndef ENGINE_H
#define ENGINE_H

#include <string>

#include "fwk/Ptr.h"
#include "fwk/PtrInterface.h"
#include "Instance.h"

namespace Shipping {

class Engine : public Fwk::PtrInterface<Engine> {
public:
	typedef Fwk::Ptr<Engine> Ptr;
	typedef Fwk::Ptr<Engine const> PtrConst;
};

} /* end namespace */

#endif
