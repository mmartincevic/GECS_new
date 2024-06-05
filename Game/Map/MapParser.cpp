#include "MapParser.h"
#include <iostream>
#include <sstream>

bool MapParser::Load()
{
	return Parse("level1", "assets/maps/map1.tmx");
}


void MapParser::Clean() {}


bool MapParser::Parse(std::string id, std::string source) 
{
	tinyxml2::XMLDocument xml;
	tinyxml2::XMLError eResult = xml.LoadFile("example.xml");
	
	if (eResult != tinyxml2::XML_SUCCESS) {
		std::cout << "Error loading file: " << eResult << std::endl;
		return false;
	}

	tinyxml2::XMLElement* root = xml.RootElement();
	int rowcount = 0;
	int colcount = 0;
	int tilesize = 0;
	root->IntAttribute("width", colcount);
	root->IntAttribute("height", rowcount);
	root->IntAttribute("tilesize", tilesize);

	TilesetList tilesets;
	for (tinyxml2::XMLElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("tileset"))
		{
			tilesets.push_back(ParseTileset(e));
		}
	}

	Map* gamemap = new Map();

	for (tinyxml2::XMLElement* e = root->FirstChildElement(); e != nullptr; e->NextSiblingElement())
	{
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
