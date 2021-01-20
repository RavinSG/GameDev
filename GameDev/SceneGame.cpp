#include "SceneGame.h"

SceneGame::SceneGame(WorkingDirectory& workingDir) : workingDir{ workingDir } {}

void SceneGame::OnCreate()
{
	player = std::make_shared<Object>();

	auto sprite = player->AddComponent<C_Sprite>();
	sprite->Load(workingDir.Get() + "viking.png");

}

void SceneGame::OnDestroy() {}

void SceneGame::ProcessInput()
{
	input.Update();
}

void SceneGame::Update(float deltaTime) 
{
	/*const sf::Vector2f& spritePos = vikingSprite.getPosition();
	const int moveSpeed = 100;

	int xMove{ 0 };
	if (input.IsKeyPressed(Input::Key::Left))
	{
		xMove = -moveSpeed;
	}
	else if (input.IsKeyPressed(Input::Key::Right))
	{
		xMove = moveSpeed;
	}

	int yMove{ 0 };
	if (input.IsKeyPressed(Input::Key::Down))
	{
		yMove = moveSpeed;
	}
	else if (input.IsKeyPressed(Input::Key::Up))
	{
		yMove = -moveSpeed;
	}

	float xFrameMove = xMove * deltaTime;
	float yFrameMove = yMove * deltaTime;

	vikingSprite.setPosition(spritePos.x + xFrameMove, spritePos.y + yFrameMove);*/
}

void SceneGame::Draw(Window& window)
{
	player->Draw(window);
}
