#include "ImageLayer.h"
#include "../Resources/SDLTexture.h"

ImageLayer::ImageLayer(std::string textureId, int x, int y, float scrollRatio, float scalex, float scaley, bool repeat)
{
    m_TextureId = textureId;
    m_OffsetX = x;
    m_OffsetY = y;
    m_ScrollRatio = scrollRatio;
    m_ScaleX = scalex;
    m_ScaleY = scaley;
    m_Repeat = repeat;
    QueryImage(m_TextureId);
}

void ImageLayer::Render() const
{
    auto textureManager = gecs::ECS_Engine.resources().Manager<SDLTexture>();
    textureManager->Draw(m_TextureId, m_OffsetX, m_OffsetY,
        m_ImgWidth, m_ImgHeight, m_ScaleX, m_ScaleY, m_ScrollRatio, 0);

}

void ImageLayer::QueryImage(std::string textureId)
{
    auto textureManager = gecs::ECS_Engine.resources().Manager<SDLTexture>();
    SDL_Texture* texture = textureManager->Texture(m_TextureId);
    SDL_QueryTexture(texture, NULL, NULL, &m_ImgWidth, &m_ImgHeight);
}

void ImageLayer::Update() {}