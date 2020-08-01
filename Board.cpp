/*
 * Board.cpp
 *
 *  Created on: Jul 22, 2020
 *      Author: truttle1
 */

#include "Board.h"

const int boardWidth = 8;
const int boardHeight = 6;

Board::Board()
{
	for(unsigned int x = 0; x < boardWidth; x++)
	{
		tiles.push_back(vector<Tile*>());
		for(unsigned int y = 0; y < boardHeight; y++)
		{
			tiles[x].push_back(new Tile(x*100+72,y*100+72,x,y));
		}
	}
	turn = 0;
	clicks = 2;
}

Board::~Board()
{
}

bool Board::isFull()
{

	for(unsigned int x = 0; x < boardWidth; x++)
	{
		tiles.push_back(vector<Tile*>());
		for(unsigned int y = 0; y < boardHeight; y++)
		{
			if(tiles[x][y]->getOwner() == NONE)
			{
				return false;
			}
		}
	}
	return true;
}

void Board::test(int x, int y)
{
	cout << "located at " << x << "," << y << endl;
}
void Board::tick(Event& event, RenderWindow& window)
{
	for(unsigned int x = 0; x < boardWidth; x++)
	{
		for(unsigned int y = 0; y < boardHeight; y++)
		{
			tiles[x][y]->setBoard(*this);
			tiles[x][y]->tick(event, window);
		}
	}


	if(isFull() && clicks <= 1)
	{
		if(getTurn() == 0)
		{
			setTurn(1);
		}
		else
		{
			setTurn(0);
		}
	}
	tilesFall();

}

int Board::getWinner()
{
	for(unsigned int x = 0; x < boardWidth; x++)
	{
		if(tiles[x][5]->colorIsWinner(x, 5, RED, -1, 0))
		{
			return 0;
		}
		if(tiles[x][5]->colorIsWinner(x, 5, BLUE, -1, 0))
		{
			return 1;
		}
	}
	return -1;
}

void Board::render(RenderWindow& window)
{
	int winner = getWinner();

	Font textFont;
	if (!textFont.loadFromFile("arial.ttf")) // @suppress("Invalid arguments")
	{
	    cout << "bad things" << endl;
	}

	Text winMsg;
	winMsg.setFont(textFont);
	winMsg.setCharacterSize(64);
	winMsg.setFillColor(Color::White);
	winMsg.setStyle(Text::Bold);
	winMsg.setPosition(Vector2f(950,128));

	RectangleShape rect(Vector2f(1280.0f,720.0f));// @suppress("Abstract class cannot be instantiated")
	switch(winner)
	{
	case -1:
		winMsg.setString("");
		rect.setFillColor(Color::Cyan);
		break;
	case 0:
		winMsg.setString("Red Wins");
		rect.setFillColor(Color::Red);
		break;
	case 1:
		winMsg.setString("Blue Wins");
		rect.setFillColor(Color::Blue);
		break;
	}
	window.draw(rect);

	window.draw(winMsg);
	RectangleShape board(Vector2f(808,608)); // @suppress("Abstract class cannot be instantiated")
	board.setFillColor(Color::White);
	board.setPosition(Vector2f(64,64));
	window.draw(board);

	for(unsigned int x = 0; x < boardWidth; x++)
	{
		for(unsigned int y = 0; y < boardHeight; y++)
		{
			tiles[x][y]->render(window);
		}
	}

	if(winner == -1)
	{

		Text turnString;
		if(getTurn() == 0)
		{
			turnString.setString("Red's Turn");
		}
		else
		{
			turnString.setString("Blue's Turn");
		}
		turnString.setFont(textFont);
		turnString.setCharacterSize(64);
		turnString.setFillColor(Color::Black);
		turnString.setStyle(Text::Bold);
		turnString.setPosition(Vector2f(890,96));
		window.draw(turnString);

		turnString.setString("Left click a tile");
		turnString.setCharacterSize(48);
		turnString.setFillColor(Color::Black);
		turnString.setStyle(Text::Bold);
		turnString.setPosition(Vector2f(890,192));
		window.draw(turnString);

		turnString.setString("to place a tower.");
		turnString.setCharacterSize(48);
		turnString.setFillColor(Color::Black);
		turnString.setStyle(Text::Bold);
		turnString.setPosition(Vector2f(890,192+48));
		window.draw(turnString);

		turnString.setString("Right click a tile");
		turnString.setCharacterSize(48);
		turnString.setFillColor(Color::Black);
		turnString.setStyle(Text::Bold);
		turnString.setPosition(Vector2f(890,192+128));
		window.draw(turnString);

		turnString.setString("to destroy.");
		turnString.setCharacterSize(48);
		turnString.setFillColor(Color::Black);
		turnString.setStyle(Text::Bold);
		turnString.setPosition(Vector2f(890,192+128+48));
		window.draw(turnString);

		turnString.setString("Build - 1 Pt");
		turnString.setCharacterSize(32);
		turnString.setFillColor(Color::Black);
		turnString.setStyle(Text::Bold);
		turnString.setPosition(Vector2f(890,500));
		window.draw(turnString);

		turnString.setString("Destroy - 2 Pts");
		turnString.setCharacterSize(32);
		turnString.setFillColor(Color::Black);
		turnString.setStyle(Text::Bold);
		turnString.setPosition(Vector2f(890,530));
		window.draw(turnString);

		String str = ("Pts: " + to_string(getClicks())); // @suppress("Invalid arguments")
		turnString.setString(str);
		turnString.setCharacterSize(48);
		if(getTurn() == 0)
		{
			turnString.setFillColor(Color::Red);
		}
		else
		{
			turnString.setFillColor(Color::Blue);
		}
		turnString.setStyle(Text::Bold);
		turnString.setPosition(Vector2f(890,600));
		window.draw(turnString);

	}
}

Tile* Board::getTileAt(int x, int y)
{
	tiles[x][y]->setBoard(*this);
	//cout << "AAA " << tiles.size() << " " << tiles[x].size() << endl;
	return tiles[x][y];
}

void Board::setTurn(int iTurn)
{
	turn = iTurn;
	clicks = 2;
}

int Board::getTurn()
{
	return turn;
}

int Board::getClicks()
{
	return clicks;
}

void Board::setClicks(int iclicks)
{
	clicks = iclicks;
}

int Board::getHeight()
{
	return boardHeight;
}

int Board::getWidth()
{
	return boardWidth;
}

int Board::getTile(int x, int y)
{
	if(tiles[x][y]->getOwner() == RED)
	{
		return 0;
	}
	if(tiles[x][y]->getOwner() == BLUE)
	{
		return 1;
	}
	return -1;
}

void Board::setTile(int x, int y, int icell)
{
	if(icell == -1)
	{
		tiles[x][y]->setOwner(NONE);
	}
	else if(icell == 0)
	{
		tiles[x][y]->setOwner(RED);
	}
	else if(icell == 1)
	{
		tiles[x][y]->setOwner(BLUE);
	}
}

bool Board::tilesFall()
{
	bool ret = false;
	for(unsigned x = 0; x < boardWidth; x++)
	{
		for(unsigned y = 0; y < boardHeight; y++)
		{
			ret = ret or tiles[x][y]->fall();
		}
	}
	return ret;
}
