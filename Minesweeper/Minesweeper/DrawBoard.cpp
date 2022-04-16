#include "DrawBoard.h"
#include <array>
#include "Random.h"

DrawBoard::DrawBoard(RenderWindow &Vwindow)
{
	this->Vwindow = &Vwindow;
	t.loadFromFile("images/tiles.jpg");
	Sprite img(t);
	for (int i = 0; i < getRows(); i++)
	{
		for (int j = 0; j < getColumns(); j++)
		{
			currentGrid[i][j] = 10;			
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
			//getting the specific texture from the sprite size 384*32 pixels		
			img.setTextureRect(IntRect(32 * currentGrid[i][j], 0, 32, 32));

			img.setPosition(i * 32, j * 32);
			Vwindow->draw(img);
			
		}
	}	
	//Vwindow->draw(bombText);
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
	currentGrid[x][y] = grid[y][x];
	//cout << currentGrid[x][y] << endl;
	if (currentGrid[x][y] == 0)
	{
		currentGrid[x + 1][y] = grid[y+1][x];
		currentGrid[x][y + 1] = grid[y][x+1];

		currentGrid[x - 1][y] = grid[y - 1][x];
		currentGrid[x - 1][y + 1] = grid[y - 1][x + 1];

		currentGrid[x][y - 1] = grid[y][x - 1];
		currentGrid[x + 1][y - 1] = grid[y + 1][x - 1];

		currentGrid[x + 1][y + 1] = grid[y + 1][x + 1];

		currentGrid[x - 1][y - 1] = grid[y - 1][x - 1];		
	}
}

void DrawBoard::revealAllBombCells()
{
	for (int i = 0; i < getRows(); i++)
	{
		for (int j = 0; j < getColumns(); j++)
		{
			if (grid[i][j] == 9)
			{
				revealCell(j,i);
			}
		}
	}
}
 
void DrawBoard::placeBombs(int x, int y)
{	
	Random r; 
	int count = 0;
	int ran = 0;
	for (int i = 0; i < getRows(); i++)
	{
		for (int j = 0; j < getColumns(); j++)
		{
			ran = r.random(0, 3);
			if (ran == 3)
			{
				if (i != y && j != x)
				{					
					grid[i][j] = 9;
				}
			}
			else grid[i][j] = 0;
		}
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
void DrawBoard::placenumbers()
{
	int n;
	for (int i = 0; i < getRows(); i++)
	{
		for (int j = 0; j < getColumns(); j++)
		{
			n = 0;
			if (grid[i][j] == 9) continue;
			if (grid[i + 1][j] == 9) n++;
			if (grid[i][j + 1] == 9) n++;
			if (i - 1 >= 0)
			{			
				if (grid[i - 1][j] == 9)
					n++;
				if (grid[i - 1][j + 1] == 9) 
					n++;
			}
			if (j - 1 >= 0)
			{
				if (grid[i][j - 1] == 9)
					n++;
				if (grid[i + 1][j - 1] == 9) 
					n++;
			}
			if (grid[i + 1][j + 1] == 9) n++;
			if (i - 1 >= 0 && j - 1 >= 0)
			{
				if (grid[i - 1][j - 1] == 9)
					n++;
			}
			grid[i][j] = n;
		}
	}
}

int DrawBoard::getnumberOfBombs()
{
	return numberoFBombs;
}

bool DrawBoard::isBombInCell(int x, int y)
{
	return (currentGrid[x][y] == 9);
}

