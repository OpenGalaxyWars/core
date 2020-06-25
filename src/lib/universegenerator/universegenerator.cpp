#include "universegenerator.h"
#include "common/gameobjects/objects.h"

namespace ogw {
void UniverseGenerator::run()
{
	for (uint64_t i = 1; i <= m_params.max_objects; i++) {
		auto obj = new GameObject(i);
		delete obj;
	}
}
}