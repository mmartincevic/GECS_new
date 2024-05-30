//#ifndef DEBUG_RENDER_H
//#define DEBUG_RENDER_H
//
//#pragma once
//
//#include <box2d.h>
//#include <SDL.h>
//
//class CBox2DDebugRenderer : public b2Draw
//{
//	public:
//
//		CBox2DDebugRenderer();
//		CBox2DDebugRenderer(SDL_Renderer* pRenderer, const float MetersPerPixelFactor, const uint32_t DrawFlags);
//		~CBox2DDebugRenderer();
//
//		virtual void	DrawPolygon(const b2Vec2* pVertices, int32 VertexCount, const b2Color& rColor) override {}
//		virtual void	DrawSolidPolygon(const b2Vec2* pVertices, int32 VertexCount, const b2Color& rColor) override;
//		virtual void	DrawCircle(const b2Vec2& rCenter, float Radius, const b2Color& rColor) override {}
//		virtual void	DrawSolidCircle(const b2Vec2& rCenter, float Radius, const b2Vec2& rAxis, const b2Color& rColor) override {}
//		virtual void	DrawSegment(const b2Vec2& rPoint1, const b2Vec2& rPoint2, const b2Color& rColor) override {}
//		virtual void	DrawTransform(const b2Transform& rTransform) override {}
//		virtual void	DrawPoint(const b2Vec2& rPoint, float Size, const b2Color& rColor) override {}
//
//	private:
//
//		float			MeterToPixel(const float Value);
//		b2Vec2			MeterToPixel(const b2Vec2& rVector);
//		SDL_Color		ToSDLColor(const b2Color& rColor);
//
//	private:
//
//		SDL_Renderer* m_pRenderer;
//
//		float			m_MetersPerPixelFactor;
//
//};
//
//#endif