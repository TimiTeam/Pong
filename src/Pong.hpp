#ifndef __PONG_HPP
# define __PONG_HPP

# include <iostream>
# include "IGraphicWorker.hpp"


class Pong
{
private:
	int winSizeX;
	int winSizeY;
	IGraphicWorker &gw;
	void setUpPlayer(AbstractPlayer &left, AbstractPlayer &right, Ball &ball);
	void drawMenu(AbstractPlayer **palyerLeft, AbstractPlayer **playerRight);

public:
	Pong(int winSizeX, int winSizeY, IGraphicWorker &gw);
	Pong(const Pong& src);
	~Pong();
	void runGame();
	Pong& operator=(const Pong& src);
};
#endif
