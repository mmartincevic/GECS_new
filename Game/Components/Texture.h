#ifndef C_TEXTURE_H__
#define C_TEXTURE_H__

#pragma once

#include "../ECS/API.h"
#include "../ECS/Component.h"
#include "TextureResource.h"

class Texture : public gecs::Component<Texture> 
{
    public:
        Texture(const gecs::ComponentTypeId& typeId, const gecs::EntityId& ownerId, const std::string& textureId)
            : gecs::Component<Texture>(typeId, ownerId) {
            // Additional initialization if needed
            m_TextureId = textureId;
        }

        [[nodiscard]] inline std::string getTextureId() const {
            return m_TextureId;
        }

    private:
        std::string m_TextureId;
        std::vector<TextureResource> resources_;
};

#endif // C_TEXTURE_H__