# include "Pong.hpp"
# include "SDL_GraphicWorkerImpl.hpp"

int 	main(void){
	
	IGraphicWorker &gw = SDL_GraphicWorkerImpl::getInstance();

	Pong p(1480, 1024, gw);
	p.runGame();

	system("leaks -q Pong");
	return (0);
}
