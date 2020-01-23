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
	virtual void printBalckText(std::string text, int posX, int posY, int height, int width) = 0;
	virtual bool isRunGame() = 0;
	virtual void initFPS() = 0;
	virtual int getFPS() = 0;
	virtual void printMenu() = 0;
	virtual bool isMultiplayerGame() = 0;
	virtual void setPlayerOnArrows(AbstractPlayer &player) = 0;
	virtual void setPlayerOnKeyboard(AbstractPlayer &player) = 0;
	virtual void updatePlayers() = 0;
	virtual void drawPlayer(AbstractPlayer &player) = 0;
	virtual void drawBall(Ball &ball) = 0;
	virtual void updateScreen() = 0;
	virtual void clearScreen() = 0;
	virtual void closeGame() = 0;
	virtual void delay(int mSec) = 0;
	virtual void getUserInput() = 0;
};
#endif
