#pragma once

#include <glad/glad.h>

#include <string>

#include <glm/vec2.hpp>

class Texture {
private:
    GLuint textureId;

    glm::vec2 size;
public:
    Texture();
    ~Texture();

    void loadFromFilePath(std::string path);

    void uploadTexture2DFromBuffer(const void* data, std::size_t width, std::size_t height, GLenum format, GLenum type);

    glm::vec2 getSize(); 

    GLuint getTextureId();
};