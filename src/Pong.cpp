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
	int width = winSizeX / 40;
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


void Pong::drawMenu(AbstractPlayer **playerOne, AbstractPlayer **playerTwo, Ball &ball){
		gw.printMenu();
		*playerOne = PlayerFactory::getInstance().createPlayer(ALIVE, "Player 1", ball);
		std::string text;

		if (gw.isMultiplayerGame()){
			*playerTwo = PlayerFactory::getInstance().createPlayer(ALIVE, "Player 2", ball);
			gw.setPlayerOnKeyboard(**playerOne);
			gw.setPlayerOnArrows(**playerTwo);
			text = "Player left -> wsda. Player right -> arrows";
		}
		else{
			*playerTwo = PlayerFactory::getInstance().createPlayer(BOT, "Bot", ball);
			text = "Player left -> arrows. Player right -> bot";
			gw.setPlayerOnArrows(**playerOne);
			gw.setPlayerOnKeyboard(**playerTwo);
			(*playerTwo)->setSpeed(10.f);
		}
		int textHeight = winSizeY / 8;
		gw.clearScreen();
		gw.printBalckText(text, 50, winSizeY / 2 - textHeight, textHeight, winSizeX - 100);
		gw.updateScreen();
		gw.delay(2);
}

void Pong::runGame(){
	bool isRun = false;
	int sum = 0;
	if (gw.initGame("Pong", winSizeX, winSizeY) == false)
		std::cout << "Can't create game. Exit.\n";
	else{
		Ball &ball = Ball::getInstance();
		AbstractPlayer *playerOne = NULL;
		AbstractPlayer *playerTwo = NULL;
		drawMenu(&playerOne, &playerTwo, ball);
		setUpPlayer(*playerOne, *playerTwo, ball);
		int scoreWidth = winSizeX / 10;
		isRun = gw.isRunGame();
		while (isRun && sum != 20)
		{
			sum = playerOne->getScore() + playerTwo->getScore();
			gw.clearScreen();
			gw.printBalckText(std::to_string(playerOne->getScore()) + " / "+(std::to_string(playerTwo->getScore())), winSizeX / 2 - scoreWidth / 2, 5, winSizeY / 10, scoreWidth);
			ball.moveBall(5, winSizeY - 5, 5, winSizeX - 5, *playerOne, *playerTwo);
			gw.drawPlayer(*playerOne);
			gw.drawPlayer(*playerTwo);
			gw.updatePlayers();
			gw.drawBall(ball);
			gw.updateScreen();
			isRun = gw.isRunGame();
		}
		if (sum == 20){
			std::string message = playerOne->getScore() > playerTwo->getScore() ? playerOne->getName() : playerTwo->getName();
			message += " Win!!";
			int messWidth = winSizeX / 2;
			int messHeight = winSizeY / 5;
			gw.clearScreen();
			gw.printBalckText(message, messWidth / 4, winSizeY / 2 - messHeight / 2, messHeight, messWidth);
			gw.updateScreen();
			gw.delay(3);
		}
	}
	gw.closeGame();
}