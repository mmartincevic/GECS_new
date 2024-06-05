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

	static MapParser& Instance() {
		static MapParser instance;
		return instance;
	}

	bool Load();
	void Clean();
	inline Map* Maps(std::string id) { return m_Maps[id]; }

private:
	bool Parse(std::string mapid, std::string source);
	TileSet ParseTileset(tinyxml2::XMLElement* xmlTileset);
	Layer* ParseLayer(tinyxml2::XMLElement* xmlLayer, TilesetList tilesets, int tilesize, int rowcount, int colcount);


private:
	MapParser() = default;  // Default constructor
	~MapParser() = default; // Default destructor
	std::map<std::string, Map*> m_Maps;
};

#endif // MAPPARSER_H