#include "TextureManager.h"
#include <iostream>

#include "../Game/Utils/Vector2D.h"
#include "../Game/World/World.h"


bool TextureManager::Load(std::string textureId, std::string filename)
{
	return TextureManager::Load(SDL_Wrapper::getInstance().getRenderer(), textureId, filename);
}

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
	int height, double angle, float ratio, SDL_RendererFlip flip)
{
	Vector2D cameraPos = World::Instance().Camera()->Position() * ratio;

	SDL_Rect srcRect, dstRect;
	srcRect.x = srcRect.y = 0;
	SDL_QueryTexture(m_TextureMap[textureId], nullptr, nullptr, &srcRect.w, &srcRect.h);

	dstRect.x = x - cameraPos.x;
	//dstRect.y = y - cameraPos.y;
	dstRect.y = y;
	dstRect.w = width;
	dstRect.h = height;

	SDL_RenderCopyEx(renderer, m_TextureMap[textureId], &srcRect, &dstRect, angle, nullptr, flip);
}

void TextureManager::Draw(std::string textureId, int x, int y, 
	int width, int height, float scalex, float scaley, float ratio, 
	double angle, SDL_RendererFlip flip)
{
	Vector2D cameraPos = World::Instance().Camera()->Position() * ratio;
	SDL_Rect srcRect = { 0, 0, width, height };
	SDL_Rect dstRect = { x - cameraPos.x, y, width * scalex, height * scaley };
	SDL_RenderCopyEx(SDL_Wrapper::getInstance().getRenderer(), m_TextureMap[textureId], &srcRect, &dstRect, angle, nullptr, flip);
}


void TextureManager::DrawTile(std::string tilesetId, int width, int height, int x, int y, int srcx, 
	int srcy, int frame, int rotation, float opacity, bool collidable, float ration, SDL_RendererFlip flip)
{
	if (opacity < 1)
	{
		Uint8 alpha = static_cast<Uint8>(opacity * 255.0f);
		SDL_SetTextureAlphaMod(m_TextureMap[tilesetId], alpha);
	}
	
	
	Vector2D cameraPos = World::Instance().Camera()->Position() * ration;
	SDL_Rect dstRect = { (x * width) - cameraPos.x, (y * width), width, height };
	SDL_Rect srcRect = { srcx * width, srcy * width, width, height };

	if (m_DrawBoundingBox && collidable)
	{
		SDL_RenderDrawRect(SDL_Wrapper::getInstance().getRenderer(), &dstRect);
	}

	SDL_RenderCopyEx(SDL_Wrapper::getInstance().getRenderer(), m_TextureMap[tilesetId], &srcRect, &dstRect, rotation, nullptr, flip);
}


void TextureManager::DrawFrame(SDL_Renderer* renderer, std::string textureId, int x, int y, int width, \
	int height, int row, int frame, SDL_RendererFlip flip)
{
	SDL_Texture* texture = m_TextureMap[textureId];
	if (!texture) {
		std::cerr << "Texture not found: " << textureId << std::endl;
		return;
	}

	SDL_Rect srcRect = { width * frame, height * (row - 1), width, height };
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

