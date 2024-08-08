#pragma once

#include <memory>

#include <glm/glm.hpp>

#include "Utility/GL/Buffer/Buffer.hpp"
#include "Utility/GL/ShaderProgram/ShaderProgram.hpp"
#include "Utility/GL/Texture/Texture.hpp"

class Crosshair {
private:
    std::unique_ptr<ShaderProgram> shader;

    GLuint textureUniform;
    GLuint aspectRatioUniform;
    GLuint scaleUniform;

    Buffer<glm::vec2> vertexBuffer;
    Buffer<glm::vec2> uvBuffer;

    Texture texture;
public:
    Crosshair();
    ~Crosshair();

    void render(float aspectRatio);
};
