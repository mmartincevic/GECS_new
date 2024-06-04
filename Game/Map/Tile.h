#ifndef MAPTILELAYER_H
#define MAPTILELAYER_H

#pragma once
#include "Layer.h"
#include <vector>
#include <string>


struct TileSet
{
	int FirstID, LastID;
	int RowCount, ColCount;
	int TileCount, TileSize;
	std::string Name, Source;
};

using TilesetList = std::vector<TileSet>;
using TileMap = std::vector<std::vector<int>>;


class Tile : public Layer
{
	public:
		Tile(int tilesize, int rowcount, int colcount, TileMap tilemap, TilesetList tilesets);
		virtual void Update() override;
		virtual void Render() override;
		inline TileMap Tilemap() { return m_Tilemap; }

	private:
		int m_TileSize;
		int m_NumRows;

		int m_RowCount;
		int m_ColCount;

		TileMap m_Tilemap;
		TilesetList m_Tilesets;
};
#endif // MAPTILELAYER_H