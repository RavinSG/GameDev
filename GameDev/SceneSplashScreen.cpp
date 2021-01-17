#include "SceneSplashScreen.h"

SceneSplashScreen::SceneSplashScreen(WorkingDirectory& workingDir,
	SceneStateMachine& sceneStateMachine,
	Window& window) :

	sceneStateMachine{ sceneStateMachine },
	workingDir{ workingDir },
	window{ window },
	switchToState{ 0 },
	currentSeconds{ 0.f },
	showForSeconds{ 3.f }
{}

void SceneSplashScreen::OnCreate()
{
	splashTexture.loadFromFile(workingDir.Get() + "splash.png");
	splashSprite.setTexture(splashTexture);

	sf::FloatRect spriteSize = splashSprite.getLocalBounds();

	// Set the origin of the sprite to the center of the image.
	splashSprite.setOrigin(spriteSize.width * 0.5f, spriteSize.height * 0.5f);
	splashSprite.setScale(0.5f, 0.5f);

	sf::Vector2u windowCenter = window.GetCenter();

	// Positions sprite in the center of the screen
	splashSprite.setPosition(static_cast<float>(windowCenter.x), static_cast<float>(windowCenter.y));
}

void SceneSplashScreen::OnActivate()
{
	// Resets the current second counter when activated
	currentSeconds = 0.f;
}

void SceneSplashScreen::OnDestroy() {}

void SceneSplashScreen::Update(float deltaTime)
{
	currentSeconds += deltaTime;

	if (currentSeconds >= showForSeconds)
	{
		// Switch states
		sceneStateMachine.SwitchTo(switchToState);
	}
}

void SceneSplashScreen::Draw(Window& window)
{
	window.Draw(splashSprite);
}

