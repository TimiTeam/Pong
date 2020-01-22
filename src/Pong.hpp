#ifndef __PONG_HPP
# define __PONG_HPP

# include <iostream>
# include "IGraphicWorker.hpp"

# define FRAME_VALUES 10

class Pong
{
private:
	int winSizeX;
	int winSizeY;
	IGraphicWorker &gw;
	void setUpPlayer(AbstractPlayer &left, AbstractPlayer &right, Ball &ball);
	void drawMenu(AbstractPlayer **palyerLeft, AbstractPlayer **playerRight, Ball &ball);

public:
	Pong(int winSizeX, int winSizeY, IGraphicWorker &gw);
	Pong(const Pong& src);
	~Pong();
	void runGame();
	Pong& operator=(const Pong& src);
};
#endif
