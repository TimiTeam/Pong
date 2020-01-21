#ifndef __PONG_HPP
# define __PONG_HPP

# include <iostream>
# include "AbstractPlayer.hpp"
# include "IGraphicWorker.hpp"
# include "Ball.hpp"
# define FRAME_VALUES 10

class Pong
{
private:
	IGraphicWorker &gw;
	int winSizeX;
	int winSizeY;
	AbstractPlayer &leftPlayer;
	AbstractPlayer &rightPlayer;
	Ball &ball;

public:
	Pong(int winSizeX, int winSizeY, IGraphicWorker &gw, AbstractPlayer &left, AbstractPlayer &right, Ball &ball);
	Pong(const Pong& src);
	~Pong();
	void runGame();
	Pong& operator=(const Pong& src);
};
#endif
