#ifndef TILLER_H
#define TILLER_H

#pragma once

#include <map>
#include <string>
#include "tinyxml2.h"
#include "TillerError.h"
#include "TileMap.h"

#define ENDL "\n"
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"

namespace tiller {


    const unsigned FLIPPED_HORIZONTALLY_FLAG = 0x80000000;
    const unsigned FLIPPED_VERTICALLY_FLAG = 0x40000000;
    const unsigned FLIPPED_DIAGONALLY_FLAG = 0x20000000;
    const unsigned ROTATED_HEXAGONAL_120_FLAG = 0x10000000;

    class Tiller
    {
        public:

            static Tiller& Instance() {
                static Tiller tiller_isntance;
                return tiller_isntance;
            }

            TileError Load(std::string filePath, std::string tmxName);
            
            Tileset ParseTileset(tinyxml2::XMLElement* xmlTileset);
            Tileset ParseClosedTileset(tinyxml2::XMLElement* xmlTileset);
            std::vector<std::vector<unsigned>> ParseLayerData(tinyxml2::XMLElement* xmlLayer, TileLayer& layer);
            std::vector<Tile> FormatLayerData(TileGroup tileGroup, TileLayer tileLayer, std::vector<std::vector<unsigned>> rawData);
            void PrintTile(const Tile& tile);

            void EnableLog() { enableLogging = true; }
            void DisableLog() { enableLogging = false; }

            void Log(const char* color, const std::string& stringToLog, const char* add = "") {
                if (enableLogging)
                {
                    std::cout << color << add << "TILLER - " << stringToLog << RESET << ENDL;
                }
            }
            void Render();
            inline std::map<int, Tileset>& TileSet() { return m_Map->TileSet(); }

            inline TileMap* Map() { return m_Map; }
            std::vector<Tile> Colliders() { return m_Map->ColliderTiles(); }

            void RegisterImguiWindow();

            inline std::map<int, std::map<int, std::vector<Tile>>> ParsedData() { return m_Map->ParsedData(); }

        private:
            TileError Parse(std::string mapId, std::string);


        private:
            Tiller() = default;  // Default constructor
            ~Tiller() = default; // Default destructor

            bool enableLogging = false;

            // TODO : Delete ptr
            TileMap* m_Map;
            std::string m_Path; 
    };

};

#endif // TILLER_H