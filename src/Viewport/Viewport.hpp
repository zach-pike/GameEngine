#pragma once

#include "glad/glad.h"

#include <cstdint>
#include <glm/glm.hpp>

class Viewport {
private:
    GLuint framebuffer;
    GLuint framebufferDepthStencil;
    GLuint framebufferTexture;

    std::size_t width, height;

    glm::vec3 clearColor;

    GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
public:
    Viewport(std::size_t width, std::size_t height);
    ~Viewport();

    void setClearColor(glm::vec3);

    void setupRender();

    void endRender();

    void renderWindow();
};