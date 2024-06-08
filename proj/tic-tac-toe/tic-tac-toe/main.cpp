#include <SFML/Graphics.hpp>
#include "Button.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(900, 900), "Kolko & Krzyzyk", sf::Style::Close);
    sf::Vector2f btnSize;
    btnSize.x = 180;
    btnSize.y = 180;
    
    Button*** array = new Button**[3];
    array[0] = new Button*[3];
    array[1] = new Button*[3];
    array[2] = new Button*[3];

    int i;
    int j;

    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++) {
            array[i][j] = new Button(btnSize);
            array[i][j]->element.setPosition(180+j*180+(j*10), 180 + i * 180+(i*10));
            array[i][j]->element.setFillColor(sf::Color::White);
        }


    
    //sf::CircleShape shape(100.f);
    //shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        window.clear(sf::Color(248, 189, 255));
        
        for (i = 0; i < 3; i++)
            for (j = 0; j < 3; j++)
                window.draw(array[i][j]->element);

        window.display();
    }

    return 0;
}