#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "DrawBoard.h"

using namespace sf;
using namespace std;

int main()
{
    Reset:
    Texture emoji;

    emoji.loadFromFile("images/inplay.png");    

    Font font;
    font.loadFromFile("Fonts/Myfont.ttf");
    Text text, bombText, bombvalue;
    text.setFont(font);
    text.setFillColor(sf::Color::Red);
    text.setScale(0.5,0.5);
    bombText.setFont(font);
    bombText.setFillColor(sf::Color::Black);
    bombText.setString("Click Once to place bombs\nNo of Bombs remaining:");
    bombText.setPosition(10, 400);
    bombText.setScale(0.5, 0.5);

    bombvalue.setFont(font);
    bombvalue.setFillColor(sf::Color::Black);    
    bombvalue.setPosition(200, 420);
    bombvalue.setScale(0.5, 0.5);
    RenderWindow window(VideoMode(390, 500), "Minesweeper!");
    DrawBoard *board = new DrawBoard(window);
    //window.setKeyRepeatEnabled(false);
    bool firstclick = true;    
    while (window.isOpen())
    {        
        int X=0, Y=0;

        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();
        
            if (e.type == Event::MouseButtonPressed)
            {
                Vector2f mposition(e.mouseButton.x, e.mouseButton.y);

                X = mposition.x / 32;
                Y = mposition.y / 32;
                if (e.key.code == Mouse::Left)
                {
                    if ( X < 12 && Y < 12 && firstclick)
                    {
                        firstclick = false;
                        board->placeBombs(X, Y);
                        board->placenumbers();
                        bombvalue.setString(to_string(board->getnumberOfBombs()));                        
                    }
                    else if (X < 12 && Y < 12)
                    {
                        cout << X << " " << Y << endl;
                        board->revealCell(X, Y);
                        //cout << e.mouseButton.x << " " << e.mouseButton.y << endl;
                        if (board->isBombInCell(X, Y))
                        {
                            emoji.loadFromFile("images/lose.png");
                            board->revealAllBombCells();
                            text.setString("Oops! Stepped on a bomb! You have lost!");
                            text.setPosition(20, 450);
                        }
                    }
                    
                }
                

                if (e.key.code == Mouse::Right)
                {
                    board->SetFlag(X, Y);
                    if (board->WinCheck())
                    {
                        emoji.loadFromFile("images/win.png");
                        text.setString("Congratulations! You have won!");
                        text.setFillColor(sf::Color::Blue);
                        text.setPosition(20, 450);
                    }
                }
                
            }   bombvalue.setString(to_string(board->getnumberOfBombs()));
        }       
        
        Sprite smiley(emoji);
        smiley.setPosition(250, 400);
        smiley.setScale(2, 2);
        window.clear(Color::White);
        board->createBoard();
        window.draw(bombText);
        window.draw(bombvalue);
        window.draw(smiley);
        window.draw(text);
        window.display();
        if (board->isBombInCell(X, Y) || board->WinCheck())
        {            
            system("pause");
            bool pause = true;
            while (window.pollEvent(e) && pause)
            {
                if (e.type == Event::Closed)
                    window.close();

                if (e.type == Event::MouseButtonPressed)
                {
                    Vector2f mposition(e.mouseButton.x, e.mouseButton.y);

                    X = mposition.x / 32;
                    Y = mposition.y / 32;
                    cout << "Print " << endl;
                }
            }
            //system("pause");
            delete board;
            goto Reset;
        }  
    }    
    
    return 0;
}