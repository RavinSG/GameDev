#include "Object.h"

Object::Object()
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
		component->Draw(window);
	}
}