#pragma once

#include "objects.h"

namespace ogw {

class StarSystem: public StellarObject
{
public:
	StarSystem(gobj_t id, const std::wstring &name): StellarObject(id, name) {}
	virtual ~StarSystem() {}
private:
};

}