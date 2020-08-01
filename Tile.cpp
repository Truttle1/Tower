/*
 * Tile.cpp
 *
 *  Created on: Jul 22, 2020
 *      Author: truttle1
 */

#include "Tile.h"

Tile::Tile(const int ix, const int iy, const int cx, const int cy)
{
	x = ix;
	y = iy;

	cellX = cx;
	cellY = cy;

}

Tile::~Tile() {
	// TODO Auto-generated destructor stub
}

void Tile::tick(Event& event, RenderWindow& window)
{
	cout << board->getClicks() << endl;
	if(event.type == Event::MouseButtonPressed && Mouse::isButtonPressed(Mouse::Left) && col == NONE)
	{
		if(Mouse::getPosition(window).x > x and Mouse::getPosition(window).y > y and Mouse::getPosition(window).x < x+92 and Mouse::getPosition(window).y < y+92)
		{
			board->setClicks(board->getClicks()-1);
			if(board->getTurn() == 0)
			{
				col = RED;
				if(board->getClicks() == 0)
				{
					board->setTurn(1);
				}
			}
			else
			{
				col = BLUE;
				if(board->getClicks() == 0)
				{
					board->setTurn(0);
				}
			}
			return;
		}
	}
	if(event.type == Event::MouseButtonPressed && Mouse::isButtonPressed(Mouse::Right))
	{
		if(Mouse::getPosition(window).x > x and Mouse::getPosition(window).y > y and Mouse::getPosition(window).x < x+92 and Mouse::getPosition(window).y < y+92)
		{

			if(board->getClicks() >= 2 and col != NONE)
			{
				col = NONE;
				if(board->getTurn() == 0)
				{
					board->setTurn(1);
				}
				else
				{
					board->setTurn(0);
				}
			}
		}
	}

}

bool Tile::colorIsWinner(int ix, int iy, CellType findColor, int lastDir, int loops)
{
	if(ix < 0 or ix > 7 or iy > 5)
	{
		return false;
	}
	if(loops > 28)
	{
		return false;
	}
	if(board->getTileAt(ix, iy)->getOwner() != findColor)
	{
		return false;
	}
	else if(iy == 0 and board->getTileAt(ix, iy)->getOwner() == findColor)
	{
		//cout << "DIDIT!!!" << endl;
		return true;
	}

	//cout << "AAA" << endl;

	return (ix > 0 and lastDir != 1 and colorIsWinner(ix-1,iy,findColor, 0, loops+1))
			or (ix < 7 and lastDir != 0 and colorIsWinner(ix+1,iy,findColor, 1, loops+1))
			or (iy > 0 and lastDir != 3 and colorIsWinner(ix,iy-1,findColor, 2, loops+1))
			or (iy < 5 and lastDir != 2 and colorIsWinner(ix,iy+1,findColor, 3, loops+1));
}

int Tile::getScore(int ix, int iy, CellType findColor, int lastDir, int loops)
{
	if(ix < 0 or ix > 7 or iy > 5)
	{
		return 0;
	}
	if(loops > 28)
	{
		return 0;
	}
	if(board->getTileAt(ix, iy)->getOwner() != findColor)
	{
		return 0;
	}
	else if(iy == 0 and board->getTileAt(ix, iy)->getOwner() == findColor)
	{
		//cout << "DIDIT!!!" << endl;
		return pow(2,iy);
	}
	else
	{
		int score = 0;
		if(ix > 0 and lastDir != 1)
		{
			score += getScore(ix-1,iy,findColor, 0, loops+1);
		}
		if(ix < 7 and lastDir != 0)
		{
			score += getScore(ix+1,iy,findColor, 1, loops+1);
		}
		if(iy > 0 and lastDir != 3)
		{
			score += getScore(ix,iy-1,findColor, 2, loops+1);
		}
		if(iy > 0 and lastDir != 2)
		{
			score += getScore(ix,iy+1,findColor, 3, loops+1);
		}
		return score;
	}

	//cout << "AAA" << endl;

}

bool Tile::fall()
{
	if(cellY >= 5)
	{
		return false;
	}

	if(getOwner() == NONE)
	{
		return false;
	}

	if(board->getTileAt(cellX, cellY+1)->getOwner() == NONE)
	{
		board->getTileAt(cellX, cellY+1)->setOwner(this->getOwner());
		setOwner(NONE);
		return true;
	}
	return false;
}

void Tile::ping()
{
	cout << "PING! " << cellX << " " << cellY << endl;
}

CellType Tile::getOwner()
{
	return col;
}

void Tile::setOwner(CellType newOwner)
{
	col = newOwner;
}

void Tile::render(RenderWindow& window)
{
	RectangleShape tileDrawing(Vector2f(92,92)); // @suppress("Abstract class cannot be instantiated")
	tileDrawing.setPosition(Vector2f(x,y));
	switch(col)
	{
	case RED:
		tileDrawing.setFillColor(Color::Red);
		break;
	case BLUE:
		tileDrawing.setFillColor(Color::Blue);
		break;
	case NONE:
		tileDrawing.setFillColor(Color::Black);
		break;
	}
	window.draw(tileDrawing);
}

void Tile::setBoard(Board& inputBoard)
{
	board = &inputBoard;
}

int Tile::getX(void)
{
	return x;
}

int Tile::getY(void)
{
	return y;
}
