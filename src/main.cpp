# include "Pong.hpp"
# include "SDL_GraphicWorkerImpl.hpp"

int 	main(void){
	
	IGraphicWorker &gw = SDL_GraphicWorkerImpl::getInstance();

	Pong p(1260, 700, gw);
	p.runGame();

//	system("leaks -q Pong");
	return (0);
}
