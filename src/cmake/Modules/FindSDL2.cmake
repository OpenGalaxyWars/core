find_library(SDL2_LIBRARY NAMES SDL2 PATHS /usr/lib)

find_path(SDL2_INCLUDE_DIRS
	NAMES SDL.h
	PATHS /usr/include/SDL2 /usr/local_include/SDL2)