#include "Crosshair.hpp"

#include "MyUtility/ShaderLoaders/VertexFragment/VertexFragment.hpp"

static glm::vec2 crosshairVertexData[] = {
    glm::vec2(-1, -1),
    glm::vec2( 1, -1),
    glm::vec2( 1,  1),
    glm::vec2(-1,  1)
};

static glm::vec2 crosshairUVData[] = {
    glm::vec2(0, 0),
    glm::vec2(0, 1),
    glm::vec2(1, 1),
    glm::vec2(1, 0),
};

Crosshair::Crosshair() {
    shader = loadVertexFragmentShader("./shader/crosshair/");
    shader->use();

    textureUniform     = shader->getUniformLocation("myTexture");
    aspectRatioUniform = shader->getUniformLocation("aspect");
    scaleUniform       = shader->getUniformLocation("scale");

    shader->unbind();

    vertexBuffer.bufferData(crosshairVertexData);
    uvBuffer.bufferData(crosshairUVData);

    texture.loadFromFilePath("resources/crosshair.png");
}

Crosshair::~Crosshair() {

}

void Crosshair::render(float aspectRatio) {
    // Render crosshair
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    shader->use();

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer.getBufferId());
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer.getBufferId());
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
        
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture.getTextureId());

    glUniform1i(textureUniform, 0);
    glUniform1f(aspectRatioUniform, aspectRatio);
    glUniform1f(scaleUniform, .01f);

    glDrawArrays(GL_QUADS, 0, 4);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    shader->unbind();
}