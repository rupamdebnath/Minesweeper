#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

using namespace sf;
using namespace std;

class DrawBoard
{
	int grid[12][12];
	Texture t;
	RenderWindow* Vwindow;
	
	public:
		DrawBoard(RenderWindow& Vwindow);

		void createBoard();
		int getRows();
		int getColumns();
		void revealCell(int x, int y);
};

