#pragma once

#include <glm/glm.hpp>

#include "glad/glad.h"
#include "imgui/imgui.h"

#include <cstdint>
#include <string>


class Viewport {
private:
    GLuint framebuffer;
    GLuint framebufferDepthStencil;
    GLuint framebufferTexture;

    std::size_t width, height;

    glm::vec3 clearColor;

    GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };

    std::string viewportName;
public:
    Viewport(std::size_t width, std::size_t height, std::string viewportName);
    ~Viewport();

    void setClearColor(glm::vec3);

    void setupRender();

    void endRender();

    void renderWindow(ImGuiWindowFlags extraFlags);
};