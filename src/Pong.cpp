#include "Pong.hpp"

Pong::Pong(int winSizeX, int winSizeY, IGraphicWorker &gw, AbstractPlayer &left, AbstractPlayer &right, Ball &ball) : winSizeX(winSizeX), winSizeY(winSizeY), gw(gw), leftPlayer(left), rightPlayer(right), ball(ball)
{

}

Pong::Pong(const Pong& src) : gw(src.gw), leftPlayer(src.leftPlayer), rightPlayer(src.rightPlayer), ball(src.ball)
{
	*this = src;
}

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
		this->ball = src.ball;
	}
	return *this;
}
 
void Pong::runGame(){
	bool isRun = false;

	if ((isRun = gw.initGame("Pong", winSizeX, winSizeY)) == false)
		std::cout << "Can't create game. Exit.\n";
	else{
		int height = winSizeY / 8;
		int width = winSizeX / 10;
		float posY =  winSizeY / 2;
		leftPlayer.setPosX(static_cast<float>(winSizeX / 8));
		leftPlayer.setPosY(posY);
		leftPlayer.setHeight(height);
		leftPlayer.setWidth(width);
		rightPlayer.setPosX(static_cast<float>(winSizeX - leftPlayer.getPosX()));
		rightPlayer.setPosY(posY);
		rightPlayer.setHeight(height);
		rightPlayer.setWidth(width);
		gw.setKeyListner(leftPlayer);
		while (isRun)
		{
			gw.clearScreen();
			//ball.moveBall();
			gw.getPlayerInput();
			gw.drawPlayer(leftPlayer);
			gw.drawPlayer(rightPlayer);
			gw.updateScreen();
			isRun = gw.isRunGame();
		}
	}
	gw.closeGame();
}