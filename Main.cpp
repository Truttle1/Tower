//============================================================================
// Name        : TestProject.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "Board.h"

using namespace std;
using namespace sf;

Board board;
DumbAI ai(&board);

void render(RenderWindow& window)
{
    board.render(window);
}

void tick(RenderWindow& window)
{
    Event event;
    bool didEvent = false;
    while (window.pollEvent(event))
    {
        if (event.type == Event::Closed or Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        if(Keyboard::isKeyPressed(Keyboard::R))
        {
        	board = Board();
        }
        board.tick(event, window);

        if(board.getTurn() == 1 and !board.tilesFall())
        {
        	ai.doTurn();
        }
        didEvent = true;
    }

    if(!didEvent)
    {
    	Event e;
    	board.tick(e, window);
    }
}


int main()
{
    RenderWindow window(VideoMode(1280, 720), "Tower");
    window.setFramerateLimit(12);
    board = Board();
    ai = DumbAI(&board);

    while (window.isOpen())
    {
    	tick(window);
        window.clear();
        render(window);
        window.display();
    }

    return 0;
}
