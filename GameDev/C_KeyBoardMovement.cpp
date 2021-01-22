#include "C_KeyBoardMovement.h"
#include "Object.h"

C_KeyBoardMovement::C_KeyBoardMovement(Object* owner) :Component{ owner }, moveSpeed{ 150 } {}

void C_KeyBoardMovement::SetInput(Input* input)
{
	this->input = input;
}

void C_KeyBoardMovement::SetMovementSpeed(int moveSpeed)
{
	this->moveSpeed = moveSpeed;
}

void C_KeyBoardMovement::Awake()
{
	animation = owner->GetComponent<C_Animation>();
}

void C_KeyBoardMovement::Update(float deltaTime)
{

	if (input == nullptr)
	{
		return;
	}

	int xMove{ 0 };
	if (input->IsKeyPressed(Input::Key::Left))
	{
		xMove = -moveSpeed;
		animation->SetAnimationDirection(FacingDirection::Left);
	}
	else if (input->IsKeyPressed(Input::Key::Right))
	{
		xMove = moveSpeed;
		animation->SetAnimationDirection(FacingDirection::Right);
	}

	int yMove{ 0 };
	if (input->IsKeyPressed(Input::Key::Down))
	{
		yMove = moveSpeed;
	}
	else if (input->IsKeyPressed(Input::Key::Up))
	{
		yMove = -moveSpeed;
	}

	if (xMove == 0 && yMove == 0)
	{
		animation->SetAnimationState(AnimationState::Idle);
	}
	else
	{
		animation->SetAnimationState(AnimationState::Walk);
	}

	float xFrameMove = xMove * deltaTime;
	float yFrameMove = yMove * deltaTime;

	owner->transform->AddPosition(xFrameMove, yFrameMove);
}
