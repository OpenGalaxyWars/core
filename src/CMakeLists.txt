cmake_minimum_required(VERSION 3.13)

set(PROJECT_NAME OpenGalaxyWars)
project(${PROJECT_NAME})

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/common")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/universegenerator")

set(CORE_SRCS
	main.cpp
	${common_SRCS}
	${generator_SRCS})

add_executable(${PROJECT_NAME} ${CORE_SRCS})
