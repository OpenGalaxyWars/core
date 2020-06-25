#include "universegenerator/universegenerator.h"

int main(int argc, const char **argv)
{
	auto params = ogw::UniverseGeneratorParams{100};
	auto gen = new ogw::UniverseGenerator(params);
	gen->run();
	return 0;
}