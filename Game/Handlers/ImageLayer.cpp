#include "ImageLayer.h"
#include "../Utils/SDL_Wrapper.h"
#include "../TextureManager.h"

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
	TextureManager::Instance().Draw(m_TextureId, m_OffsetX, m_OffsetY,
		m_ImgWidth, m_ImgHeight, m_ScaleX, m_ScaleY, m_ScrollRatio, 0);
}

void ImageLayer::QueryImage(std::string textureId)
{
	SDL_Texture* texture = TextureManager::Instance().Texture(m_TextureId);
	SDL_QueryTexture(texture, NULL, NULL, &m_ImgWidth, &m_ImgHeight);
}

void ImageLayer::Update() {}