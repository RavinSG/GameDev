#pragma once

#include "Scene.h"
#include "Input.h"
#include "Object.h"
#include "C_Sprite.h"
#include "WorkingDirectory.h"
#include "C_KeyBoardMovement.h"
#include "ResorceAllocator.h"

class SceneGame : public Scene
{
public:
	SceneGame(WorkingDirectory& workingDir, ResorceAllocator<sf::Texture>& textureAllocator);

	void OnCreate() override;
	void OnDestroy() override;

	void ProcessInput() override;
	void Update(float deltaTime) override;
	void Draw(Window& window) override;
	void LateUpdate(float deltaTime) override;

private:
	std::shared_ptr<Object> player;

	WorkingDirectory workingDir{};
	Input input{};
	ResorceAllocator<sf::Texture>& textureAllocator;
};

