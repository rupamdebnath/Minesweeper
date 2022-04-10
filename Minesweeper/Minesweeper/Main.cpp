#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "DrawBoard.h"

using namespace sf;
using namespace std;

int main()
{
    RenderWindow window(VideoMode(390, 500), "Minesweeper!");
    DrawBoard *board = new DrawBoard(window);
    bool firstclick = true;
    while (window.isOpen())
    {
        int X=0, Y=0;

        Event e;

        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();
        }
        if (e.type == Event::MouseButtonPressed)
        {
            Vector2f mposition(e.mouseButton.x, e.mouseButton.y);
            X = mposition.x / 32;
            Y = mposition.y / 32;
            X++;
            Y++;
            if (firstclick)
            {
                board->placeBombs(X, Y);
                firstclick = false;
            }
        }

        window.clear(Color::White);
        board->createBoard();
        board->revealCell(X, Y);
        
        window.display();

        /*cout << "No of bombs randomly placed this round:" << board->getnumberoFBombs() << endl;*/
    }
    
    delete board;
    return 0;
}