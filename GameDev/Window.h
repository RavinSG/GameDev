#pragma once
#include <SFML/Graphics.hpp>
class Window {
public:
	Window(const std::string& windowName);

	void Update();
	void BeginDraw();
	void Draw(const sf::Drawable& drawable);
	void EndDraw();

	sf::Vector2u GetCenter() const;

	bool isOpen() const;

private:
	sf::RenderWindow window;
};