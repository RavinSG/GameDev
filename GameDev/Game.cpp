#include <iostream>
#include "Game.h"
#include "Helper.h"

const std::string gameName{ "My First Game" };
Helper helper{};

Game::Game() :window(gameName)
{
	auto splashScreen = std::make_shared<SceneSplashScreen>(workingDir, sceneStateMachine, window, textureAllocator);
	auto gameScene = std::make_shared<SceneGame>(workingDir, textureAllocator);

	unsigned int splashScrennID = sceneStateMachine.Add(splashScreen);
	unsigned int gameSceneID = sceneStateMachine.Add(gameScene);

	splashScreen->SetSwitchToScene(gameSceneID);
	sceneStateMachine.SwitchTo(splashScrennID);

	deltaTime = clock.restart().asSeconds();
}

void::Game::ProcessInput()
{
	sceneStateMachine.ProcessInput();
}

void Game::Update()
{
	window.Update();
	sceneStateMachine.Update(deltaTime);
}

void Game::LateUpdate()
{
	sceneStateMachine.LateUpdate(deltaTime);
}

void Game::Draw()
{
	window.BeginDraw();
	sceneStateMachine.Draw(window);
	window.EndDraw();
}

bool Game::IsRunning() const
{
	return window.isOpen();
}

void Game::ResetTime()
{
	deltaTime = 0;
}

void Game::CalculateDeltaTime()
{
	deltaTime = clock.restart().asSeconds();
}
