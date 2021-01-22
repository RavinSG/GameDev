#pragma once

#include <vector>

struct FrameData
{
	int id;
	int x;
	int y;
	int width;
	int height;
	float displayTimeSeconds;
};

enum class FacingDirection
{
	None,
	Left,
	Right
};

class Animation
{
public:
	Animation(FacingDirection direction);

	void AddFrame(int textureID, int x, int y, int width, int height, float frameTIme);
	const FrameData* GetCurrentFrame() const;
	bool UpdateFrame(float deltaTime);
	void Reset();

	void SetDirection(FacingDirection direction);
	FacingDirection GetDirection() const;

private:
	void IncrmentFrame();

	std::vector<FrameData> frames;
	int CurrentFrameIndex;
	float CurrentFrameTime;

	FacingDirection direction;

};

