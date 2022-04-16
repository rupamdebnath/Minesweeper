#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

using namespace sf;
using namespace std;

class DrawBoard
{
	int grid[12][12];
	int currentGrid[12][12];
	Texture t;
	RenderWindow* Vwindow;
	int numberoFBombs;	
	
	public:
		DrawBoard(RenderWindow& Vwindow);

		void createBoard();
		int getRows();
		int getColumns();
		void revealCell(int x, int y);
		void revealAllBombCells();
		void placeBombs(int x, int y);
		void placenumbers();
		int getnumberOfBombs();

		bool isBombInCell(int x, int y);

		void SetFlag(int x, int y);

};

