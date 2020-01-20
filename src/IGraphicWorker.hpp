#ifndef __IGRAPHICWORKER_HPP
# define __IGRAPHICWORKER_HPP

# include <iostream>
# include "AbstractPlayer.hpp"
# include "Ball.hpp"

class IGraphicWorker
{
private:

public:
	virtual ~IGraphicWorker() {};
	virtual bool initGame() = 0;
	virtual bool isRunGame() = 0;
	virtual eDirection getPlayerInput() = 0;
	virtual void drawPlayer(AbstractPlayer &player) = 0;
	virtual void drawBall(Ball ball) = 0;
	virtual void updateScreen() = 0;
	virtual void clearScreen() = 0;
	virtual void closeGame() = 0;
};
#endif
