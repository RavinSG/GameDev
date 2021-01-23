#include "TileMapParser.h"
#include <iostream>

TileMapParser::TileMapParser(ResorceAllocator<sf::Texture>& textureAllocator)
	: textureAllocator{ textureAllocator } {}

std::vector<std::shared_ptr<Object>> TileMapParser::Parse(const std::string& file, sf::Vector2i offset)
{
	char* fileLoc = new char[file.size() + 1];
	strcpy_s(fileLoc, file.size() + 1, file.c_str());

	rapidxml::file<> xmlFile(fileLoc);
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlFile.data());
	xml_node<>* rootNode = doc.first_node("map");

	// Load tile layers from XML
	std::shared_ptr <MapTiles> map = BuildMapTiles(rootNode);

	// We need to calculate tile positions in world space
	int tileSizeX = std::atoi(rootNode->first_attribute("tilewidth")->value());
	int tileSizeY = std::atoi(rootNode->first_attribute("tileheight")->value());
	int mapSizeX = std::atoi(rootNode->first_attribute("width")->value());
	int mapSizeY = std::atoi(rootNode->first_attribute("height")->value());

	// This will contain all the tiles as objects
	std::vector<std::shared_ptr<Object>> tileObjects;

	// Keep track of layer count
	int layerCount = map->size() - 1;

	for (const auto& layer : *map)
	{
		for (const auto& tile : layer.second->tiles)
		{
			std::shared_ptr<TileInfo> tileInfo = tile->properties;

			std::shared_ptr<Object> tileObject = std::make_shared<Object>();
			const unsigned int tileScale{ 3 };

			// Check visibility befreo allocating sprites
			if (layer.second->isVisible)
			{
				auto sprite = tileObject->AddComponent<C_Sprite>();
				sprite->SetTextureAllocator(&textureAllocator);
				sprite->Load(tileInfo->textureID);
				sprite->SetTextureRect(tileInfo->textureRect);
				sprite->SetScale(tileScale, tileScale);

				// Set ther sort order for drawing
				sprite->SetSortOrder(layerCount);
			}
			// Calculate world position
			float x = static_cast<float>(tile->x * tileSizeX * tileScale + offset.x);
			float y = static_cast<float>(tile->y * tileSizeY * tileScale + offset.y);

			tileObject->transform->SetPosition(x, y);
			tileObjects.emplace_back(tileObject);
		}
		layerCount--;
	}

	return tileObjects;
}

std::shared_ptr<MapTiles> TileMapParser::BuildMapTiles(xml_node<>* rootNode)
{
	std::shared_ptr<TileSheets> tileSheetData = BuildTileSheetData(rootNode);

	std::shared_ptr<MapTiles> map = std::make_shared<MapTiles>();

	// Loop through each layer of the XML document
	for (xml_node<>* node = rootNode->first_node("layer"); node; node = node->next_sibling())
	{
		std::pair<std::string, std::shared_ptr<Layer>> mapLayer = BuildLayer(node, tileSheetData);

		map->emplace(mapLayer);
	}

	return map;
}


std::shared_ptr<TileSheets> TileMapParser::BuildTileSheetData(xml_node<>* rootNode)
{
	TileSheets tileSheets;
	for (xml_node<>* tileSheetNode = rootNode->first_node("tileset"); tileSheetNode; tileSheetNode = tileSheetNode->next_sibling("tileset"))
	{
		TileSheetData tileSheetData;

		int firstid = std::atoi(tileSheetNode->first_attribute("firstgid")->value());
		int tileCount = std::atoi(tileSheetNode->first_attribute("tilecount")->value());

		tileSheetData.tileSize.x =
			std::atoi(tileSheetNode->first_attribute("tilewidth")->value());
		tileSheetData.tileSize.y =
			std::atoi(tileSheetNode->first_attribute("tileheight")->value());
		tileSheetData.columns =
			std::atoi(tileSheetNode->first_attribute("columns")->value());

		tileSheetData.rows = tileCount / tileSheetData.columns;

		xml_node<>* imageNode = tileSheetNode->first_node("image");
		tileSheetData.textureID = textureAllocator.Add(
			std::string(imageNode->first_attribute("source")->value())
		);

		tileSheetData.imageSize.x = std::atoi(imageNode->first_attribute("width")->value());
		tileSheetData.imageSize.y = std::atoi(imageNode->first_attribute("height")->value());

		tileSheets.insert(std::make_pair(firstid, std::make_shared<TileSheetData>(tileSheetData)));
	}
	return std::make_shared<TileSheets>(tileSheets);
}

std::pair<std::string, std::shared_ptr<Layer>>
TileMapParser::BuildLayer(xml_node<>* layerNode,
	std::shared_ptr<TileSheets> tileSheets)
{

	TileSet tileSet;
	std::shared_ptr<Layer> layer = std::make_shared<Layer>();

	int width = std::atoi(layerNode->first_attribute("width")->value());
	int height = std::atoi(layerNode->first_attribute("height")->value());

	xml_node<>* dataNode = layerNode->first_node("data");
	char* mapIndicies = dataNode->value();

	std::stringstream fileStream(mapIndicies);

	int count = 0;

	std::string line;
	while (fileStream.good())
	{
		std::string substr;
		std::getline(fileStream, substr, ',');

		if (!Utilities::IsInteger(substr))
		{
			// Remove special characters before parsing
			substr.erase(
				std::remove(substr.begin(), substr.end(), '\r'), substr.end());
			substr.erase(
				std::remove(substr.begin(), substr.end(), '\n'), substr.end());
		}

		int tileID = std::stoi(substr);

		if (tileID != 0)
		{
			auto itr = tileSet.find(tileID);
			if (itr == tileSet.end())
			{
				std::shared_ptr<TileSheetData> tileSheet;

				for (auto iter = tileSheets->rbegin(); iter != tileSheets->rend(); ++iter)
				{
					if (tileID >= iter->first)
					{
						tileSheet = iter->second;
						break;
					}

				}

				if (!tileSheet)
				{
					continue;
				}

				int textureX = tileID % tileSheet->columns - 1;
				int textureY = tileID / tileSheet->columns;

				std::shared_ptr<TileInfo> tileInfo =
					std::make_shared<TileInfo>(
						tileSheet->textureID, tileID,
						sf::IntRect(
							textureX * tileSheet->tileSize.x,
							textureY * tileSheet->tileSize.y,
							tileSheet->tileSize.x,
							tileSheet->tileSize.y)
						);

				itr = tileSet.insert(std::make_pair(tileID, tileInfo)).first;
			}

			std::shared_ptr<Tile> tile = std::make_shared<Tile>();

			// Bind properties to tile from set
			tile->properties = itr->second;
			tile->x = count % width - 1;
			tile->y = count / width;

			layer->tiles.emplace_back(tile);
		}

		count++;
	}

	const std::string layerName = layerNode->first_attribute("name")->value();
	bool layerVisible = true;
	xml_attribute<>* visibleAttribute = layerNode->first_attribute("visible");

	if (visibleAttribute)
	{
		layerVisible = std::stoi(visibleAttribute->value());
	}
	layer->isVisible = layerVisible;

	return std::make_pair(layerName, layer);
}