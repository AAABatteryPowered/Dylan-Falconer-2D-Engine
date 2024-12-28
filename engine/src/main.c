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

vec3 camera_position = {0,0,1};

static void input_handle(void) {

    if (global.input.escape == KS_PRESSED || global.input.escape == KS_HELD)
        should_quit = true;
    
    if (global.input.left == KS_PRESSED || global.input.left == KS_HELD)
        camera_position[1] += 500 * global.time.delta;
    if (global.input.right == KS_PRESSED || global.input.right == KS_HELD)
        camera_position[1] -= 500 * global.time.delta;
    if (global.input.up == KS_PRESSED || global.input.up == KS_HELD)
        camera_position[0] -= 500 * global.time.delta;
    if (global.input.down == KS_PRESSED || global.input.down == KS_HELD)
        camera_position[0] += 500 * global.time.delta;
    if (global.input.jump == KS_PRESSED || global.input.jump == KS_HELD)
        camera_position[2] -= 10 * global.time.delta;
    if (global.input.sneak == KS_PRESSED || global.input.sneak == KS_HELD)
        camera_position[2] += 10 * global.time.delta;
}

int main(int argc, char *argv[]) {
    time_init(144);
    config_init();
    render_init();

    pos[0] = global.render.width * 0.5;
    pos[1] = global.render.height * 0.5;
    
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

        printf("%.6f\n", camera_position[2]);

        render_begin();

        render_quad(
            pos,
            (vec3){50,50,510},
            (vec4){0,1,1,1},
            camera_position);
            
        render_end();
        time_update_late();
    }

    return 0;
}

int resizeWindow(int winWidth, int winHeight) {
    glViewport(0, 0, winWidth, winHeight);
    return 0;
}