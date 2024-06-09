#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Game.h"

int main()
{

    int result = -2;

    Game board;
    sf::Texture X_turn;
    X_turn.loadFromFile("1turn.png");
    sf::Texture O_turn;
    O_turn.loadFromFile("0turn.png");
    sf::Texture X_won;
    X_won.loadFromFile("1won.png");
    sf::Texture O_won;
    O_won.loadFromFile("0won.png");
    sf::Texture draw;
    draw.loadFromFile("draw.png");
    sf::Texture yes;
    yes.loadFromFile("yes.png");
    sf::Texture no;
    no.loadFromFile("no.png");
    sf::Texture O_texture;
    O_texture.loadFromFile("0.png");
    sf::Texture X_texture;
    X_texture.loadFromFile("1.png");
    int player = 1;
    sf::RenderWindow window(sf::VideoMode(900, 900), "Kolko & Krzyzyk", sf::Style::Close);
    sf::Vector2f btnSize;
    btnSize.x = 180;
    btnSize.y = 180;

    sf::Vector2f hellosize;
    hellosize.x = 720;
    hellosize.y = 150;

    sf::Vector2f ynsize;
    ynsize.x = 200;
    ynsize.y = 120;

    sf::RectangleShape text(hellosize);
    text.setPosition(90, 40);

    
    Button y(ynsize);
    Button n(ynsize);

    y.element.setPosition(180, 750);
    n.element.setPosition(540, 750);

    y.element.setTexture(&yes);
    n.element.setTexture(&no);
    
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
            bool foundButton = false;
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed){
                if (result != -2) {
                    if(y.is_mouse_on_element(window)){ 
                        result = -2;
                        board.reset();
                        for (i = 0; i < 3; i++)
                            for (j = 0; j < 3; j++) {
                                array[i][j]->flag = false;
                                array[i][j]->element.setTexture(NULL);
                            }

                    }
                    continue;        
                }

                for (i = 0; i < 3; i++) {
                    for (j = 0; j < 3; j++) {
                        if (array[i][j]->is_mouse_on_element(window)) {
                            if (array[i][j]->flag == false) {
                                board.setElement(player, i, j);
                                array[i][j]->flag = true;

                                if (player == 1)
                                    array[i][j]->element.setTexture(&X_texture);
                                else
                                    array[i][j]->element.setTexture(&O_texture);
                                result = board.result();
                                if (result != -2) {
                                    for (i = 0; i < 3; i++)
                                        for (j = 0; j < 3; j++) {
                                            array[i][j]->flag = true;
                                        }
                                }
                                player = (player == 1) ? 0 : 1;
                            }
                            foundButton = true;
                            break;
                        }
                        if (foundButton)
                            break;
                    }
                }
            }


        }


        
        window.clear(sf::Color(248, 189, 255));
        
        for (i = 0; i < 3; i++)
            for (j = 0; j < 3; j++)
                window.draw(array[i][j]->element);

        if (result != -2) {
            window.draw(y.element);
            window.draw(n.element);

            if (result == 1)
                text.setTexture(&X_won);
            else if (result == 0)
                text.setTexture(&O_won);
            else if (result == -1)
                text.setTexture(&draw);
        }
        else if (player == 1)
            text.setTexture(&X_turn);
        else
            text.setTexture(&O_turn);

        window.draw(text);
        window.display();
    }

    return 0;
}