#include "SDLTexture.h"
#include "SDLRender.h"
#include "../Game/World/World.h"


void SDLTexture::Draw(std::string textureId, int x, int y,
    int width, int height, float scalex, float scaley, float ratio,
    double angle, SDL_RendererFlip flip)
{
    Vector2D cameraPos = m_Camera->Position() * ratio;
    SDL_Rect srcRect = { 0, 0, width, height };
    SDL_Rect dstRect = { x - cameraPos.x, y, width * scalex, height * scaley };

    //SDL_RenderCopyEx(m_Render, m_TextureMap[textureId], &srcRect, &dstRect, angle, nullptr, flip);
    m_Render->DrawTexture(m_TextureMap[textureId], &srcRect, &dstRect, angle, nullptr, flip);
}


void SDLTexture::DrawFrame(std::string textureId, Vector2D position, int width,
    int height, int row, int frame, double angle, SDL_RendererFlip flip)
{

    Vector2D cameraPos = m_Camera->Position();
    SDL_Rect srcRect = { width * frame, height * (row -1), width, height };

    std::cout << "Camera pos : " << position.x << " - " << position.x - cameraPos.x << " - " << cameraPos.x << std::endl;

    float x = 0;
    if (cameraPos.x == 0)
    {
        x = position.x;
    }
    else
    {
        x = 448.0f;
    }
    SDL_Rect dstRect = { position.x - cameraPos.x, position.y - cameraPos.y, width, height };
    m_Render->DrawTexture(m_TextureMap[textureId], &srcRect, &dstRect, angle, nullptr, flip);
}

void SDLTexture::DrawTile(std::string tilesetId, int width, int height, int x, int y, int srcx,
    int srcy, int frame, int rotation, float opacity, bool collidable, float ration, SDL_RendererFlip flip)
{
    if (opacity < 1)
    {
        Uint8 alpha = static_cast<Uint8>(opacity * 255.0f);
        SDL_SetTextureAlphaMod(m_TextureMap[tilesetId], alpha);
    }


    Vector2D cameraPos = m_Camera->Position() * ration;
    SDL_Rect dstRect = { (x * width) - cameraPos.x, (y * width), width, height };
    SDL_Rect srcRect = { srcx * width, srcy * width, width, height };

    if (m_DrawBoundingBox && collidable)
    {
        //SDL_RenderDrawRect(m_Render, &dstRect);
        //m_Render->DrawRect(dstRect);
    }

    //SDL_RenderCopyEx(m_Render, m_TextureMap[tilesetId], &srcRect, &dstRect, rotation, nullptr, flip);
    m_Render->DrawTexture(m_TextureMap[tilesetId], &srcRect, &dstRect, rotation, nullptr, flip);
}


bool SDLTexture::Load(std::string textureId, std::string filename)
{
    SDL_Texture* texture = m_Render->LoadTexture(textureId, filename);

    if (texture == nullptr)
    {
        return false;
    }

    m_TextureMap[textureId] = texture;
    return true;
}

void SDLTexture::Drop(const std::string& textureId)
{
    auto it = m_TextureMap.find(textureId);
    if (it != m_TextureMap.end()) {
        SDL_DestroyTexture(it->second);
        m_TextureMap.erase(it);
    }
}


void SDLTexture::Initialize() 
{
    m_Render = gecs::ECS_Engine.resources().Manager<SDLRender>();
    m_Camera = gecs::ECS_Engine.resources().Manager<SDLCamera>();
}


void SDLTexture::Cleanup() {}

void SDLTexture::Clear() 
{
    for (auto& pair : m_TextureMap) {
        SDL_DestroyTexture(pair.second);
    }
    m_TextureMap.clear();
}