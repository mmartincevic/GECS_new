#ifndef CAMERA_H__
#define CAMERA_H__

#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "../Utils/Vector2D.h"

class WorldCamera {

public:
	void Update(Vector2D targetPosition);
	inline int SceneWidth() const { return m_SceneWidth; }
	inline int SceneHeight() const { return m_SceneHeight; }

	inline SDL_Rect GetViewBox() const { return m_ViewBox; }

	inline void MoveX(float x) { m_Position.x = x; }
	inline void MoveY(float y) { m_Position.y = y; }
	inline void SetSceneLimit(int width, int height) { m_SceneWidth = width; m_SceneHeight = height; }

	inline void SetTarget(Vector2D* target) { m_Target = target; }

	Vector2D Position() const { return m_Position; }

private:
	int m_SceneWidth;
	int m_SceneHeight;
	SDL_Rect m_ViewBox;
	Vector2D m_Position;
	Vector2D* m_Target = nullptr;
};

#endif