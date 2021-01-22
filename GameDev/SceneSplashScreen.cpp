#include "SceneSplashScreen.h"

SceneSplashScreen::SceneSplashScreen(WorkingDirectory& workingDir,
	SceneStateMachine& sceneStateMachine,
	Window& window,
	ResorceAllocator<sf::Texture>& textureAllocator) :

	sceneStateMachine{ sceneStateMachine },
	workingDir{ workingDir },
	window{ window },
	textureAllocator{textureAllocator},
	switchToState{ 0 },
	currentSeconds{ 0.f },
	showForSeconds{ 5.f }
{}

void SceneSplashScreen::OnCreate()
{	
	int textureID = textureAllocator.Add(workingDir.Get() + "viking_splash.jpg");
	if (textureID >= 0) {
		std::shared_ptr<sf::Texture> texture = textureAllocator.Get(textureID);
		splashSprite.setTexture(*texture);

		sf::FloatRect spriteSize = splashSprite.getLocalBounds();

		// Set the origin of the sprite to the center of the image.
		splashSprite.setOrigin(spriteSize.width * 0.5f, spriteSize.height * 0.5f);
		splashSprite.setScale(0.5f, 0.5f);

		sf::Vector2u windowCenter = window.GetCenter();

		// Positions sprite in the center of the screen
		splashSprite.setPosition(static_cast<float>(windowCenter.x), static_cast<float>(windowCenter.y));
	}
}

void SceneSplashScreen::OnActivate()
{
	// Resets the current second counter when activated
	currentSeconds = 0.f;
}

void SceneSplashScreen::SetSwitchToScene(unsigned int id)
{
	// Store the id of the next scene that we will transition to.
	switchToState = id;
}

void SceneSplashScreen::OnDestroy() {}

void SceneSplashScreen::Update(float deltaTime)
{
	currentSeconds += deltaTime;

	if (currentSeconds >= showForSeconds)
	{
		// Switch states
		sceneStateMachine.SwitchTo(switchToState);
		std::cout << "Switching States";
	}
}

void SceneSplashScreen::Draw(Window& window)
{
	window.Draw(splashSprite);
}

