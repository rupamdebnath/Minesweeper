#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class DrawBoard
{

	int grid[12][12];	

	public:
		void createBoard(RenderWindow &Vwindow);


};

