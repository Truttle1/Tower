/*
 * Tile.h
 *
 *  Created on: Jul 22, 2020
 *      Author: truttle1
 */

#ifndef TILE_H_
#define TILE_H_
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Board.h"


using namespace std;
using namespace sf;
class Board;
enum CellType {RED, BLUE, NONE};
class Tile
{
public:
	Tile(const int ix, const int iy, const int cx, const int cy);
	virtual ~Tile();
	void tick(Event& event, RenderWindow& window);
	void render(RenderWindow& window);
	void setBoard(Board& inputBoard);
	int getX();
	int getY();
	CellType getOwner();
	void setOwner(CellType newOwner);
	void ping();
	bool colorIsWinner(int ix, int iy, CellType findColor, int lastDir, int loops);
	int getScore(int ix, int iy, CellType findColor, int lastDir, int loops);
	bool fall();

private:
	Board* board;
	int x;
	int y;

	int cellX;
	int cellY;
	CellType col = NONE;

};

#endif /* TILE_H_ */
