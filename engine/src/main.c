#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "../../include/glad/glad.h"
#define SDL_MAIN_HANDLED
#include "../../include/SDL2/SDL.h"

#include "engine/global.h"
#include "engine/config.h"
#include "engine/input.h"
#include "engine/time.h"
#include "engine/types.h"

static bool should_quit = false;
static vec2 pos;

double yaccel = 0;
double gravity_accel = 5;

vec3 globalcam = {0,0,0};
vec3 cubevertices[] = {{0,0,0},{0,1,0},{1,1,0},{1,0,0},{0,0,1},{0,1,1},{1,1,1},{1,0,1}};


static void input_handle(void) {

    if (global.input.escape == KS_PRESSED || global.input.escape == KS_HELD)
        should_quit = true;
    
    if (global.input.left == KS_PRESSED || global.input.left == KS_HELD)
        globalcam[0] -= 500 * global.time.delta;
    if (global.input.right == KS_PRESSED || global.input.right == KS_HELD)
        globalcam[0] += 500 * global.time.delta;
    if (global.input.up == KS_PRESSED || global.input.up == KS_HELD)
        globalcam[1] += 500 * global.time.delta;
    if (global.input.down == KS_PRESSED || global.input.down == KS_HELD)
        globalcam[1] -= 500 * global.time.delta;
    if (global.input.jump == KS_PRESSED || global.input.jump == KS_HELD)
        globalcam[2] -= 500 * global.time.delta;
    if (global.input.sneak == KS_PRESSED || global.input.sneak == KS_HELD)
        globalcam[2] += 500 * global.time.delta;
}

int main(int argc, char *argv[]) {
    time_init(144);
    config_init();
    render_init();

    pos[0] = global.render.width * 0.5;
    pos[1] = global.render.height * 0.5;

    int cubelength = *(&cubevertices + 1) - cubevertices;
    
    while (!should_quit) {
        time_update();

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

        input_update();
        input_handle();

        render_begin();
        
        render_triangle(
            (vec2){50,50},
            (vec2){50,50},
            (vec4){1,1,1,1}
        );

        render_triangle(
            (vec2){100,50},
            (vec2){50,50},
            (vec4){1,1,1,.5}
        );
            
        render_end();
        time_update_late();
    }

    return 0;
}

int resizeWindow(int winWidth, int winHeight) {
    glViewport(0, 0, winWidth, winHeight);
    return 0;
}