#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

#include "SceneStateMachine.h"
#include "WorkingDirectory.h"
#include "ResorceAllocator.h"

class SceneSplashScreen : public Scene
{
public:
	SceneSplashScreen(
		WorkingDirectory& workingDir,
		SceneStateMachine& sceneStateMachine,
		Window& window,
		ResorceAllocator<sf::Texture>& textureAllocator);

	void OnCreate() override;
	void OnDestroy() override;

	void OnActivate() override;

	void SetSwitchToScene(unsigned int id);

	void Update(float deltaTime) override;
	void Draw(Window& window) override;

private:
	sf::Sprite splashSprite;

	WorkingDirectory& workingDir;
	SceneStateMachine& sceneStateMachine;
	Window& window;
	ResorceAllocator<sf::Texture>& textureAllocator;

	// Amount of time we wnat to display the splashscreen.
	float showForSeconds;

	// How long the scener has currently been visible.
	float currentSeconds;

	// The state we want to transition to when this scene timeouts.
	unsigned int switchToState;
};

