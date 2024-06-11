#include <SFML/Graphics.hpp>
#include <iostream> //nowe
#include <fstream> //nowe
#include <ctime> //nowe
#include <iomanip>//nowe
#include "Button.h"
#include "Game.h"

void wczytaj_wynik(int wynik);

int main()
{
    sf::Font font;
    font.loadFromFile("ARLRDBD.ttf");

    //nowe: zmienne s³u¿¹ce do zapisywania wyników
    int wynikdraw = 0;
    int wynikkolko = 0;
    int wynikkrzyzyk = 0;

    bool koniec_gry = false;
    sf::Text napis_koncowy;
    napis_koncowy.setPosition(360, 360);
    napis_koncowy.setFont(font);
  
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
    sf::RenderWindow window(sf::VideoMode(900, 900), "Kolko & Krzyzyk!1!111!!", sf::Style::Close);
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
                    else if (n.is_mouse_on_element(window)) {
                        koniec_gry = true;
                        std::string wyniki = "Draw: ";
                        wyniki = wyniki + std::to_string(wynikdraw);
                        wyniki = wyniki + "\nKolko: ";
                        wyniki = wyniki + std::to_string(wynikkolko);
                        wyniki = wyniki + "\nKrzyzyk: ";
                        wyniki = wyniki + std::to_string(wynikkrzyzyk);
                        napis_koncowy.setString(wyniki);
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
                                    if (result == 1) {
                                        text.setTexture(&X_won);
                                        wynikkrzyzyk++;//nowe
                                    }
                                    else if (result == 0) {
                                        text.setTexture(&O_won);
                                        wynikkolko++;//nowe
                                    }
                                    else if (result == -1) {
                                        text.setTexture(&draw);
                                        wynikdraw++;//nowe
                                    }
                                    wczytaj_wynik(result);
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
        if (koniec_gry == false) {
            for (i = 0; i < 3; i++)
                for (j = 0; j < 3; j++)
                    window.draw(array[i][j]->element);

            if (result != -2) {
                window.draw(y.element);
                window.draw(n.element);
            }
            else if (player == 1)
                text.setTexture(&X_turn);
            else
                text.setTexture(&O_turn);

            window.draw(text);
        }
        else
            window.draw(napis_koncowy);
            
        window.display();
    }

    return 0;
}

void wczytaj_wynik(int wynik) {
    std::time_t t = std::time(nullptr);  // Pobierz aktualny czas
    std::tm local_time;
    localtime_s(&local_time, &t);
    std::ofstream MyFile("WYNIKI.txt", std::ios_base::app);
    if (wynik == -1)
        MyFile << "\nRemis: " << std::put_time(&local_time, "%Y-%m-%d %H:%M:%S");
    else if (wynik == 0)
        MyFile << "\nKolko wygralo: " << std::put_time(&local_time, "%Y-%m-%d %H:%M:%S");
    else if (wynik == 1)
        MyFile << "\nKrzyzyk wygral: " << std::put_time(&local_time, "%Y-%m-%d %H:%M:%S");
    MyFile.close();
}