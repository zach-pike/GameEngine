#include "Viewport/Viewport.hpp"

#include <iostream>

void Viewport::leftClick(ImVec2 pos, ImVec2 displaySize) {

}

Viewport::Viewport(std::size_t _width, std::size_t _height, std::string _viewportName):
    width(_width),
    height(_height),
    viewportName(_viewportName)
{
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

    glGenRenderbuffers(1, &framebufferDepthStencil);
    glBindRenderbuffer(GL_RENDERBUFFER, framebufferDepthStencil);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);

    glGenTextures(1, &framebufferTexture);
    glBindTexture(GL_TEXTURE_2D, framebufferTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
    // Use location=0 in fragment shader
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, framebufferTexture, 0);

    // Attach depth buffer
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, framebufferDepthStencil);

    glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "Bad framebuffer state!\n";
        std::exit(1);
    }
}

Viewport::~Viewport() {
    glDeleteRenderbuffers(1, &framebufferDepthStencil);
    glDeleteTextures(1, &framebufferTexture);
    glDeleteFramebuffers(1, &framebuffer);
}

void Viewport::setClearColor(glm::vec3 color) {
    clearColor = color;
}

void Viewport::setupRender() {
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glViewport(0, 0, width, height);
    glClearColor(clearColor.r, clearColor.g, clearColor.b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Viewport::endRender() {

}

void Viewport::renderWindow(ImGuiWindowFlags extraFlags) {
    ImGui::Begin(viewportName.c_str(), nullptr, extraFlags);
        ImVec2 viewportSize = ImGui::GetContentRegionAvail();

        float imageAspectRatio = (float)width / (float)height;
        float contentRegionAspectRatio = viewportSize.x / viewportSize.y;

        if (contentRegionAspectRatio > imageAspectRatio) {
            float imageWidth = viewportSize.y * imageAspectRatio;
            float xPadding = (viewportSize.x - imageWidth) / 2;
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + xPadding);
            ImGui::ImageButton((ImTextureID)(intptr_t)framebufferTexture, ImVec2(imageWidth, viewportSize.y), ImVec2(0, 1), ImVec2(1, 0));
            lastImageSize = ImVec2(imageWidth, viewportSize.y);
        } else {
            float imageHeight = viewportSize.x / imageAspectRatio;
            float yPadding = (viewportSize.y - imageHeight) / 2;
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + yPadding);
            ImGui::ImageButton((ImTextureID)(intptr_t)framebufferTexture, ImVec2(viewportSize.x, imageHeight), ImVec2(0, 1), ImVec2(1, 0));
            lastImageSize = ImVec2(viewportSize.x, imageHeight);
        }
        frameCorner = ImGui::GetItemRectMin();

        unsigned int coordX = (ImGui::GetMousePos().x - frameCorner.x);
        unsigned int coordY = (ImGui::GetMousePos().y - frameCorner.y);
        lastMousePos = ImVec2(coordX, coordY);
        
        if(ImGui::IsItemActive() && ImGui::IsItemHovered()) {
            if (!imgLeftClicked) {
                leftClick(ImVec2(coordX, coordY), lastImageSize);
                imgLeftClicked = true;
            }
        } else {
            imgLeftClicked = false;
        }
    ImGui::End();
}

ImVec2 Viewport::getMousePos() const {
    return lastMousePos;
}

ImVec2 Viewport::getImageSize() const {
    return lastImageSize;
}

ImVec2 Viewport::getViewportImageFrameCorner() const {
    return frameCorner;
}

glm::vec2 Viewport::getSize() const {
    return glm::vec2(width, height);
}