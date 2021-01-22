#pragma once

#include <SFML/Graphics.hpp>

#include "Window.h"
#include "Input.h"
#include "WorkingDirectory.h"
#include "SceneStateMachine.h"
#include "SceneSplashScreen.h"
#include "SceneGame.h"

class Game {
public:
	Game();

	void ProcessInput();
	void Update();
	void LateUpdate();
	void Draw();
	void CalculateDeltaTime();
	bool IsRunning() const;

	void ResetTime();

private:
	Window window;
	WorkingDirectory workingDir;

	sf::Clock clock;
	float deltaTime{};

	ResorceAllocator<sf::Texture> textureAllocator{};
	SceneStateMachine sceneStateMachine;
	
};
