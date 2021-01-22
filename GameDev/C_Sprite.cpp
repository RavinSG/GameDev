#include <iostream>
#include "Object.h"
#include "C_Sprite.h"

C_Sprite::C_Sprite(Object* owner) : Component{ owner } {}

void C_Sprite::SetTextureAllocator(ResorceAllocator<sf::Texture>* allocator)
{
	this->allocator = allocator;
}

void::C_Sprite::Load(int id)
{
	if (id >= 0)
	{
		std::shared_ptr<sf::Texture> texture = allocator->Get(id);
	}
}

void C_Sprite::Load(const std::string& filePath)
{
	if (allocator)
	{
		int textureId = allocator->Add(filePath);
		if (textureId >= 0)
		{
			std::shared_ptr<sf::Texture> texture = allocator->Get(textureId);
			sprite.setTexture(*texture);
		}
	}
}


void C_Sprite::Draw(Window& window)
{
	window.Draw(sprite);
}

void C_Sprite::LateUpdate(float deltaTime)
{
	sprite.setPosition(owner->transform->GetPosition());
}