#include "Tiller.h"

#include <filesystem>
#include <iostream>
#include <sstream>

#include <vector>
#include <string>

#include "../TextureManager.h"

using namespace tiller;


TileError Tiller::Load(std::string filePath, std::string tmxName)
{
	m_Path = filePath;
	auto fullPath = filePath + tmxName + ".tmx";
	Log(GREEN, "Loading file: " + fullPath);
	return Parse(tmxName, fullPath);
}

void Tiller::Render()
{
	for (auto group : m_Map->ParsedData())
	{
		int groupId = group.first;

		for (auto layer : group.second)
		{
			int layerId = layer.first;

			for (Tile tile : layer.second)
			{
				TextureManager::Instance().DrawTile(
					tile.imageName, tile.width, tile.height, 
					tile.displayCol, tile.displayRow,
					tile.matrixCol, tile.matrixRow,
					1, tile.rotation, tile.opacity);
			}
		}
	}
}

TileError Tiller::Parse(std::string mapId, std::string source)
{
	TileError status;
	status.result = TileResult::TOK;

	tinyxml2::XMLDocument xml;
	tinyxml2::XMLError eResult = xml.LoadFile(source.c_str());

	if (eResult != tinyxml2::XML_SUCCESS) {
		Log(RED, "Error loading file: " + eResult);
		status.result = TileResult::TERROR;
		return status;
	}

	tinyxml2::XMLElement* root = xml.RootElement();

	m_Map = new TileMap(mapId, source, root->Attribute("orientation"),
		root->IntAttribute("width", 0), root->IntAttribute("height", 0), 
		root->IntAttribute("tilewidth", 0), root->IntAttribute("tileheight", 0));


	// Fetch tilesets
	Tileset tileset;
	for (tinyxml2::XMLElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("tileset"))
		{
			if (e->ClosingType() == tinyxml2::XMLElement::ElementClosingType::OPEN)
			{
				tileset = ParseTileset(e);
			}
			else
			{
				tileset = ParseClosedTileset(e);
				tileset.ID = e->IntAttribute("firstgid");
			}

			Log(GREEN, "Loading tileset: " + tileset.ID);
			m_Map->AddTileset(tileset);
		}
	}

	tinyxml2::XMLElement* hasGroups = root->FirstChildElement("group");

	if (!hasGroups)
	{
		// Create a fake group
		TileGroup tilegroup;
		tilegroup.ID = 1;
		tilegroup.Opacity = 1.0f;
		tilegroup.Name = "no-group-fake";
		m_Map->AddGroup(tilegroup);

		Log(YELLOW, "Loading group: " + tilegroup.ID);
		for (tinyxml2::XMLElement* l = root->FirstChildElement(); l != nullptr; l = l->NextSiblingElement())
		{
			if (l->Value() == std::string("layer"))
			{
				TileLayer tilelayer;
				tilelayer.ID = l->IntAttribute("id", 0);
				tilelayer.Name = l->Attribute("name");
				tilelayer.Width = l->IntAttribute("width", 0);
				tilelayer.Height = l->IntAttribute("height", 0);
				tilelayer.OffsetX = l->IntAttribute("offsetx", 0);
				tilelayer.OffsetY = l->IntAttribute("offsety", 0);

				Log(YELLOW, "Loading tilelayer: " + std::to_string(tilelayer.ID), "\t");
				m_Map->AddLayer(tilelayer);

				std::vector<std::vector<unsigned>> dataParsed = ParseLayerData(l, tilelayer);

				Log(GREEN, "SAVING DATA " + std::to_string(tilegroup.ID) + " - " + std::to_string(tilelayer.ID), "\t");
				m_Map->AddRawData(tilegroup.ID, tilelayer.ID, dataParsed);

				m_Map->AddFormattedData(tilegroup.ID, tilelayer.ID, FormatLayerData(tilegroup, tilelayer, dataParsed));
			}
		}
	}
	else
	{
		// If there are groups go by group -> layer
		for (tinyxml2::XMLElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
		{
			if (e->Value() == std::string("group"))
			{
				TileGroup tilegroup;
				tilegroup.ID = e->IntAttribute("id", 0);
				tilegroup.Opacity = e->FloatAttribute("opacity", 1.0f);
				tilegroup.Name = e->Attribute("name");
				m_Map->AddGroup(tilegroup);

				Log(YELLOW, "Loading group: " + tilegroup.ID);
				for (tinyxml2::XMLElement* l = e->FirstChildElement(); l != nullptr; l = l->NextSiblingElement())
				{
					if (l->Value() == std::string("layer"))
					{
						TileLayer tilelayer;
						tilelayer.ID = l->IntAttribute("id", 0);
						tilelayer.Name = l->Attribute("name");
						tilelayer.Width = l->IntAttribute("width", 0);
						tilelayer.Height = l->IntAttribute("height", 0);
						tilelayer.OffsetX = l->IntAttribute("offsetx", 0);
						tilelayer.OffsetY = l->IntAttribute("offsety", 0);

						Log(YELLOW, "Loading tilelayer: " + std::to_string(tilelayer.ID), "\t");
						m_Map->AddLayer(tilelayer);

						std::vector<std::vector<unsigned>> dataParsed = ParseLayerData(l, tilelayer);

						Log(GREEN, "SAVING DATA " + std::to_string(tilegroup.ID) + " - " + std::to_string(tilelayer.ID), "\t");
						m_Map->AddRawData(tilegroup.ID, tilelayer.ID, dataParsed);

						m_Map->AddFormattedData(tilegroup.ID, tilelayer.ID, FormatLayerData(tilegroup, tilelayer, dataParsed));
					}
				}

			}
		}
	}
	

	return status;
}

unsigned extractTileID(unsigned value) {
	// Mask out the flags to get the actual tile ID
	return value & ~(FLIPPED_HORIZONTALLY_FLAG |
		FLIPPED_VERTICALLY_FLAG |
		FLIPPED_DIAGONALLY_FLAG |
		ROTATED_HEXAGONAL_120_FLAG);
}

int getRotationForTileFlip(TileFlip const flip)
{
	switch (flip)
	{
	case HORIZONTAL: return 180; // Horizontal flip is equivalent to 180 degrees rotation
	case VERTICAL: return 180; // Vertical flip is also equivalent to 180 degrees rotation
	case DIAGONAL: return 90; // Assuming diagonal flip is a 90 degrees rotation
	case HEXAGONAL: return 120; // Hexagonal 120 degrees rotation
	default: return 0; // No rotation for undefined cases
	}
}

std::vector<Tile> Tiller::FormatLayerData(TileGroup tileGroup, TileLayer tileLayer, std::vector<std::vector<unsigned>> rawData)
{
	std::vector<Tile> fData;

	for (int row = 0; row < rawData.size(); ++row)
	{
		for (int col = 0; col < rawData[row].size(); ++col)
		{
			auto gId = rawData[row][col];

			if (gId > 0)
			{
				unsigned global_tile_id = gId;

				bool flipped_horizontally = (global_tile_id & FLIPPED_HORIZONTALLY_FLAG);
				bool flipped_vertically = (global_tile_id & FLIPPED_VERTICALLY_FLAG);
				bool flipped_diagonally = (global_tile_id & FLIPPED_DIAGONALLY_FLAG);
				bool rotated_hex120 = (global_tile_id & ROTATED_HEXAGONAL_120_FLAG);


				global_tile_id &= ~(FLIPPED_HORIZONTALLY_FLAG |
					FLIPPED_VERTICALLY_FLAG |
					FLIPPED_DIAGONALLY_FLAG |
					ROTATED_HEXAGONAL_120_FLAG);


				auto firstgid = m_Map->FindFirstGid(global_tile_id);

				Tile tile;
				tile.gID = gId;
				tile.lID = global_tile_id - *firstgid;

				int matrixRow = tile.lID / m_Map->GetTileset(*firstgid).Columns;
				int matrixColumn = tile.lID % m_Map->GetTileset(*firstgid).Columns;
				
				tile.displayRow = row;
				tile.displayCol = col;
				tile.matrixRow = matrixRow;
				tile.matrixCol = matrixColumn;
				tile.groupID = tileGroup.ID;
				tile.layerID = tileLayer.ID;
				tile.opacity = tileGroup.Opacity; // not good
				tile.width = m_Map->GetTileset(*firstgid).TileWidth;
				tile.height = m_Map->GetTileset(*firstgid).TileHeight;
				tile.imageSrc = m_Map->GetTileset(*firstgid).ImgSource;
				tile.imageName = m_Map->GetTileset(*firstgid).Name;
				tile.tilesetID = *firstgid;

				int finalRotation = 0;

				if (flipped_horizontally) {
					finalRotation += getRotationForTileFlip(tiller::TileFlip::HORIZONTAL);
				}
				else if (flipped_vertically) {
					finalRotation += getRotationForTileFlip(tiller::TileFlip::VERTICAL);
				}
				else if (flipped_diagonally) {
					finalRotation += getRotationForTileFlip(tiller::TileFlip::DIAGONAL);
				}
				else if (rotated_hex120) {
					finalRotation += getRotationForTileFlip(tiller::TileFlip::HEXAGONAL);
				}
				finalRotation = finalRotation % 360;

				tile.rotation = finalRotation;

				fData.push_back(tile);
			}
		}
	}

	return fData;
}

std::vector<std::vector<unsigned>> Tiller::ParseLayerData(tinyxml2::XMLElement* xmlLayer, TileLayer& layer) {
	tinyxml2::XMLElement* data = nullptr;
	std::vector<std::vector<unsigned>> dataParsed(layer.Height, std::vector<unsigned>(layer.Width, 0));

	for (tinyxml2::XMLElement* e = xmlLayer->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
		if (strcmp(e->Value(), "data") == 0) {
			data = e;
			break;
		}
	}

	if (!data) {
		Log(RED, "No data element found in layer", "\t");
		return dataParsed;
	}

	const char* dataText = data->GetText();
	if (!dataText) {
		Log(RED, "No text found in data element", "\t");
		return dataParsed;
	}

	std::string matrix(dataText);
	std::istringstream iss(matrix);
	std::string id;

	for (int row = 0; row < layer.Height; ++row) {
		for (int col = 0; col < layer.Width; ++col) {
			getline(iss, id, ',');
			std::stringstream convertor(id);
			convertor >> dataParsed[row][col];

			if (!iss.good())
			{
				break;
			}
		}
	}

	return dataParsed;
}

Tileset Tiller::ParseTileset(tinyxml2::XMLElement* xmlTileset)
{
	Tileset tileset;
	tileset.ID = xmlTileset->IntAttribute("firstgid");
	tileset.Name = xmlTileset->Attribute("name");
	tileset.TileWidth = xmlTileset->IntAttribute("tilewidth");
	tileset.TileHeight = xmlTileset->IntAttribute("tileheight");
	tileset.TileCount = xmlTileset->IntAttribute("tilecount");
	tileset.Columns = xmlTileset->IntAttribute("columns");
	tileset.LastID = (tileset.ID + tileset.TileCount) - 1;
	tileset.RowCount = tileset.TileCount / tileset.Columns;

	tinyxml2::XMLElement* image = xmlTileset->FirstChildElement();
	std::string imgSource = image->Attribute("source");

	std::filesystem::path imgBasePath(m_Path);
	std::filesystem::path imgRelativePath(imgSource);
	std::filesystem::path fullPath = imgBasePath / imgRelativePath;
	fullPath = fullPath.lexically_normal();
	tileset.ImgSource = fullPath.string();


	return tileset;
}

Tileset Tiller::ParseClosedTileset(tinyxml2::XMLElement* xmlTileset)
{
	auto sourceFile = xmlTileset->Attribute("source");

	tinyxml2::XMLDocument xml;

	Log(GREEN, "Loading tileset: " + (m_Path + sourceFile));
	Tileset tileset;

	tinyxml2::XMLError eResult = xml.LoadFile((m_Path + sourceFile).c_str());
	if (eResult != tinyxml2::XML_SUCCESS) {
		Log(RED, "Error loading tileset file: " + eResult);
		return tileset;
	}

	// TODO: Should raise error
	if (eResult != tinyxml2::XML_SUCCESS) {
		Log(RED, "Error loading file: " + eResult);
		return tileset;
	}

	tinyxml2::XMLElement* root = xml.RootElement();
 	tileset.Name = root->Attribute("name");
	tileset.TileWidth = root->IntAttribute("tilewidth");
	tileset.TileHeight = root->IntAttribute("tileheight");
	tileset.TileCount = root->IntAttribute("tilecount");
	tileset.Columns = root->IntAttribute("columns");
	tileset.LastID = (tileset.ID + tileset.TileCount) - 1;
	tileset.RowCount = tileset.TileCount / tileset.Columns;
	tinyxml2::XMLElement* image = root->FirstChildElement();


	std::string imgSource = image->Attribute("source");
	std::filesystem::path imgBasePath(m_Path);
	std::filesystem::path imgRelativePath(imgSource);
	std::filesystem::path fullPath = imgBasePath / imgRelativePath;
	fullPath = fullPath.lexically_normal();
	tileset.ImgSource = fullPath.string();

	return tileset;
}

void Tiller::PrintTile(const Tile& tile) {
	std::cout << "Tile properties:" << std::endl;
	std::cout << "gID: " << tile.gID << std::endl;
	std::cout << "lID: " << tile.lID << std::endl;
	std::cout << "tilesetID: " << tile.tilesetID << std::endl;
	std::cout << "layerID: " << tile.layerID << std::endl;
	std::cout << "groupID: " << tile.groupID << std::endl;
	std::cout << "opacity: " << tile.opacity << std::endl;
	std::cout << "width: " << tile.width << std::endl;
	std::cout << "height: " << tile.height << std::endl;
	std::cout << "DST row: " << tile.displayRow << std::endl;
	std::cout << "DST col: " << tile.displayCol << std::endl;
	std::cout << "SRC row: " << tile.matrixRow << std::endl;
	std::cout << "SRC col: " << tile.matrixCol << std::endl;
	std::cout << "imageSrc: " << tile.imageSrc << std::endl;
	std::cout << "rotation: " << tile.rotation << std::endl;
}