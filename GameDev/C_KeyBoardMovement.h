#pragma once

#include "Component.h"
#include "Input.h"

class C_KeyBoardMovement : public Component
{
public:
	C_KeyBoardMovement(Object* owner);

	void SetInput(Input* input);
	void SetMovementSpeed(int moveSpeed);

	void Update(float deltaTime) override;

private:
	int moveSpeed;
	Input* input;
};

