#include "Animation.h"

Animation::Animation(FacingDirection direction) :
	frames{ 0 },
	CurrentFrameIndex{ 0 },
	CurrentFrameTime{ 0.f },
	direction{ direction } {}

void Animation::AddFrame(int textureID, int x, int y, int width, int height, float frameTime)
{
	FrameData data{};
	data.id = textureID;
	data.x = x;
	data.y = y;
	data.width = width;
	data.height = height;
	data.displayTimeSeconds = frameTime;

	frames.push_back(data);
}

void Animation::SetDirection(FacingDirection direction)
{
	if (direction != this->direction)
	{
		this->direction = direction;
		for (auto& frame : frames)
		{
			frame.x += frame.width;
			frame.width *= -1;
		}
	}
}

FacingDirection Animation::GetDirection() const
{
	return direction;
}

const FrameData* Animation::GetCurrentFrame() const
{
	if (frames.size() > 0)
	{
		return &frames[CurrentFrameIndex];
	}

	return nullptr;
}

bool Animation::UpdateFrame(float deltaTime)
{
	if (frames.size() > 0)
	{
		CurrentFrameTime += deltaTime;

		if (CurrentFrameTime >= frames[CurrentFrameIndex].displayTimeSeconds)
		{
			CurrentFrameTime = 0.f;
			IncrmentFrame();
			return true;
		}

	}
	return false;
}

void Animation::IncrmentFrame()
{
	CurrentFrameIndex = (CurrentFrameIndex + 1) % frames.size();
}

void Animation::Reset()
{
	CurrentFrameIndex = 0;
	CurrentFrameTime = 0.f;
}
