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
		int height = winSizeY / 6;
		int width = winSizeX / 25;
		float posY =  winSizeY / 2;
		leftPlayer.setPosX(width);
		leftPlayer.setPosY(posY);
		leftPlayer.setHeight(height);
		leftPlayer.setWidth(width);
		rightPlayer.setPosX(winSizeX - width * 2);
		rightPlayer.setPosY(posY);
		rightPlayer.setHeight(height);
		rightPlayer.setWidth(width);
		gw.setKeyListnerOne(leftPlayer);
		ball.setHeight(100);
		ball.setWidth(100);
		//gw.setKeyListnerTwo(rightPlayer);
		ball.setPosition(winSizeX / 2, winSizeY / 2);
		while (isRun)
		{
			gw.clearScreen();
			if (ball.moveBall(5, winSizeY - 5, leftPlayer, rightPlayer) != NULL)
			{
				ball.setPosition(winSizeX / 2, winSizeY / 2);
			}
			gw.getPlayerInput();
			gw.drawPlayer(leftPlayer);
			gw.drawPlayer(rightPlayer);
			gw.drawBall(ball);
			gw.updateScreen();
			isRun = gw.isRunGame();
		}
	}
	gw.closeGame();
}