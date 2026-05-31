#include "resources/resourcemanager.h"
#include <stdexcept>

void ResourceManager::LoadTextureResource(const std::string& id, const std::string& path)
{
    if (m_Textures.find(id) != m_Textures.end()) throw std::runtime_error("Texture already loaded: " + id);

    Texture2D texture = ::LoadTexture(path.c_str());

    if (texture.id == 0) throw std::runtime_error("Failed to load texture: " + path);

    m_Textures.emplace(id, texture);
}

Texture2D& ResourceManager::GetTexture(const std::string& id)
{
    auto it = m_Textures.find(id);

    if (it == m_Textures.end()) throw std::runtime_error("Texture not found: " + id);

    return it->second;
}

bool ResourceManager::HasTexture(const std::string& id)
{
    return m_Textures.find(id) != m_Textures.end();
}

void ResourceManager::Unload()
{
    for (auto& texture : m_Textures)
    {
        UnloadTexture(texture.second);
    }

    m_Textures.clear();
}