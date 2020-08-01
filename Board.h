/*
 * Board.h
 *
 *  Created on: Jul 22, 2020
 *      Author: truttle1
 */

#ifndef BOARD_H_
#define BOARD_H_

#include "Tile.h"
#include "DumbAI.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <math.h>

using namespace std;
using namespace sf;
class Tile;
class DumbAI;
class Board {
public:
	Board();
	virtual ~Board();
	void tick(Event& event, RenderWindow& window);
	void render(RenderWindow& window);
	void test(int x, int y);
	void setTurn(int iTurn);
	void setClicks(int iclicks);
	int getTurn();
	int getClicks();
	Tile* getTileAt(int x, int y);
	int getWinner();
	int getWidth();
	int getHeight();
	void setTile(int x, int y, int icell);
	int getTile(int x, int y);
	bool tilesFall();

private:
	vector<vector<Tile*>> tiles;
	int turn;
	int clicks;
	bool isFull();
};

#endif
