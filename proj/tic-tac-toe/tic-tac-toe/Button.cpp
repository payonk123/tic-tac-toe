#include "Button.h"


Button::Button(sf::Vector2f size) {
	element.setSize(size);
}


bool Button::is_mouse_on_element(sf::RenderWindow& window){
	sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
	sf::FloatRect element_size = element.getLocalBounds();
	sf::Vector2f element_position = element.getPosition();

	

	float max_width = element_position.x + element_size.width;
	float max_height = element_position.y + element_size.height;

	if (mouse_position.x < max_width && element_position.x < mouse_position.x && mouse_position.y < max_height && element_position.y < mouse_position.y) {
		return true;
	}
	else
		return false;

}