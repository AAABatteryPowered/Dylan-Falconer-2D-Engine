#include <glad/glad.h>
#include <SDL2/SDL.h>

#include "../util.h"
#include "../global.h"

#include "render.h"
#include "render_internal.h"

SDL_Window *render_init_window(u32 width, u32 height) {
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        ERROR_EXIT("Could not init SDL: %s\n", SDL_GetError());
    }

    SDL_Window *window = SDL_CreateWindow(
        "My Window",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800,
        600,
        SDL_WINDOW_OPENGL
    );

    if (!window) {
        ERROR_EXIT("Failed to init window: %s\n", SDL_GetError());
    }

    SDL_GL_CreateContext(window);
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        ERROR_EXIT("Failed to load GL: %s\n", SDL_GetError());
    }

    puts("OpenGL Loaded");
    printf("Vendor:   %s\n", glGetString(GL_VENDOR));
    printf("Renderer: %s\n", glGetString(GL_RENDERER));
    printf("Version:  %s\n", glGetString(GL_VERSION));

    return window;
}
void render_init_quad(u32 *vao, u32 *vbo, u32 *ebo);