cmake_minimum_required(VERSION 3.13)

set(PROJECT_NAME OpenGalaxyWars)
project(${PROJECT_NAME})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules/")

find_package(SDL2 REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/common")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/universegenerator")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/client")

set(CORE_SRCS
	main.cpp
	${client_SRCS}
	${common_SRCS}
	${generator_SRCS})

add_executable(${PROJECT_NAME} ${CORE_SRCS})
target_link_libraries(${PROJECT_NAME}
	SDL2::SDL2)
