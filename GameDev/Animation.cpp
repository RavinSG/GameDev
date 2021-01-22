#include "Animation.h"

Animation::Animation() : frames{ 0 }, CurrentFrameIndex{ 0 }, CurrentFrameTime{ 0.f } {}

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
