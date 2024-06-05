#include "MapParser.h"
#include <iostream>
#include <sstream>

bool MapParser::Load()
{
	return Parse("level1", "resources/ECS/level1/mainlevel.tmx");
}


void MapParser::Clean() 
{
	std::map<std::string, Map*>::iterator it;
	for (it = m_Maps.begin(); it != m_Maps.end(); ++it)
	{
		delete it->second;
		it->second = nullptr;
	}

	m_Maps.clear();
}


bool MapParser::Parse(std::string id, const char* source) 
{
	tinyxml2::XMLDocument xml;
	tinyxml2::XMLError eResult = xml.LoadFile(source);
	
	if (eResult != tinyxml2::XML_SUCCESS) {
		std::cout << "Error loading file: " << eResult << std::endl;
		return false;
	}

	tinyxml2::XMLElement* root = xml.RootElement();
	int colcount = root->IntAttribute("width", 0);
	int rowcount = root->IntAttribute("height", 0);
	int tilesize = root->IntAttribute("tilewidth", 0);

	TilesetList tilesets;
	for (tinyxml2::XMLElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("tileset"))
		{
			tilesets.push_back(ParseTileset(e));
		}
	}

	Map* gamemap = new Map();
	for (tinyxml2::XMLElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		std::cout << "Value : " << e->Value() << std::endl;
 		if (e->Value() == std::string("layer"))
		{
			Layer* tilelayer = ParseLayer(e, tilesets, tilesize, rowcount, colcount);
			gamemap->m_MapLayers.push_back(tilelayer);
		}
	}

	m_Maps[id] = gamemap;
	return true;
}

TileSet MapParser::ParseTileset(tinyxml2::XMLElement* xmlTileset)
{
	TileSet tileset;
	tileset.Name = xmlTileset->Attribute("name");
	tileset.FirstID = xmlTileset->IntAttribute("fistgid");
	tileset.TileCount = xmlTileset->IntAttribute("tilecount");
	tileset.LastID = (tileset.FirstID + tileset.TileCount) - 1;
	tileset.ColCount = xmlTileset->IntAttribute("columns");
	tileset.RowCount = tileset.TileCount / tileset.ColCount;
	tileset.TileSize = xmlTileset->IntAttribute("tilewidth");

	tinyxml2::XMLElement* image = xmlTileset->FirstChildElement();
	tileset.Source = image->Attribute("source");
	return tileset;
}


Layer* MapParser::ParseLayer(tinyxml2::XMLElement* xmlLayer, TilesetList tilesets, int tilesize, int rowcount, int colcount) {
	tinyxml2::XMLElement* data = nullptr;

	for (tinyxml2::XMLElement* e = xmlLayer->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
		if (strcmp(e->Value(), "data") == 0) {
			data = e;
			break;
		}
	}

	if (!data) {
		std::cerr << "No data element found in layer" << std::endl;
		return nullptr;
	}

	const char* dataText = data->GetText();
	if (!dataText) {
		std::cerr << "No text found in data element" << std::endl;
		return nullptr;
	}

	std::string matrix(dataText);
	std::cout << "Matrix: " << matrix << std::endl; // Debug: print the matrix content

	std::istringstream iss(matrix);
	std::string id;

	TileMap tilemap(rowcount, std::vector<int>(colcount, 0));

	for (int row = 0; row < rowcount; ++row) {
		for (int col = 0; col < colcount; ++col) {
			if (!getline(iss, id, ',')) {
				std::cerr << "Error reading tile ID from data" << std::endl;
				return nullptr;
			}
			std::stringstream convertor(id);
			convertor >> tilemap[row][col];
		}
	}

	return new Tile(tilesize, rowcount, colcount, tilemap, tilesets);
}
