#include "universegenerator.h"
#include "common/gameobjects/starsystem.h"

namespace ogw {
void UniverseGenerator::run()
{
	for (uint64_t i = 1; i <= m_params.max_objects; i++) {
		auto obj = new StarSystem(i, L"pouet");
		delete obj;
	}
}
}