#include "SDL_GraphicWorkerImpl.hpp"

SDL_GraphicWorkerImpl *SDL_GraphicWorkerImpl::selfGW = 0;

SDL_GraphicWorkerImpl::SDL_GraphicWorkerImpl()
{
	playerArrow = NULL;
	playerKeyboard = NULL;
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

void SDL_GraphicWorkerImpl::setPlayerOnArrows(AbstractPlayer &player){
	playerArrow = &player;
}

void SDL_GraphicWorkerImpl::setPlayerOnKeyboard(AbstractPlayer &player){
	playerKeyboard = &player;
}

void SDL_GraphicWorkerImpl::printMenu(){
	isMulti = false;
}

bool SDL_GraphicWorkerImpl::isMultiplayerGame(){
	return isMulti;
}


void SDL_GraphicWorkerImpl::makeKeysEvent(SDL_Keycode up, SDL_Keycode down, AbstractPlayer &player){
	SDL_Event	e;
	eDirection result = NON;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))
			isRun = false;
		else if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP)
		{
			if (e.key.keysym.sym == up){
				result = UP;
			}
			else if (e.key.keysym.sym == down){
				result = DOWN;
			}
		}
	}
	player.updateState(result, 0, winSizeY);	
}

void SDL_GraphicWorkerImpl::getPlayerInputArrows(){
	if (playerArrow != NULL)
		makeKeysEvent(SDLK_UP, SDLK_DOWN, *playerArrow);
}

void SDL_GraphicWorkerImpl::getPlayerInputKeyboard(){
	if (playerKeyboard != NULL)
		makeKeysEvent(SDLK_w, SDLK_s, *playerKeyboard);
}

void SDL_GraphicWorkerImpl::updatePlayers(){
	getPlayerInputArrows();
	getPlayerInputKeyboard();
}

bool SDL_GraphicWorkerImpl::initGame(const std::string title, int sizeX, int sizeY){
	isRun = false;
	
	winSizeY = sizeY;
	winSizeX = sizeX;
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