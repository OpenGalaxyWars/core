#pragma once

#include <SDL.h>

struct nk_context;

namespace ogw {

class Window {
public:
	Window();
	~Window();
	void run();
private:
	bool initSDL();
	bool initGL();
	bool initNuklear();

	SDL_Window *m_window = nullptr;
	SDL_GLContext m_gl_context = nullptr;
	SDL_DisplayMode m_init_displaymode;

	int m_window_width = 0;
	int m_window_height = 0;

	nk_context *m_nuklear_context;

	bool m_should_stop = false;
};
}