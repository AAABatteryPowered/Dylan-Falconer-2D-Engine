#include "../../include/glad/glad.h"

#include "../global.h"
#include "render.h"
#include "render_internal.h"

static Render_State_Internal state = {0};

void render_init(void) {
    global.render.width = 800;
    global.render.height = 600;
    global.render.window = render_init_window(global.render.width, global.render.height);

    render_init_quad(&state.vao_quad, &state.vbo_quad, &state.ebo_quad);
    render_init_shaders(&state);
    render_init_color_texture(&state.texture_color);

}
void render_begin(void) {
    glClearColor(0.2, 0.3, 0.3, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}
void render_end(void) {
    SDL_GL_SwapWindow(global.render.window);
}

/*void mulMatrix4x4Vec3(vec3 returningVec, vec3 vec, mat4x4 mat) {
    returningVec[0] = vec[0] * mat[0][0] + vec[1] * mat[1][0] + vec[2] * mat[2][0] + mat[3][0];
    returningVec[1] = vec[0] * mat[0][1] + vec[1] * mat[1][1] + vec[2] * mat[2][1] + mat[3][1];
    returningVec[2] = vec[0] * mat[0][2] + vec[1] * mat[1][2] + vec[2] * mat[2][2] + mat[3][2];
    float w = vec[0] * mat[0][3] + vec[1] * mat[1][3] + vec[2] * mat[2][3] + mat[3][3];

    if (w != 0) {
        returningVec[0] /= w;
        returningVec[1] /= w;
        returningVec[2] /= w;
    }
}*/

void render_quad(vec3 pos, vec3 camera, vec2 size, vec4 color) {
    glUseProgram(state.shader_default);

    /*float fNear = 0.1;
    float fFar = 1000.0;
    float fov = 90.0;
    float screenratio = global.render.width/global.render.height;
    float fovRad = 1 / tanf(fov * 0.5 / 180 * 3.14159);

    mat4x4 threedmatrix;
    threedmatrix[0][0] = screenratio * fovRad;
    threedmatrix[1][1] = fovRad;
    threedmatrix[2][2] = fFar / (fFar/fNear);
    threedmatrix[3][2] = (-fFar * fNear) / (fFar - fNear);
    threedmatrix[2][3] = 1;
    threedmatrix[3][3] = 0;*/

    mat4x4 model;
    mat4x4_identity(model);

    //mat4x4_mul_vec4(pos, threedmatrix, pos);

    pos[0] = pos[0] + 50;
    pos[1] = pos[1] + 50;
    pos[2] = pos[2] + 50;

    mat4x4_translate(
        model,
        camera[0],
        camera[1],
        camera[2]
    );
    mat4x4_scale_aniso(model, model, size[0], size[1], size[2]);
  
    glUniformMatrix4fv(glGetUniformLocation(state.shader_default, "model"), 1, GL_FALSE, &model[0][0]);
    glUniform4fv(glad_glGetUniformLocation(state.shader_default, "color"), 1, color);
    
    glBindVertexArray(state.vao_quad); 

    glBindTexture(GL_TEXTURE_2D, state.texture_color);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

    glBindVertexArray(0);

}

void render_triangle(vec2 pos, vec2 size, vec4 color) {
    glUseProgram(state.shader_default);

    mat4x4 model;
    mat4x4_identity(model);

    mat4x4_translate(model, pos[0], pos[1], 0);
    mat4x4_scale_aniso(model, model, size[0], size[1], 1);

    glUniformMatrix4fv(glGetUniformLocation(state.shader_default, "model"), 1, GL_FALSE, &model[0][0]);
    glUniform4fv(glad_glGetUniformLocation(state.shader_default, "color"), 1, color);
    
    glBindVertexArray(state.vao_quad); 

    glBindTexture(GL_TEXTURE_2D, state.texture_color);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, NULL);

    glBindVertexArray(0);
}