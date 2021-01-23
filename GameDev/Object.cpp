#include "Object.h"

Object::Object() : queuedForRemoval{false}
{
	transform = AddComponent<C_Transform>();
}

void Object::Awake()
{
	for (auto component : components)
	{
		component->Awake();
	}
}

void Object::Start()
{
	for (auto component : components)
	{
		component->Start();
	}
}

void Object::Update(float deltaTime)
{
	for (auto component : components)
	{
		component->Update(deltaTime);
	}
}

void Object::LateUpdate(float deltaTime)
{
	for (auto component : components)
	{
		component->LateUpdate(deltaTime);
	}
}

void Object::Draw(Window& window)
{
	for (auto component : components)
	{
		drawable->Draw(window);
	}
}

void Object::QueueForRemoval() 
{
	queuedForRemoval = true;
}

bool Object::IsQueuedForRemoval()
{
	return queuedForRemoval;
}

std::shared_ptr<C_Drawable> Object::GetDrawable()
{
	return drawable;
}