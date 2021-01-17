#pragma once
#include "Window.h"
#include "Input.h"
#include "WorkingDirectory.h"

class Game {
public:
	Game();

	void Update();
	void LateUpdate();
	void Draw();
	bool IsRunning() const;

	void ResetTime();
	void CalculateDeltaTime();

	void CaptureInput();

private:
	Window window;
	WorkingDirectory workingDir;

	sf::Texture vikingTeture;
	sf::Sprite vikingSprite;
	sf::Clock clock;

	float deltaTime;
	Input input;
};
