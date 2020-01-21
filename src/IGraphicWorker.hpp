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
	virtual bool initGame(const std::string title, int sizeX, int sizeY) = 0;
	virtual bool isRunGame() = 0;
	virtual void setKeyListnerOne(AbstractPlayer &player) = 0;
	virtual void setKeyListnerTwo(AbstractPlayer &player) = 0;
	virtual void getPlayerInput() = 0;
	virtual void drawPlayer(AbstractPlayer &player) = 0;
	virtual void drawBall(Ball &ball) = 0;
	virtual void updateScreen() = 0;
	virtual void clearScreen() = 0;
	virtual void closeGame() = 0;
};
#endif
