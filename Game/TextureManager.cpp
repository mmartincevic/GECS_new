#include "TextureManager.h"
#include <iostream>
bool TextureManager::Load(SDL_Renderer* renderer, std::string textureId, std::string filename)
{
	SDL_Surface* surface = IMG_Load(filename.c_str());
	if (surface == nullptr)
	{
		SDL_Log("FILED to load texture: %s, %s", filename.c_str(), SDL_GetError());
		return false;
	}
	 
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	if (texture == nullptr)
	{
		SDL_Log("FILED to create texture from surface: %s", SDL_GetError());
		return false;
	} 

	m_TextureMap[textureId] = texture;
	return true;
}

void TextureManager::Drop(const std::string& textureId)
{
	auto it = m_TextureMap.find(textureId);
	if (it != m_TextureMap.end()) {
		SDL_DestroyTexture(it->second);
		m_TextureMap.erase(it);
	}
}

void TextureManager::Clean()
{
	for (auto& pair : m_TextureMap) {
		SDL_DestroyTexture(pair.second);
	}
	m_TextureMap.clear();
}

void TextureManager::Draw(SDL_Renderer* renderer, std::string textureId, int x, int y, int width, 
	int height, double angle, SDL_RendererFlip flip)
{
	SDL_Rect srcRect, dstRect;
	srcRect.x = srcRect.y = 0;
	SDL_QueryTexture(m_TextureMap[textureId], nullptr, nullptr, &srcRect.w, &srcRect.h);

	dstRect.x = x;
	dstRect.y = y;
	dstRect.w = width;
	dstRect.h = height;

	SDL_RenderCopyEx(renderer, m_TextureMap[textureId], &srcRect, &dstRect, angle, nullptr, flip);
}

void TextureManager::DrawFrame(SDL_Renderer* renderer, std::string textureId, int x, int y, int width, \
	int height, int row, int frame, SDL_RendererFlip flip)
{
	SDL_Texture* texture = m_TextureMap[textureId];
	if (!texture) {
		std::cerr << "Texture not found: " << textureId << std::endl;
		return;
	}

	SDL_Rect srcRect = { width * frame, height * row, width, height };
	SDL_Rect dstRect = { x, y, width, height };

	if (SDL_RenderCopyEx(renderer, m_TextureMap[textureId], &srcRect, &dstRect, 0, nullptr, flip))
	{
		std::cerr << "SDL_RenderCopyEx Error: " << SDL_GetError() << std::endl;
	}
}

void TextureManager::DrawFrame(SDL_Renderer* renderer, std::string textureId, int x, int y, int width, 
	int height, int row, int frame, double angle, SDL_RendererFlip flip)
{
	SDL_Rect srcRect = { width * frame, height * row, width, height };
	SDL_Rect dstRect = { x, y, width, height };
	SDL_RenderCopyEx(renderer, m_TextureMap[textureId], &srcRect, &dstRect, 0, nullptr, flip);
}
