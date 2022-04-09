#pragma once
#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include "DrawBoard.h"

using namespace sf;
using namespace std;

int main()
{
    //Seed for Random generator for marking bombs
    srand(time(0));

    RenderWindow window(VideoMode(390, 500), "Minesweeper!");
    DrawBoard *board = new DrawBoard(window);

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
            cout << X << endl;
            cout << Y << endl;
        }

        window.clear(Color::White);

        board->createBoard();
        
        board->revealCell(X, Y);
        window.display();
    }
    delete board;
    return 0;
}