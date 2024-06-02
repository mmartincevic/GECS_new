#ifndef IMAGE_LAYER_H__
#define IMAGE_LAYER_H__

#pragma once
#include <iostream>

class ImageLayer
{
public:

	ImageLayer(std::string m_TextureId, int x, int y, float scrollRatio = 1.0f, float scalex = 1.0f, float scaley = 1.0f, bool repeat = false);

	inline void SetScrollRatio(float scrollRatio) { m_ScrollRatio = scrollRatio; }
	inline void SetOffset(int x, int y) { m_OffsetX = x; m_OffsetY = y; }
	inline void SetRepeat(bool repeat) { m_Repeat = repeat; }
	void QueryImage(std::string textureId);

	void Render() const;
	void Update();
private:
	std::string m_TextureId;
	float m_ScrollRatio;
	int m_OffsetX, m_OffsetY;
	int m_ImgWidth, m_ImgHeight;
	bool m_Repeat;
	float m_ScaleX;
	float m_ScaleY;
};
#endif