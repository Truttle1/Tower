/*
 * DumbAI.cpp
 *
 *  Created on: Jul 23, 2020
 *      Author: truttle1
 */

#include "DumbAI.h"

DumbAI::DumbAI(Board* iboard)
{
	board = iboard;
	points = 2;
}

DumbAI::~DumbAI()
{
}

void DumbAI::setBoard(Board* iboard)
{
	board = iboard;
}

void DumbAI::doTurn()
{
	points = 2;
	while(points > 0)
	{
		for(unsigned x = 0; x < board->getWidth(); x++)
		{
			if(board->getTile(x, 0) == -1 and points > 0)
			{
				board->setTile(x,0,1);
				points--;
				break;
			}
		}
	}
	board->setTurn(0);
}
