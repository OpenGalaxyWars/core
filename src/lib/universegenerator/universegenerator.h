#pragma once

#include <cstdint>

namespace ogw {

struct UniverseGeneratorParams {
	uint64_t max_objects = 0;
};

class UniverseGenerator {
public:
	UniverseGenerator(const UniverseGeneratorParams &params): m_params(params) {}
	void run();
private:
	UniverseGeneratorParams m_params;
};
}