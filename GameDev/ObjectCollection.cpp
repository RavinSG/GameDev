#include "ObjectCollection.h"

void ObjectCollection::Update(float deltaTime)
{
	for (auto& object : objects)
	{
		object->Update(deltaTime);
	}
}

void ObjectCollection::LateUpdate(float deltaTime)
{
	for (auto& object : objects)
	{
		object->LateUpdate(deltaTime);
	}
}

void ObjectCollection::Draw(Window& window)
{
	for (auto& object : objects)
	{
		object->Draw(window);
	}
}

void ObjectCollection::Add(std::shared_ptr<Object> object)
{
	newObjects.push_back(object);
}

void ObjectCollection::ProcessNewObjects()
{
	if (newObjects.size() > 0)
	{
		for (const auto& object : newObjects)
		{
			object->Awake();
		}

		for (const auto& object : newObjects)
		{
			object->Start();
		}

		objects.assign(newObjects.begin(), newObjects.end());
		newObjects.clear();
	}

}

void ObjectCollection::ProcessRemovals()
{
	auto objectIterator = objects.begin();

	while (objectIterator != objects.end())
	{
		auto object = **objectIterator;

		if (object.IsQueuedForRemoval())
		{
			objectIterator = objects.erase(objectIterator);
		}
		else
		{
			++objectIterator;
		}
	}
}