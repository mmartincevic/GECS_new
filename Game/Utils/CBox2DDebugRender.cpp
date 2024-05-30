//#include "CBox2DDebugRender.h"
//
//#include <vector>
//
//CBox2DDebugRenderer::CBox2DDebugRenderer()
//	: m_pRenderer(nullptr)
//	, m_MetersPerPixelFactor(0.0f)
//{
//
//}
//
//CBox2DDebugRenderer::CBox2DDebugRenderer(SDL_Renderer* pRenderer, const float MetersPerPixelFactor, const uint32_t DrawFlags)
//	: m_pRenderer(pRenderer)
//	, m_MetersPerPixelFactor(MetersPerPixelFactor)
//{
//	SetFlags(DrawFlags);
//}
//
//CBox2DDebugRenderer::~CBox2DDebugRenderer()
//{
//
//}
//
//void CBox2DDebugRenderer::DrawSolidPolygon(const b2Vec2* pVertices, int32 VertexCount, const b2Color& rColor)
//{
//	const SDL_Color			LineColor = ToSDLColor(rColor);
//	const SDL_Color			TriangleColor = ToSDLColor(b2Color(rColor.r * 0.5f, rColor.g * 0.5f, rColor.b * 0.5f, rColor.a * 0.5f));
//	std::vector<SDL_Vertex> Vertices;
//
//	for (int32_t i = 0; i < VertexCount; ++i)
//	{
//		if (i < (VertexCount - 2))
//		{
//			const b2Vec2 TriangleVertex[3] =
//			{
//				MeterToPixel(pVertices[0 + 0]),
//				MeterToPixel(pVertices[i + 1]),
//				MeterToPixel(pVertices[i + 2]),
//			};
//
//			for (int32_t j = 0; j < 3; ++j)
//			{
//				Vertices.push_back({ {TriangleVertex[j].x, TriangleVertex[j].y}, TriangleColor, {0.0f, 0.0f} });
//			}
//		}
//	}
//
//	SDL_RenderGeometry(m_pRenderer, nullptr, Vertices.data(), (int32_t)Vertices.size(), nullptr, 0);
//	SDL_SetRenderDrawBlendMode(m_pRenderer, SDL_BLENDMODE_BLEND);
//	SDL_SetRenderDrawColor(m_pRenderer, LineColor.r, LineColor.g, LineColor.b, LineColor.a);
//
//	for (int32_t i = 0; i < VertexCount; ++i)
//	{
//		const b2Vec2 LineStart = MeterToPixel(pVertices[i]);
//		const b2Vec2 LineEnd = MeterToPixel(pVertices[((i < (VertexCount - 1)) ? (i + 1) : 0)]);
//
//		SDL_RenderDrawLineF(m_pRenderer, LineStart.x, LineStart.y, LineEnd.x, LineEnd.y);
//	}
//}
//
//float CBox2DDebugRenderer::MeterToPixel(const float Value)
//{
//	return (Value * m_MetersPerPixelFactor);
//}
//
//b2Vec2 CBox2DDebugRenderer::MeterToPixel(const b2Vec2& rVector)
//{
//	return b2Vec2(MeterToPixel(rVector.x), MeterToPixel(rVector.y));
//}
//
//SDL_Color CBox2DDebugRenderer::ToSDLColor(const b2Color& rColor)
//{
//	return { (uint8_t)(rColor.r * 255.0f), (uint8_t)(rColor.g * 255.0f), (uint8_t)(rColor.b * 255.0f), (uint8_t)(rColor.a * 255.0f) };
//}