#include <fstream>
#include <sstream>
#include <iostream>
#include "Texture.h"
#include "stb_image/stb_image.h"

Texture::Texture(const std::string& filepath)
    : rendererId(0), filepath(filepath), localBuffer(nullptr), width(0), height(0), bitsPerPixel(0)  {


    stbi_set_flip_vertically_on_load(1); // textures in opengl are bottome left (0,0). images are top left (0,0). so it has to be flipped horicantally
    localBuffer = stbi_load(filepath.c_str(), &width, &height, &bitsPerPixel, 4);

    GLCall(glGenTextures(1, &rendererId));
    GLCall(glBindTexture(GL_TEXTURE_2D, rendererId));

    // settings how fitting and sizing is done. mandatory params
    // set the texture wrapping/filtering options (on the currently bound texture object)
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR)); //  how texture resampled down if texture has to be smaller
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR)); //  how texture resampled up if texture has to be bigger
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE)); // horizontal
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE)); // vertical

    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (const void*) localBuffer ));
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));

    if (localBuffer) {
        stbi_image_free(localBuffer);
    }

}

Texture::~Texture() {
    GLCall(glDeleteTextures(1, &rendererId));
}

void Texture::bind(unsigned int slot) const {
    GLCall(glActiveTexture(GL_TEXTURE0 + slot));
    GLCall(glBindTexture(GL_TEXTURE_2D, rendererId));
}

void Texture::unbind() const  {
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
