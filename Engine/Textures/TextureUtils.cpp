#include "TextureUtils.h"

#include "TextureSettings.h"
#include "TextureData.h"

#include <fstream>
#include <iostream>

// for reading from png
// https://github.com/nothings/stb/blob/master/stb_image.h
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


TextureData TextureUtils::decodeTextureFile(std::ifstream& file) {
    int width = 0;
    int height = 0;
    int nrChannels;
    stbi_set_flip_vertically_on_load(1);
    // this is called from main, which is in root
    // TODO: Change this later to not be hard coded (i.e. change asset path from ifstream to char[])
    GLubyte* data = stbi_load("assets/diffuse.png", &width, &height, &nrChannels, 0);
    if (stbi_failure_reason()) 
        std::cout << stbi_failure_reason() << std::endl;
    
    if (data == NULL) {
        std::cout << "Could not load texture file" << std::endl;
    } else {
        std::cout << "Loaded texture file" << std::endl;
    }

    return TextureData(data, width, height);
}

void TextureUtils::loadTextureToOpenGL(GLuint* textures, TextureData& data, TextureSettings& settings) {
    std::cout << "\tBefore Gen: " << textures << " - " << *textures << std::endl;
    glGenTextures(1, textures);
    std::cout << "\tAfter Gen: " << textures << " - " << *textures << std::endl;
    glActiveTexture(GL_TEXTURE0);
    // binding texture to be edited
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, data.getWidth(), data.getHeight(), 0, GL_BGRA,
            GL_UNSIGNED_BYTE, data.getDataArray());

    // setting new parameters based on builder settings
    if (settings.isMipmap()) {
        glGenerateMipmap(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        if (settings.isAnisotropic() && GL_EXT_texture_filter_anisotropic) {
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, 0);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT,
                    4.0f);
        }
    } else if (settings.isNearest()) {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    } else {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    }

    // clamping edges of texture
    if (settings.isClampEdges()) {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    } else {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }
    glBindTexture(GL_TEXTURE_2D, 0);
}

