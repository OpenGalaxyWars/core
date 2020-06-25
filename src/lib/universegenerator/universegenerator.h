#pragma once

#include <cstdint>

namespace ogw {

struct UniverseGeneratorParams {
	uint64_t max_objects = 0;
};

/**
 * This generator is intended to generate the whole universe solar systems without
 * generating the objects inside the solar systems themselves
 */
class UniverseGenerator {
public:
	UniverseGenerator(const UniverseGeneratorParams &params): m_params(params) {}
	void run();
private:
	UniverseGeneratorParams m_params;
};
}