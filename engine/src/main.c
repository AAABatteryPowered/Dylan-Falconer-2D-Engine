#include <stdio.h>
#include <stdbool.h>
#include "../../include/glad/glad.h"
#define SDL_MAIN_HANDLED
#include "../../include/SDL2/SDL.h"

#include "engine/global.h"

int main(int argc, char *argv[]) {
    render_init();

    bool should_quit = false;

    f32 current_x = 0.5;
    f64 gravity = 0.01;
    f32 calculated_height = global.render.height * current_x;
    
    while (!should_quit) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    should_quit = true;
                    break;
                case SDL_WINDOWEVENT:
                    if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                        resizeWindow(event.window.data1, event.window.data2);
                    }
                    break;
                default:
                    break;
            }
        }

        render_begin();

        render_quad(
            (vec2){global.render.width * 0.5, calculated_height},
            (vec2){50,50},
            (vec4){0,1,1,1});

        current_x -= gravity;
        gravity += 1/1000000000000000;
        calculated_height = global.render.height * current_x;

        if (calculated_height >= 300) {
            gravity *= -1;
        }

        render_end();
    }

    return 0;
}

int resizeWindow(int winWidth, int winHeight) {
    glViewport(0, 0, winWidth, winHeight);
    return 0;
}