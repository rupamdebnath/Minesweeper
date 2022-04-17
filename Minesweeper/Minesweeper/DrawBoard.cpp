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
	currentGrid[x][y] = grid[x][y];	
	if (currentGrid[x][y] == 0)
	{
		if (x+1 < 12 && y+1 < 12 && x-1 >= 0 && y-1 >= 0)
		{
			currentGrid[x + 1][y] = grid[x + 1][y];
			currentGrid[x][y + 1] = grid[x][y + 1];
			currentGrid[x - 1][y] = grid[x - 1][y];
			currentGrid[x - 1][y - 1] = grid[x - 1][y - 1];
			currentGrid[x - 1][y + 1] = grid[x - 1][y + 1];
			currentGrid[x][y - 1] = grid[x][y - 1];
			currentGrid[x + 1][y - 1] = grid[x + 1][y - 1];

			currentGrid[x + 1][y + 1] = grid[x + 1][y + 1];

			currentGrid[x - 1][y - 1] = grid[x - 1][y - 1];
		}
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
				revealCell(i,j);
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
			ran = r.random(0, 5);
			if (ran == 5)
			{
				if (i != x && j != y)
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
			if (i + 1 < 12)
			{
				if (grid[i + 1][j] == 9) n++;
			}
			if (j + 1 < 12)
			{
				if (grid[i][j + 1] == 9) n++;
			}
			if (i - 1 >= 0)
			{
				if (grid[i - 1][j] == 9) n++;
				if (j + 1 < 12)
				{
					if (grid[i - 1][j + 1] == 9) n++;
				}
			}
			if (j - 1 >= 0)
			{
				if (grid[i][j - 1] == 9) n++;
				if (i + 1 < 12)
				{
					if (grid[i + 1][j - 1] == 9) n++;
				}
			}
			if (i + 1 < 12 && j + 1 < 12)
			{
				if (grid[i + 1][j + 1] == 9) n++;
			}
			if (i - 1 >= 0 && j - 1 >= 0)
			{
				if (grid[i - 1][j - 1] == 9) n++;
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

void DrawBoard::SetFlag(int x, int y)
{
	if (currentGrid[x][y] == 11 && currentGrid[x][y] != 10)
	{
		currentGrid[x][y] = 10;
		numberoFBombs++;
	}
	else if (currentGrid[x][y] != 11 && currentGrid[x][y] == 10)
	{
		currentGrid[x][y] = 11;
		numberoFBombs--;
	}
}
 
bool DrawBoard::WinCheck()
{
	int n=0;
	for (int i = 0; i < getRows(); i++)
	{
		for (int j = 0; j < getColumns(); j++)
		{
			if (currentGrid[i][j] != 10)
			{
				n++;
			}
		}
	}

	if (numberoFBombs == 0 && n == (getRows() + getColumns()))
	{
		cout << "Congratulations you have won!" << endl;
		return true;
	}
	return false;
}
