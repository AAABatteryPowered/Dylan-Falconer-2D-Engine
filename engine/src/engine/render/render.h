#ifndef RENDER_H
#define RENDER_H

#include "../../include/SDL2/SDL.h"
#include "../../lib/linmath.h"

#include "../types.h"

typedef struct render_state {
    SDL_Window *window;
    f32 width;
    f32 height;

} Render_State;

void render_init(void);
void render_begin(void);
void render_end(void);
//void mulMatrix4x4Vec3(vec3 vec, mat4x4 mat);
void render_quad(vec3 pos, vec3 camera, vec2 size, vec4 color);
void render_triangle(vec2 pos, vec2 size, vec4 color);

#endif