#pragma once

#include <SDL.h>

namespace ogw {

class Window {
public:
	Window();
	~Window();
	void run();
private:
	SDL_Window *m_window = nullptr;
	SDL_Surface *m_screen_surface = nullptr;

	bool m_should_stop = false;
};
}