#include "Tile.h"
#include "../TextureManager.h"



Tile::Tile(int tilesize, int rowcount, int colcount, TileMap tilemap, TilesetList tilesets) : m_Tilesets(tilesize), m_RowCount(rowcount),
m_ColCount(colcount), m_Tilemap(tilemap)
{

	for (unsigned int i = 0; i < m_Tilesets.size(); ++i)
	{
		TextureManager::Instance().Load(m_Tilesets[i].Name, "assets/maps/" + m_Tilesets[i].Source);
	}
}


void Tile::Render() 
{
	for (unsigned int i = 0; i < m_RowCount; ++i)
	{
		for (unsigned int j = 0; j < m_ColCount; ++j)
		{
			int tileID = m_Tilemap[i][j];
			

			if (tileID == 0) { continue; }
			else
			{
				int index;

				if (m_Tilesets.size() > 1) 
				{ 
					for (unsigned int k = 1; k < m_Tilesets.size(); ++k)
					{
						if (tileID > m_Tilesets[k].FirstID && tileID < m_Tilesets[k].LastID)
						{
							tileID = tileID + m_Tilesets[k].TileCount - m_Tilesets[k].LastID;
							index = k;
							break;
						}
					}
				}

				TileSet ts = m_Tilesets[index];
				int tileRow = tileID / ts.ColCount;
				int tileCol = tileID - tileRow * ts.ColCount - 1;

				if (tileID % ts.ColCount == 0)
				{
					--tileRow;
					tileCol = ts.ColCount - 1;
				}

				TextureManager::Instance().DrawTile(ts.Name, ts.TileSize, j * ts.TileSize, i * ts.TileSize, tileRow, tileCol);
			}
		}
	}
}

void Tile::Update() {}