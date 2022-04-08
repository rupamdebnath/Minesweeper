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
    DrawBoard *board = new DrawBoard();

    while (window.isOpen())
    {
        Vector2i pos = Mouse::getPosition(window);
        int x = pos.x / 32;
        int y = pos.y / 32;
        x++;
        y++;
        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();
            if (e.type == Event::MouseButtonPressed)
            {
                cout << x << endl;
                cout << y << endl;
            }
        }

        window.clear(Color::White);

        
        
        //window.draw(img);

        board->createBoard(window);

        window.display();
    }
    delete board;
    return 0;
}