#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <sstream>

#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "Tile.h"
#include "Utilities.h"
#include "Object.h"
#include "C_Sprite.h"

using namespace rapidxml;

struct TileSheetData
{
	int textureID;				// The id of the tile sets texture
	sf::Vector2u imageSize;		// The size of the texture
	int columns;					// How many columns in the sheet
	int rows;					// How many rows in the sheet
	sf::Vector2u tileSize;		// The size of an individual tile
};

using Layer = std::vector<std::shared_ptr<Tile>>;

// Stores layer name with layers
using MapTiles = std::map<std::string, std::shared_ptr<Layer>>;

// Stores the different tile types that can be used
using TileSet = std::unordered_map<unsigned int, std::shared_ptr<TileInfo>>;

class TileMapParser
{
public:
	TileMapParser(ResorceAllocator<sf::Texture>& textureAllocator);

	std::vector<std::shared_ptr<Object>> Parse(const std::string& file, sf::Vector2i offset);

private:
	std::shared_ptr<TileSheetData> BuildTileSheetData(xml_node<>* rootNode);
	std::shared_ptr<MapTiles> BuildMapTiles(xml_node<>* rootNode);
	std::pair<std::string, std::shared_ptr<Layer>> BuildLayer(xml_node<>* layerNode, std::shared_ptr<TileSheetData> tileSheetData);

	ResorceAllocator<sf::Texture>& textureAllocator;
};

