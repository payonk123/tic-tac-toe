#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include<SFML/Graphics/RenderWindow.hpp>
#include<SFML/Window/Mouse.hpp>


class Button
{
public:
	sf::RectangleShape element;
	bool flag = false;

	Button(sf::Vector2f size);

	//ustaliæ po³o¿enie i rozmiar element
	//ustaliæ czy element jest oflagowany
	

	bool is_mouse_on_element(sf::RenderWindow& window);



};

