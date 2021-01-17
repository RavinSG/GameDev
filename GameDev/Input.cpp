#include "Input.h"

void Input::Update()
{
	lastFrameKeys.SetMask(thisFrameKeys);

	thisFrameKeys.SetBit(static_cast<int>(Key::Left),
		(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) ||
		(sf::Keyboard::isKeyPressed(sf::Keyboard::A)));

	thisFrameKeys.SetBit(static_cast<int>(Key::Right),
		(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) ||
		(sf::Keyboard::isKeyPressed(sf::Keyboard::D)));

	thisFrameKeys.SetBit(static_cast<int>(Key::Up),
		(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) ||
		(sf::Keyboard::isKeyPressed(sf::Keyboard::W)));

	thisFrameKeys.SetBit(static_cast<int>(Key::Down),
		(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) ||
		(sf::Keyboard::isKeyPressed(sf::Keyboard::S)));

	thisFrameKeys.SetBit(static_cast<int>(Key::Esc),
		(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)));
}

bool Input::IsKeyPressed(Key keycode) {
	return thisFrameKeys.GetBit(static_cast<int>(keycode));
}

// Returns true if the key was just pressed
bool Input::IsKeyDown(Key keycode) {
	bool lastFrame = lastFrameKeys.GetBit(static_cast<int> (keycode));
	bool thisFrame = thisFrameKeys.GetBit(static_cast<int> (keycode));

	return thisFrame && !lastFrame;
}

// Returns true if the key was just released
bool Input::IsKeyUp(Key keycode) {
	bool lastFrame = lastFrameKeys.GetBit(static_cast<int> (keycode));
	bool thisFrame = thisFrameKeys.GetBit(static_cast<int> (keycode));

	return !thisFrame && lastFrame;
}