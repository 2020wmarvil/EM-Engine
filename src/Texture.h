#pragma once

#include <GL/glew.h>

#include <string>
#include <vector>
#include <iostream>

class Texture {
private:
    unsigned int m_RendererID;
    std::string m_Filepath;
    unsigned char* m_LocalBuffer;
    int m_SpriteSheetWidth, m_SpriteSheetHeight, m_Rows, m_Cols, m_BBP;
    float m_SpriteWidth, m_SpriteHeight;

    bool m_Opaque;

    std::vector<std::vector<std::vector<bool>>> m_Bitmaps;

    void GenBitmaps();
public:
    Texture(const std::string& filepath, int rows, int cols);
    ~Texture();

    void Bind(unsigned int slot=0) const;
    void Unbind() const;

    bool isTransparent(int sprite, int x, int y) const {
        if (m_Opaque) return 0;

        return m_Bitmaps[sprite][y][x];
    }

    inline int GetSpriteSheetWidth() const { return m_SpriteSheetWidth; }
    inline int GetSpriteSheetHeight() const { return m_SpriteSheetHeight; }
    inline float GetSpriteWidth() const { return m_SpriteWidth; }
    inline float GetSpriteHeight() const { return m_SpriteHeight; }
};
