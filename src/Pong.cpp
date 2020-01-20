#include "Pong.hpp"

Pong::Pong(int winSizeX, int winSizeY, IGraphicWorker &gw, AbstractPlayer &left, AbstractPlayer &right) : winSizeX(winSizeX), winSizeY(winSizeY), gw(gw), leftPlayer(left), rightPlayer(right)
{

}
/*
Pong::Pong(const Pong& src)
{
	*this = src;
}
*/
Pong::~Pong()
{
	
}

Pong& Pong::operator=(const Pong& src)
{
	if (this != &src){
		this->winSizeX = src.winSizeX;
		this->winSizeY = src.winSizeY;
		this->gw = src.gw;
		this->leftPlayer = src.leftPlayer;
		this->rightPlayer = src.rightPlayer;
	}
	return *this;
}
 
void Pong::runGame(){
	bool isRun = true;

	if (gw.initGame() == false)
		std::cout << "Can't create game. Exit.\n";
	else{
		while (isRun)
		{
			gw.clearScreen();
			ball.moveBall();
			leftPlayer.changePos(gw.getPlayerInput());
			gw.drawPlayer(leftPlayer);
			gw.drawPlayer(rightPlayer);
			isRun = gw.isRunGame();
			gw.updateScreen();
		}
	}
	gw.closeGame();
}