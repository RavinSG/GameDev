#pragma once
#include "Window.h"
class Scene
{
public:
	// Called only once when the scene is created.
	virtual void OnCreate() = 0;

	// Called at most once when the scene is destroyed. (If a scene is not
	// removed from the game this will not be called.)
	virtual void OnDestroy() = 0;

	// Called whenever a scene is transitioned into.  
	// Can be called many times in a game cycle.
	virtual void OnActivate() {};

	// Called whenever a transition out of scene occurs.
	// Can be called many times in a game cycle.
	virtual void OnDeactivate() {};

	// Following functions can be overwritten as necessary in our scenes.
	virtual void ProcessInput() {};
	virtual void Update(float deltaTime) {};
	virtual void LateUpdate(float deltaTime) {};
	virtual void Draw(Window& window) {};
};

