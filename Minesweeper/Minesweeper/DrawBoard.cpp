#include "DrawBoard.h"
#include <array>
#include "Random.h"

DrawBoard::DrawBoard(RenderWindow &Vwindow)
{
	this->Vwindow = &Vwindow;
	for (int i = 0; i < getRows(); i++)
	{
		for (int j = 0; j < getColumns(); j++)
		{
			grid[i][j] = 10;
		}
	}
}


void DrawBoard::createBoard()
{
	t.loadFromFile("images/tiles.jpg");
	Sprite img(t);
	
	for (int i = 0; i < getRows(); i++)
	{
		for (int j = 0; j < getColumns(); j++)
		{
			//getting the specific texture from the sprite size 32*384 pixels		
			img.setTextureRect(IntRect(32 * grid[i][j], 0, 32, 32));

			img.setPosition(i * 32, j * 32);
			Vwindow->draw(img);
		}
	}
	
}

int DrawBoard::getRows()
{
	int rows = sizeof grid / sizeof grid[0];
	return rows;
}

int DrawBoard::getColumns()
{
	int cols = sizeof grid[0] / sizeof(int);
	return cols;
}

void DrawBoard::revealCell(int x, int y)
{
	Texture rt;
	rt.loadFromFile("images/tiles.jpg");
	Sprite reveal(rt);

	reveal.setTextureRect(IntRect(0, 0, 32, 32));

	reveal.setPosition((x-1) * 32, (y-1) * 32);

	Vwindow->draw(reveal);
}
 
void DrawBoard::placeBombs(int x, int y)
{
	Random r; 
	int count = 0;
	int nBombs = r.random(20, 30);
	
	for (int i = 0; i < getRows(); i++)
	{
		for (int j = 0; j < getColumns(); j++)
		{
			if ((x - 1) == i && (y - 1) == j)
			{
				continue;
			}
			else
			{
				grid[i][j] = r.random(0, 5 ) == 1? 9 : 10;
				count++;
			}
		}
		if (count == nBombs)
			break;
	}
	int noofbombs = 0;
	for (int i = 0; i < getRows(); i++)
	{
		for (int j = 0; j < getColumns(); j++)
		{
			if (grid[i][j] == 9)
			{
				noofbombs++;
			}
		}
	}

	numberoFBombs = noofbombs;
}

int DrawBoard::getnumberoFBombs()
{
	return numberoFBombs;
}
