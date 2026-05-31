#pragma once

#include <raylib.h>
#include <string>
#include <unordered_map>

class ResourceManager
{
public:
    void LoadTextureResource(const std::string& id, const std::string& path);
    Texture2D& GetTexture(const std::string& id);
    bool HasTexture(const std::string& id);

    void Unload();

private:
    std::unordered_map<std::string, Texture2D> m_Textures;
    std::unordered_map<std::string, Sound> m_Sounds;
    std::unordered_map<std::string, Font> m_Fonts;
};