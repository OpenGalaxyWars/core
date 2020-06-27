#include "window.h"
#include <cstdio>
#include <iostream>

namespace ogw {

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

Window::Window()
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
    }

	SDL_GL_SetAttribute (SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
    SDL_GL_SetAttribute (SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// Detect screen size & use it
	SDL_DisplayMode displayMode;
	SDL_GetCurrentDisplayMode(0, &displayMode);


	m_window = SDL_CreateWindow("Hello World!", 0, 0, displayMode.w, displayMode.h, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if (!m_window) {
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return;
	}

	//Get window surface
	m_screen_surface = SDL_GetWindowSurface(m_window);

	//Fill the surface white
	SDL_FillRect(m_screen_surface, NULL, SDL_MapRGB(m_screen_surface->format, 0x00, 0x00, 0x00));

	//Update the surface
	SDL_UpdateWindowSurface(m_window);

	//Wait two seconds
	SDL_Delay( 2000 );
}

Window::~Window()
{
	if (m_window) {
    	SDL_DestroyWindow(m_window);
	}
    SDL_Quit();

}

void Window::run()
{
	SDL_Event e;
	while (!m_should_stop) {
		// Handle events on queue
		while (SDL_PollEvent( &e ) != 0) {
			// User requests quit
			switch (e.type) {
				// Key press
				case SDL_KEYDOWN:
					break;
				// Key release
				case SDL_KEYUP:
					break;
				case SDL_QUIT:
					m_should_stop = true;
					break;
			}
		}

		//Update the surface
		SDL_UpdateWindowSurface(m_window);

	}
}

}