#pragma once

#include "Component.h"

class C_Sprite : public Component
{
public:
	C_Sprite(Object* owner);

	// Loads a sprite file
	void Load(const std::string& filePath);

	// Override the dar method so we can draw our sprite
	void Draw(Window& window) override;

private:
	sf::Texture texture;
	sf::Sprite sprite;
};

