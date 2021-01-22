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

class Animation
{
public:
	Animation();

	void AddFrame(int textureID, int x, int y, int width, int height, float frameTIme);
	const FrameData* GetCurrentFrame() const;
	bool UpdateFrame(float deltaTime);
	void Reset();

private:
	void IncrmentFrame();

	std::vector<FrameData> frames;
	int CurrentFrameIndex;
	float CurrentFrameTime;
};

