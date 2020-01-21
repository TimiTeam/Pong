#include "SDL_GraphicWorkerImpl.hpp"

SDL_GraphicWorkerImpl *SDL_GraphicWorkerImpl::selfGW = 0;

SDL_GraphicWorkerImpl::SDL_GraphicWorkerImpl()
{
	this->listner = NULL;
	this->framework = new SDL_Framework();
	playerTexture = NULL;
	ballTexture = NULL;
	screen = NULL;
}

SDL_GraphicWorkerImpl::SDL_GraphicWorkerImpl(const SDL_GraphicWorkerImpl& src)
{
	*this = src;
}

SDL_GraphicWorkerImpl::~SDL_GraphicWorkerImpl()
{
	closeGame();
	delete [] framework;
}

SDL_GraphicWorkerImpl& SDL_GraphicWorkerImpl::operator=(const SDL_GraphicWorkerImpl& src)
{
	return *this;
}

bool SDL_GraphicWorkerImpl::isRunGame(){
	return isRun;
}

void SDL_GraphicWorkerImpl::getPlayerInput(){
	SDL_Event	e;
	eDirection result = NON;

	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))
			isRun = false;
		else if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP)
		{
			if (e.key.keysym.sym == SDLK_UP){
				result = UP;
				break ;
			}
			else if (e.key.keysym.sym == SDLK_DOWN){
				result = DOWN;
				break;
			}
		}
	}
	if (listner != NULL)
		listner->updateState(result);
}


void SDL_GraphicWorkerImpl::setKeyListner(AbstractPlayer &player){
	this->listner = &player;
}

bool SDL_GraphicWorkerImpl::initGame(const std::string title, int sizeX, int sizeY){
	isRun = false;
	
	if (framework != NULL && framework->initSDL(title,  sizeX,  sizeY)){
		screen = framework->getMainTexture();
		isRun = true;
		if (playerTexture == NULL)
			playerTexture = framework->loadTexture("Racket.jpeg");
	}
	return isRun;
}

void SDL_GraphicWorkerImpl::drawPlayer(AbstractPlayer &player){
	framework->setRenderTarget(screen);
	SDL_Rect rect = {player.getPosX(), player.getPosY(), player.getWidth(), player.getHeight()};
	framework->drawTexture(playerTexture, NULL, &rect);
	framework->setRenderTarget(NULL);
}

void SDL_GraphicWorkerImpl::drawBall(Ball ball){
	framework->setRenderTarget(screen);
	framework->drawTexture(ballTexture, NULL, NULL);
	framework->setRenderTarget(NULL);
}

void SDL_GraphicWorkerImpl::updateScreen(){
	framework->drawTexture(screen, NULL, NULL);
	framework->renderPresent(screen);
}

void SDL_GraphicWorkerImpl::clearScreen(){
	framework->setRenderTarget(screen);
	framework->clearScrean();
}

void SDL_GraphicWorkerImpl::closeGame(){
	if (screen != NULL){
		SDL_DestroyTexture(screen);
		screen = NULL;
	}
	if (ballTexture != NULL){
		SDL_DestroyTexture(ballTexture);
		ballTexture = NULL;
	}
	if (playerTexture != NULL){
		SDL_DestroyTexture(playerTexture);
		playerTexture = NULL;
	}
	framework->close();
}

SDL_GraphicWorkerImpl &SDL_GraphicWorkerImpl::getInstance(){
	if (selfGW == NULL)
		selfGW = new SDL_GraphicWorkerImpl();
	return *selfGW;
}