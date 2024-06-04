#include "Tile.h"

Tile::Tile(int tilesize, int rowcount, int colcount, TileMap tilemap, TilesetList tilesets) : m_Tilesets(tilesize)
{
	m_RowCount = rowcount;
	m_ColCount = colcount;
	m_Tilemap = tilemap;
	m_Tilesets = tilesets;
}

void Tile::Update() {}
void Tile::Render() {}