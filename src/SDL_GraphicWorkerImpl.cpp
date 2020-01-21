#include "SDL_GraphicWorkerImpl.hpp"

SDL_GraphicWorkerImpl *SDL_GraphicWorkerImpl::selfGW = 0;

SDL_GraphicWorkerImpl::SDL_GraphicWorkerImpl()
{
	listnerOne = NULL;
	listnerTwo = NULL;
	framework = new SDL_Framework();
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
	eDirection resultOne = NON;
	eDirection resultTwo = NON;


	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))
			isRun = false;
		else if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP)
		{
			if (e.key.keysym.sym == SDLK_UP){
				resultOne = UP;
			}
			else if (e.key.keysym.sym == SDLK_DOWN){
				resultOne = DOWN;
			}
			if (e.key.keysym.sym == SDLK_w){
				resultTwo = UP;
			}
			else if (e.key.keysym.sym == SDLK_s){
				resultTwo = DOWN;
			}
		}
	}
	if (listnerOne != NULL){
		if (listnerTwo == NULL)
			listnerOne->updateState(resultOne);
		else
			listnerOne->updateState(resultTwo);
	}
	if (listnerTwo != NULL){
		listnerTwo->updateState(resultOne);
	}
}


void SDL_GraphicWorkerImpl::setKeyListnerOne(AbstractPlayer &player){
	this->listnerOne = &player;
}

void SDL_GraphicWorkerImpl::setKeyListnerTwo(AbstractPlayer &player){
	this->listnerTwo = &player;
}

bool SDL_GraphicWorkerImpl::initGame(const std::string title, int sizeX, int sizeY){
	isRun = false;
	
	if (framework != NULL && framework->initSDL(title,  sizeX,  sizeY)){
		screen = framework->getMainTexture();
		isRun = true;
		if (playerTexture == NULL)
			playerTexture = framework->loadTexture("Racket.jpeg");
		if (ballTexture == NULL)
			ballTexture = framework->loadTexture("Ball.png");
	}
	return isRun;
}

void SDL_GraphicWorkerImpl::drawPlayer(AbstractPlayer &player){
	framework->setRenderTarget(screen);
	SDL_Rect rect = {player.getPosX(), player.getPosY(), player.getWidth(), player.getHeight()};
	framework->drawTexture(playerTexture, NULL, &rect);
	framework->setRenderTarget(NULL);
}

void SDL_GraphicWorkerImpl::drawBall(Ball &ball){
	framework->setRenderTarget(screen);
	SDL_Rect rect = {ball.getPosX(), ball.getPosY(), ball.getWidth(), ball.getHeight()};
	framework->drawTexture(ballTexture, NULL, &rect);
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