#include "SceneGame.h"

SceneGame::SceneGame(WorkingDirectory& workingDir,
	ResorceAllocator<sf::Texture>& textureAllocator) :
	workingDir{ workingDir },
	textureAllocator{ textureAllocator } {}

void SceneGame::OnCreate()
{
	std::shared_ptr<Object> player = std::make_shared<Object>();

	auto sprite = player->AddComponent<C_Sprite>();
	sprite->SetTextureAllocator(&textureAllocator);

	auto movement = player->AddComponent<C_KeyBoardMovement>();
	movement->SetInput(&input);

	auto animation = player->AddComponent<C_Animation>();

	int vikingTextureID = textureAllocator.Add(workingDir.Get() + "viking.png");

	const int frameWidth = 165;
	const int frameHeight = 145;

	std::shared_ptr<Animation> idleAnimation = std::make_shared<Animation>();

	const float idleAnimFrameSeconds{ 0.2f };

	idleAnimation->AddFrame(vikingTextureID, 600, 0, frameWidth, frameHeight, idleAnimFrameSeconds);
	idleAnimation->AddFrame(vikingTextureID, 800, 0, frameWidth, frameHeight, idleAnimFrameSeconds);
	idleAnimation->AddFrame(vikingTextureID, 0, 145, frameWidth, frameHeight, idleAnimFrameSeconds);
	idleAnimation->AddFrame(vikingTextureID, 200, 145, frameWidth, frameHeight, idleAnimFrameSeconds);

	animation->AddAnimation(AnimationState::Idle, idleAnimation);

	objects.Add(player);
}

void SceneGame::OnDestroy() {}

void SceneGame::ProcessInput()
{
	input.Update();
}

void SceneGame::Update(float deltaTime)
{
	// Process all the new objects at the begining of each frame.
	objects.ProcessRemovals();
	objects.ProcessNewObjects();

	objects.Update(deltaTime);
}

void SceneGame::LateUpdate(float deltaTime)
{
	objects.LateUpdate(deltaTime);
}

void SceneGame::Draw(Window& window)
{
	objects.Draw(window);
}
