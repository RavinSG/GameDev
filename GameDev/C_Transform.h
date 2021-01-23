#pragma once

#include "Component.h"
class C_Transform : public Component
{
public:
	C_Transform(Object* owner);

	void SetPosition(float x, float y);
	void SetPosition(sf::Vector2f pos);

	void AddPosition(float x, float y);
	void AddPosition(sf::Vector2f pos);

	void SetX(float x);
	void SetY(float y);

	void AddX(float x);
	void AddY(float y);

	void SetStatic(bool isStatic);
	bool isStatic() const;

	const sf::Vector2f& GetPosition() const;

private:
	sf::Vector2f position;
	bool isStaticTransform;
};

