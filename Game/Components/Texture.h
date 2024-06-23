#ifndef C_TEXTURE_H__
#define C_TEXTURE_H__

#pragma once

#include "../ECS/API.h"
#include "../ECS/Component.h"
#include "../Resources/SDLTexture.h"
#include "TextureResource.h"
#include <unordered_map>

class Texture : public gecs::Component<Texture> 
{
    public:
        Texture(const gecs::ComponentTypeId& typeId, const gecs::EntityId& ownerId, float scalex = 1.0f, float scaley = 1.0f)
            : gecs::Component<Texture>(typeId, ownerId) {
            // Additional initialization if needed
            m_ScaleX = scalex;
            m_ScaleY = scaley;
        }

        [[nodiscard]] inline std::string TextureId() const { return m_TextureId; }
        inline void SetTextureId(std::string textureId) { m_TextureId = textureId; }

        inline float ScaleX() const { return m_ScaleX; }
        inline float ScaleY() const { return m_ScaleY; }

        void SetResource(const std::string& key, const TextureResource& resource) 
        { 
            gecs::ECS_Engine.resources().Manager<SDLTexture>()->Load(key, resource.m_ResourcePath);
            m_TextureId = resource.m_ResourceId;
            resources_[key] = resource; 
        }

        [[nodiscard]] inline TextureResource GetActiveResource() const { return GetResource(m_TextureId); }

        TextureResource GetResource(const std::string& key) const {
            auto it = resources_.find(key);
            if (it != resources_.end()) {
                return it->second;
            }
            throw std::runtime_error("Resource not found: " + key);
        }

        [[nodiscard]] inline bool Flip() const { return m_Flip; }
        inline void FlipIt() { m_Flip = true; }
        inline void UnFlip() { m_Flip = false; }

    private:
        std::string m_TextureId;
        std::unordered_map<std::string, TextureResource> resources_;
        float       m_ScaleX = 1.0f;
        float       m_ScaleY = 1.0f;
        bool		m_Flip = false;
};

#endif // C_TEXTURE_H__