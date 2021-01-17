#pragma once
#include <SFML/Graphics.hpp>
#include "Bitmask.h"

class Input
{
public:

	enum class Key
	{
		None = 0,
		Left = 1,
		Right = 2,
		Up = 3,
		Down = 4,
		Esc = 5
	};

	bool IsKeyPressed(Key keycode);
	bool IsKeyDown(Key keycode);
	bool IsKeyUp(Key keycode);

	void Update();

private:
	Bitmask thisFrameKeys;
	Bitmask lastFrameKeys;
};

