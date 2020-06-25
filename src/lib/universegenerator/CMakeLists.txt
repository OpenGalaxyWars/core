set(generator_SRCS
	${CMAKE_CURRENT_SOURCE_DIR}/universegenerator.cpp)

add_library(${PROJECT_NAME}generator
	${generator_SRCS})