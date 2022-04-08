#include "DrawBoard.h"
#include <array>

void DrawBoard::createBoard(RenderWindow &Vwindow)
{
	int rows = sizeof grid / sizeof grid[0]; 
	//cout << rows << endl; 12

	int cols = sizeof grid[0] / sizeof(int); 
	//cout << cols << endl; 12
	Texture t;
	t.loadFromFile("images/tiles.jpg");
	Sprite img(t);
	img.setTextureRect(IntRect(32 * 10, 0, 32, 32));
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			//getting the specific texture from the sprite size 32*384 pixels		
			img.setPosition(i * 32, j * 32);
			Vwindow.draw(img);
		}
	}
	
}
