#pragma once

#include <SFML/Graphics.hpp>
#include "ResorceAllocator.h"

struct TileInfo
{
	TileInfo() : tileID(-1) {}

	TileInfo(int textureID, unsigned int tileID, sf::IntRect texturRect) :
		tileID{ tileID },
		textureID{ textureID },
		textureRect{ textureRect } {}

	unsigned int tileID;
	int textureID;
	sf::IntRect textureRect;
};

struct Tile
{
	std::shared_ptr<TileInfo> properties;
	int x;
	int y;
};
