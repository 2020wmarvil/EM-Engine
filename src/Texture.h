#pragma once

#include <GL/glew.h>

#include <string>

class Texture {
private:
    unsigned int m_RendererID;
    std::string m_Filepath;
    unsigned char* m_LocalBuffer;
    int m_Width, m_Height, m_Rows, m_Cols, m_BBP;
    float m_SpriteWidth, m_SpriteHeight;
public:
    Texture(const std::string& filepath, int rows, int cols);
    ~Texture();

    void Bind(unsigned int slot=0) const;
    void Unbind() const;

    inline int GetWidth() const { return m_Width; }
    inline int GetHeight() const { return m_Height; }
    inline float GetSpriteWidth() const { return m_SpriteWidth; }
    inline float GetSpriteHeight() const { return m_SpriteHeight; }
};
