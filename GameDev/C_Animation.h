#pragma once

#include "Component.h"
#include "Animation.h"
#include "C_Sprite.h"

enum class AnimationState
{
	None,
	Idle,
	Walk
};

class C_Animation : public Component
{
public:
	C_Animation(Object* object);

	void Awake();
	void Update(float deltaTime);

	// Adds an animation to a object.
	void AddAnimation(AnimationState state, std::shared_ptr<Animation> animation);

	void SetAnimationState(AnimationState state);

	const AnimationState& GetAnimationState() const;
	void SetAnimationDirection(FacingDirection direction);

private:
	std::shared_ptr<C_Sprite> sprite;
	std::map<AnimationState, std::shared_ptr<Animation>> animations;

	// A reference to the current animation so we can quickly update it.
	std::pair<AnimationState, std::shared_ptr<Animation>> currentAnimation;
};

