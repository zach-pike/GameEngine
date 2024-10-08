#pragma once

#include <glm/glm.hpp>

#include "imgui/imgui.h"
#include "glad/glad.h"

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

    bool imgLeftClicked = false;

    ImVec2 lastMousePos, lastImageSize;
    ImVec2 frameCorner;
protected:
    virtual void leftClick(ImVec2 pos, ImVec2 displaySize);
public:
    Viewport(std::size_t width, std::size_t height, std::string viewportName);
    ~Viewport();

    void setClearColor(glm::vec3);

    void setupRender();

    void endRender();

    void renderWindow(ImGuiWindowFlags extraFlags);

    ImVec2 getMousePos() const;
    ImVec2 getImageSize() const;

    ImVec2 getViewportImageFrameCorner() const;

    glm::vec2 getSize() const;
};