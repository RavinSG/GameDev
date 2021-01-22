#pragma once

#include <vector>

#include "Window.h"
#include "Component.h"
#include "C_Transform.h"

class Object
{
public:
	Object();

	std::shared_ptr<C_Transform> transform;
	// Awake is alled when the object is created. Used to ensure
	// all required components are present
	void Awake();

	// Start is called after Awake method to initialize the components.
	void Start();

	void Update(float deltaTime);
	void LateUpdate(float deltaTime);
	void Draw(Window& window);

	bool IsQueuedForRemoval();
	void QueueForRemoval();

	template <typename T> std::shared_ptr<T> AddComponent()
	{
		// This endures that we only try to add a class that derives
		// from Component. This is tested at compile time.
		static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");

		// Checks that we don't already have a component of this type.
		for (auto& exsistingComponent : components)
		{
			// This might be change in the future
			if (std::dynamic_pointer_cast<T>(exsistingComponent))
			{
				return std::dynamic_pointer_cast<T>(exsistingComponent);
			}
		}

		// We create the component and add it to the list.
		std::shared_ptr<T> newComponent = std::make_shared<T>(this);
		components.push_back(newComponent);
		return newComponent;
	}

	template <typename T> std::shared_ptr<T> GetComponent()
	{
		static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");

		for (auto& exsistingComponent : components)
		{
			if (std::dynamic_pointer_cast<T>(exsistingComponent))
			{
				return std::dynamic_pointer_cast<T>(exsistingComponent);
			}
		}

		return nullptr;
	}

private:
	std::vector<std::shared_ptr<Component>> components;
	bool queuedForRemoval;
};

