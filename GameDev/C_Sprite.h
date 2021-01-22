#pragma once

#include "Component.h"
#include "C_Transform.h"
#include "ResorceAllocator.h" 

class C_Sprite : public Component
{
public:
	C_Sprite(Object* owner);

	// Loads a sprite file
	void Load(const std::string& filePath);
	void Load(int id);

	void SetTextureAllocator(ResorceAllocator<sf::Texture>* allocator);

	// Override the dar method so we can draw our sprite
	void Draw(Window& window) override;

	void LateUpdate(float deltaTime) override;

private:
	ResorceAllocator<sf::Texture>* allocator;
	sf::Sprite sprite;
};

