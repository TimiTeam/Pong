# include "Pong.hpp"
# include "SDL_GraphicWorkerImpl.hpp"
# include "UserPlayerImpl.hpp"
# include "BotPlayerImpl.hpp"

int 	main(void){
	
	Ball &ball = Ball::getInstance();
	AbstractPlayer *ab = new UserPlayerImpl("player1");
	AbstractPlayer *bot = new BotPlayerImpl("bot", ball);
	IGraphicWorker &gw = SDL_GraphicWorkerImpl::getInstance();

	Pong p(1024, 720, gw, *ab, *bot, ball);
	p.runGame();

	system("leaks -q Pong");
	return (0);
}
