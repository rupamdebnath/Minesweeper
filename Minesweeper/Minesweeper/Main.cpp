#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "DrawBoard.h"

using namespace sf;
using namespace std;

int main()
{
    Reset:
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

            if (firstclick)
            {
                //cout << e.mouseButton.x << endl;
                //cout << e.mouseButton.y << endl;
                //cout << X << endl;
                //cout << Y << endl;
                board->placeBombs(X, Y);
                board->placenumbers();
                firstclick = false;
            }
            else
            {                
                board->revealCell(X, Y);
                if (board->isBombInCell(X, Y))
                    board->revealAllBombCells();
            }
        }

       window.clear(Color::White);
       board->createBoard();
       
        window.display();
        if (board->isBombInCell(X, Y))
        {
            board->revealAllBombCells();           
            system("pause");
            cout << "Busted, clicked on a bomb! You have lost!" << endl;
            window.clear();
            delete board;
            goto Reset;
        }
        //cout << "No of bombs randomly placed this round:" << board->getnumberOfBombs() << endl;
    }
    
    delete board;
    return 0;
}