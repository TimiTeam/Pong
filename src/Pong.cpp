#include "Pong.hpp"
#include "PlayerFactory.hpp"
#include <chrono>

Pong::Pong(int winSizeX, int winSizeY, IGraphicWorker &gw) : winSizeX(winSizeX), winSizeY(winSizeY), gw(gw)
{
}

Pong::Pong(const Pong &src) : gw(src.gw)
{
	*this = src;
}

Pong::~Pong()
{
}

Pong &Pong::operator=(const Pong &src)
{
	if (this != &src)
	{
		this->winSizeX = src.winSizeX;
		this->winSizeY = src.winSizeY;
		this->gw = src.gw;
	}
	return *this;
}

void Pong::setUpPlayer(AbstractPlayer &left, AbstractPlayer &right, Ball &ball)
{
	int height = winSizeY / 10;
	int width = winSizeX / 40;
	int posY = winSizeY / 2 - height / 2;

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

void Pong::drawMenu(AbstractPlayer **playerOne, AbstractPlayer **playerTwo)
{
	gw.printMenu();
	*playerOne = PlayerFactory::getInstance().createPlayer(ALIVE, "Player 1");
	std::string text;

	if (gw.isMultiplayerGame())
	{
		*playerTwo = PlayerFactory::getInstance().createPlayer(ALIVE, "Player 2");
		gw.setPlayerOnKeyboard(**playerOne);
		gw.setPlayerOnArrows(**playerTwo);
		text = "Player left -> wsda. Player right -> arrows";
	}
	else
	{
		*playerTwo = PlayerFactory::getInstance().createPlayer(BOT, "Bot");
		text = "Player left -> arrows. Player right -> bot";
		gw.setPlayerOnArrows(**playerOne);
		gw.setPlayerOnKeyboard(**playerTwo);
	}
	if (gw.isRunGame())
	{
		int textHeight = winSizeY / 8;
		gw.clearScreen();
		gw.printBalckText(text, 50, winSizeY / 2 - textHeight, textHeight, winSizeX - 100);
		gw.updateScreen();
		gw.delay(2000);
	}
}

void Pong::runGame()
{
	bool isRun = false;
	int sum = 0;
	if (gw.initGame("Pong", winSizeX, winSizeY) == false)
		std::cout << "Can't create game. Exit.\n";
	else
	{
		Ball &ball = Ball::getInstance();
		AbstractPlayer *playerOne = NULL;
		AbstractPlayer *playerTwo = NULL;
		drawMenu(&playerOne, &playerTwo);
		setUpPlayer(*playerOne, *playerTwo, ball);
		int scoreWidth = winSizeX / 10;
		int scoreHeight = scoreWidth / 2;
		isRun = gw.isRunGame();
		int fps;
		playerOne->setSpeed(50);
		playerTwo->setSpeed(50);
		ball.setSpeed(10);
		double lag = 0.0;
		const double mmPerSecond = 1.0 / 60.0;
		gw.initFPS();
		while (isRun && sum != 20)
		{
			auto start = std::chrono::system_clock::now();
			sum = playerOne->getScore() + playerTwo->getScore();
			gw.clearScreen();
			gw.printBalckText(std::to_string(playerOne->getScore()) + " / " + (std::to_string(playerTwo->getScore())), winSizeX / 2 - scoreWidth / 2, 5, scoreHeight, scoreWidth);

			auto end = std::chrono::system_clock::now();
			std::chrono::duration<double> elapsed_seconds = end - start;
			lag += elapsed_seconds.count();
			gw.getUserInput();
			gw.updatePlayers();
			while (lag >= mmPerSecond)
			{
				gw.updatePlayers();
				ball.moveBall(5, winSizeY - 5, 5, winSizeX - 5, *playerOne, *playerTwo);
				lag -= mmPerSecond;
			}
			fps = gw.getFPS();
			gw.printBalckText(std::to_string(fps), 5, 5, 100, 150);
			gw.drawPlayer(*playerOne);
			gw.drawPlayer(*playerTwo);
			gw.drawBall(ball);
			gw.updateScreen();
			isRun = gw.isRunGame();
		}
		if (sum == 20)
		{
			std::string message = playerOne->getScore() > playerTwo->getScore() ? playerOne->getName() : playerTwo->getName();
			message += " Win!!";
			int messWidth = winSizeX / 2;
			int messHeight = winSizeY / 5;
			gw.clearScreen();
			gw.printBalckText(message, winSizeX / 2 -  messWidth / 2, winSizeY / 2 - messHeight / 2, messHeight, messWidth);
			gw.updateScreen();
			gw.delay(3000);
		}
	}
	gw.closeGame();
}