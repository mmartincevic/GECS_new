#ifndef MAPPARSER_H
#define MAPPARSER_H

#pragma once

#include <map>
#include <string>
#include "Layer.h"
#include "Map.h"
#include "Tile.h"
#include "tinyxml2.h"

class MapParser
{
public:

	inline static MapParser* Instance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new MapParser(); }

	bool Load();
	void Clean();
	inline Map* Maps(std::string id) { return m_Maps[id]; }

private:
	bool Parse(std::string mapid, std::string source);
	TileSet ParseTileset(tinyxml2::XMLElement* xmlTileset);
	Layer* ParseLayer(tinyxml2::XMLElement* xmlLayer, TilesetList tilesets, int tilesize, int rowcount, int colcount);


private:
	static MapParser* s_Instance;
	MapParser();
	std::map<std::string, Map*> m_Maps;
};

#endif // MAPPARSER_H