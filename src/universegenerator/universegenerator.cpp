#include "universegenerator.h"
#include "common/gameobjects/starsystem.h"
#include "common/utils/uuid.h"

#include <iostream>

namespace ogw {
void UniverseGenerator::run()
{
	for (uint64_t i = 1; i <= m_params.max_objects; i++) {
		auto obj = new StarSystem(util::generate_uuid_v4(), L"pouet");
		std::cout << obj->getId() << std::endl;
		delete obj;
	}
}
}