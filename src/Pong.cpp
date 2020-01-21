#include "Pong.hpp"
# include "PlayerFactory.hpp"

Pong::Pong(int winSizeX, int winSizeY, IGraphicWorker &gw) : winSizeX(winSizeX), winSizeY(winSizeY), gw(gw)
{

}

Pong::Pong(const Pong& src) : gw(src.gw)
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
	}
	return *this;
}

void Pong::setUpPlayer(AbstractPlayer &left, AbstractPlayer &right, Ball &ball){
	int height = winSizeY / 10;
	int width = winSizeX / 30;
	int posY = winSizeY / 2 - height;
	
	left.setPosX(0 + width * 2);
	left.setPosY(posY);
	left.setHeight(height);
	left.setWidth(width);

	right.setPosX(winSizeX - width * 2 - width);
	right.setPosY(posY);
	right.setHeight(height);
	right.setWidth(width);

	ball.setPosition(winSizeX / 2 - height / 2, winSizeY / 2 - height / 2);
	ball.setHeight(height / 2);
	ball.setWidth(height / 2);
}

void Pong::runGame(){
	bool isRun = false;
	bool isMultiplayer = false;
	AbstractPlayer *playerOne;
	AbstractPlayer *playerTwo;

	if ((isRun = gw.initGame("Pong", winSizeX, winSizeY)) == false)
		std::cout << "Can't create game. Exit.\n";
	else{
		Ball &ball = Ball::getInstance();
		gw.printMenu();
		isMultiplayer = gw.isMultiplayerGame();
		playerOne = PlayerFactory::getInstance().createPlayer(ALIVE, "Player 1", ball);
		if (isMultiplayer){
			playerTwo = PlayerFactory::getInstance().createPlayer(ALIVE, "Player 2", ball);
			gw.setPlayerOnKeyboard(*playerOne);
			gw.setPlayerOnArrows(*playerTwo);
		}
		else{
			playerTwo = PlayerFactory::getInstance().createPlayer(BOT, "Bot", ball);
			gw.setPlayerOnArrows(*playerOne);
			gw.setPlayerOnKeyboard(*playerTwo);
		}
		setUpPlayer(*playerOne, *playerTwo, ball);
		while (isRun)
		{
			gw.clearScreen();
			if (ball.moveBall(5, winSizeY - 5, *playerOne, *playerTwo) != NULL)
			{
				//ball.setPosition(winSizeX / 2, winSizeY / 2);
			}
			gw.drawPlayer(*playerOne);
			gw.drawPlayer(*playerTwo);
			gw.updatePlayers();
			gw.drawBall(ball);
			gw.updateScreen();
			isRun = gw.isRunGame();
		}
	}
	// delete [] playerOne;
	// delete [] playerTwo;
	gw.closeGame();
}