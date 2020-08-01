/*
 * DumbAI.h
 *
 *  Created on: Jul 23, 2020
 *      Author: truttle1
 */

#ifndef DUMBAI_H_
#define DUMBAI_H_
#include "Board.h"
#include <stdlib.h>

using namespace std;
class Board;
class DumbAI {
public:
	DumbAI(Board* iboard);
	virtual ~DumbAI();
	void setBoard(Board* iboard);
	void doTurn();

private:
	int points;
	Board* board;
};

#endif /* DUMBAI_H_ */
