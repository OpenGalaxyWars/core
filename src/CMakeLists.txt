cmake_minimum_required(VERSION 3.13)

set(PROJECT_NAME OpenGalaxyWars)
project(${PROJECT_NAME})

set(CORE_SRCS
	main.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/lib/universegenerator")

add_executable(${PROJECT_NAME} ${CORE_SRCS})
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}generator)