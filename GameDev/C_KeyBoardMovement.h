#pragma once

#include "Component.h"
#include "Input.h"
#include "C_Animation.h"

class C_KeyBoardMovement : public Component
{
public:
	C_KeyBoardMovement(Object* owner);

	void SetInput(Input* input);
	void SetMovementSpeed(int moveSpeed);

	void Awake() override;
	void Update(float deltaTime) override;

private:
	int moveSpeed;
	Input* input;

	std::shared_ptr<C_Animation> animation;
};

