#include "window.h"
#include <cstdio>
#include <iostream>
#include <GL/glew.h>

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_SDL_GL3_IMPLEMENTATION
#include "external/nuklear/nuklear.h"
#include "external/nuklear/nucklear_sdl_gl3.h"

#define MAX_VERTEX_MEMORY 512 * 1024
#define MAX_ELEMENT_MEMORY 128 * 1024

namespace ogw {

Window::Window()
{
    // Initialize SDL
    if (!initSDL()) {
        std::cerr << "Failed to setup window. Aborting." << std::endl;
		exit(1);
    }

	 if (!initGL()) {
		std::cerr << "Failed to setup window. Aborting." << std::endl;
		exit(2);
	 }

	 if (!initNuklear()) {
		std::cerr << "Failed to setup window. Aborting." << std::endl;
		exit(3);
	 }
}

Window::~Window()
{
	nk_sdl_shutdown();
	if (m_gl_context) {
    	SDL_GL_DeleteContext(m_gl_context);
	}

	if (m_window) {
    	SDL_DestroyWindow(m_window);
	}
    SDL_Quit();

}

bool Window::initSDL()
{
	/* SDL setup */
    SDL_SetHint(SDL_HINT_VIDEO_HIGHDPI_DISABLED, "0");
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER|SDL_INIT_EVENTS) < 0) {
		std::cerr << "Unable to init SDL. Error was: " << SDL_GetError() << std::endl;
		return false;
	}

    SDL_GL_SetAttribute (SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
    SDL_GL_SetAttribute (SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// Detect screen size & use it
	SDL_GetCurrentDisplayMode(0, &m_init_displaymode);

    m_window = SDL_CreateWindow("Demo",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        m_init_displaymode.w, m_init_displaymode.h, SDL_WINDOW_OPENGL|SDL_WINDOW_SHOWN|SDL_WINDOW_ALLOW_HIGHDPI|SDL_WINDOW_RESIZABLE);

	if (!m_window) {
		std::cerr << "Unable to create main window. Error was: " << SDL_GetError() << std::endl;
		return false;
	}

	int win_width, win_height;
    m_gl_context = SDL_GL_CreateContext(m_window);
    SDL_GetWindowSize(m_window, &win_width, &win_height);

	return true;
}

bool Window::initGL()
{
	m_gl_context = SDL_GL_CreateContext(m_window);
    SDL_GetWindowSize(m_window, &m_window_width, &m_window_height);

    /* OpenGL setup */
    glViewport(0, 0, m_init_displaymode.w, m_init_displaymode.h);
    glewExperimental = 1;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to setup GLEW" << std::endl;
        return false;
    }

	return true;
}

bool Window::initNuklear()
{
	m_nuklear_context = nk_sdl_init(m_window);

	nk_font_atlas *atlas;
    nk_sdl_font_stash_begin(&atlas);
	// Here for loading fonts
    nk_sdl_font_stash_end();

	return true;
}

void Window::run()
{
	SDL_Event evt;
	nk_colorf bg;

	bg.r = 0.10f, bg.g = 0.18f, bg.b = 0.24f, bg.a = 1.0f;
	while (!m_should_stop) {
        nk_input_begin(m_nuklear_context);
        while (SDL_PollEvent(&evt)) {
            switch (evt.type) {
				case SDL_QUIT:
					m_should_stop = true;
					break;
			}
            nk_sdl_handle_event(&evt);
        } nk_input_end(m_nuklear_context);

		// If one input asked for a stop, break here
		if (m_should_stop) {
			break;
		}

        /* GUI */
        if (nk_begin(m_nuklear_context, "Demo", nk_rect(50, 50, 230, 250),
            NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE|
            NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE)) {
            enum {EASY, HARD};
            static int op = EASY;
            static int property = 20;

            nk_layout_row_static(m_nuklear_context, 30, 80, 1);
            if (nk_button_label(m_nuklear_context, "button"))
                printf("button pressed!\n");
            nk_layout_row_dynamic(m_nuklear_context, 30, 2);
            if (nk_option_label(m_nuklear_context, "easy", op == EASY)) op = EASY;
            if (nk_option_label(m_nuklear_context, "hard", op == HARD)) op = HARD;
            nk_layout_row_dynamic(m_nuklear_context, 22, 1);
            nk_property_int(m_nuklear_context, "Compression:", 0, &property, 100, 10, 1);

            nk_layout_row_dynamic(m_nuklear_context, 20, 1);
            nk_label(m_nuklear_context, "background:", NK_TEXT_LEFT);
            nk_layout_row_dynamic(m_nuklear_context, 25, 1);
            if (nk_combo_begin_color(m_nuklear_context, nk_rgb_cf(bg), nk_vec2(nk_widget_width(m_nuklear_context),400))) {
                nk_layout_row_dynamic(m_nuklear_context, 120, 1);
                bg = nk_color_picker(m_nuklear_context, bg, NK_RGBA);
                nk_layout_row_dynamic(m_nuklear_context, 25, 1);
                bg.r = nk_propertyf(m_nuklear_context, "#R:", 0, bg.r, 1.0f, 0.01f,0.005f);
                bg.g = nk_propertyf(m_nuklear_context, "#G:", 0, bg.g, 1.0f, 0.01f,0.005f);
                bg.b = nk_propertyf(m_nuklear_context, "#B:", 0, bg.b, 1.0f, 0.01f,0.005f);
                bg.a = nk_propertyf(m_nuklear_context, "#A:", 0, bg.a, 1.0f, 0.01f,0.005f);
                nk_combo_end(m_nuklear_context);
            }
        }
        nk_end(m_nuklear_context);

        /* Draw */
        SDL_GetWindowSize(m_window, &m_window_width, &m_window_height);
        glViewport(0, 0, m_window_width, m_window_height);
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(bg.r, bg.g, bg.b, bg.a);
        /* IMPORTANT: `nk_sdl_render` modifies some global OpenGL state
         * with blending, scissor, face culling, depth test and viewport and
         * defaults everything back into a default state.
         * Make sure to either a.) save and restore or b.) reset your own state after
         * rendering the UI. */
        nk_sdl_render(NK_ANTI_ALIASING_ON, MAX_VERTEX_MEMORY, MAX_ELEMENT_MEMORY);
        SDL_GL_SwapWindow(m_window);
	}
}

}