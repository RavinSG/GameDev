#include <iostream>
#include "Object.h"
#include "C_Sprite.h"

C_Sprite::C_Sprite(Object* owner) : Component{ owner }, currentTextureID{ -1 } {}

void C_Sprite::SetTextureAllocator(ResorceAllocator<sf::Texture>* allocator)
{
	this->allocator = allocator;
}

void::C_Sprite::Load(int id)
{
	if (id >= 0 && id != currentTextureID)
	{
		currentTextureID = id;
		std::shared_ptr<sf::Texture> texture = allocator->Get(id);
		sprite.setTexture(*texture);
	}
}

void C_Sprite::Load(const std::string& filePath)
{
	if (allocator)
	{
		int textureId = allocator->Add(filePath);
		if (textureId >= 0 && textureId != currentTextureID)
		{
			currentTextureID = textureId;
			std::shared_ptr<sf::Texture> texture = allocator->Get(textureId);
			sprite.setTexture(*texture);
		}
	}
}

void C_Sprite::SetTextureRect(int x, int y, int width, int height)
{
	sprite.setTextureRect(sf::IntRect(x, y, width, height));
}

void C_Sprite::SetTextureRect(const sf::IntRect& rect)
{
	sprite.setTextureRect(rect);
}


void C_Sprite::Draw(Window& window)
{
	window.Draw(sprite);
}

void C_Sprite::LateUpdate(float deltaTime)
{
	sprite.setPosition(owner->transform->GetPosition());
}