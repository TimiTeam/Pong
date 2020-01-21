# include "Pong.hpp"
# include "SDL_GraphicWorkerImpl.hpp"
# include "UserPlayerImpl.hpp"
# include "BotPlayerImpl.hpp"

int 	main(void){
	
	Ball &ball = Ball::getInstance();
	AbstractPlayer *ab = new UserPlayerImpl("player1");
	AbstractPlayer *bot = new BotPlayerImpl("bot", ball);
	AbstractPlayer *ab1 = new UserPlayerImpl("player2");
	IGraphicWorker &gw = SDL_GraphicWorkerImpl::getInstance();

	Pong p(1024, 720, gw, *ab, *ab1, ball);
	p.runGame();

	system("leaks -q Pong");
	return (0);
}
