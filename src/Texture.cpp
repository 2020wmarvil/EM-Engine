#include "Texture.h"

#include "stb_image/stb_image.h"

#include <cassert>

#define assertm(exp, msg) assert(((void)msg, exp))

Texture::Texture(const std::string& path, int rows, int cols) 
    : m_RendererID(0), m_Filepath(path), m_LocalBuffer(nullptr), m_Rows(rows), m_Cols(cols)
{
    stbi_set_flip_vertically_on_load(1);

    m_LocalBuffer = stbi_load(path.c_str(), &m_SpriteSheetWidth, &m_SpriteSheetHeight, &m_BBP, 4);

    assertm(m_BBP == 3 || m_BBP == 4, "Texture format not accepted. Must be RGB or RGBA.");

    m_SpriteWidth = 1.0 / cols;
    m_SpriteHeight = 1.0 / rows;

    if (m_BBP == 3) {
        m_Opaque = true;
    } else {
        m_Opaque = false;

        GenBitmaps();
    }

    glGenTextures(1, &m_RendererID);
    glBindTexture(GL_TEXTURE_2D, m_RendererID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_SpriteSheetWidth, m_SpriteSheetHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);
    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture() {
    glDeleteTextures(1, &m_RendererID);

    if (m_LocalBuffer)
        stbi_image_free(m_LocalBuffer);
}

void Texture::Bind(unsigned int slot) const {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_RendererID);
}

void Texture::Unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::GenBitmaps() {
    int width = m_SpriteWidth * m_SpriteSheetWidth;
    int height = m_SpriteHeight * m_SpriteSheetHeight;

    for (int r=m_Rows-1; r>=0; r--) {
        for (int c=0; c<m_Cols; c++) {
            std::vector<std::vector<bool>> bitmap;

            for (int y=height*(r+1)-1; y>=height*r; y--) {
                std::vector<bool> line;

                for (int x=width*c; x<width*(c+1); x++) {
                    for (int bytes=3; bytes<m_BBP; bytes++) {
                        line.push_back(m_LocalBuffer[bytes+x*m_BBP+m_BBP*y*m_SpriteSheetWidth]==0);
                    }
                } bitmap.push_back(line);
            } m_Bitmaps.push_back(bitmap);
        }
    }
}