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
	if (this != &src){
		this->winSizeX = src.winSizeX;
		this->winSizeY = src.winSizeY;
		this->framework = src.framework;
		this->screen = src.screen;
		this->playerTexture = src.playerTexture;
		this->ballTexture = src.ballTexture;
		this->isRun = src.isRun;
		this->isMulti = src.isMulti;
		this->playerArrow = src.playerArrow;
		this->playerKeyboard = src.playerKeyboard;
	}
	return *this;
}

bool SDL_GraphicWorkerImpl::isRunGame(){
	return isRun;
}


void SDL_GraphicWorkerImpl::printBalckText(std::string text, int posX, int posY, int height, int width){
	SDL_Texture *texture = framework->createTextTexture(text, 0, 0, 0);
	if (texture == NULL){
		std::cout << "Error: can't draw text\n";
	}else{
		SDL_Rect rect = {posX, posY, width, height};
		framework->drawTexture(texture, NULL, &rect);
		SDL_DestroyTexture(texture);
	}
}

void SDL_GraphicWorkerImpl::setPlayerOnArrows(AbstractPlayer &player){
	playerArrow = &player;
}

void SDL_GraphicWorkerImpl::setPlayerOnKeyboard(AbstractPlayer &player){
	playerKeyboard = &player;
}

void SDL_GraphicWorkerImpl::printMenu(){
	bool menuRun = true;
	SDL_Event e;

	std::string menuHeader = "Choose type";
	std::string singl = "Player vs Bot";
	std::string multi = "Player vs Player";

	int headerSizeX = winSizeX / 2;
	int headerSizeY = winSizeX / 4;
	int typeSizeX = winSizeX / 3;
	int typeSizeY = headerSizeY / 2;
	SDL_Rect choice = {winSizeX / 2 - typeSizeX / 2 - 10 , 5 + headerSizeY - 5, typeSizeX + 20, typeSizeY + 10};

	while (menuRun){
		clearScreen();
		printBalckText(menuHeader, winSizeX / 4, 5, headerSizeY, headerSizeX);
		framework->setDrawColor(15, 130, 55);
		framework->drawRectArea(&choice);
		framework->setDrawColor(255,255,255);
		printBalckText(singl, winSizeX / 2 - typeSizeX / 2, 5 + headerSizeY, typeSizeY, typeSizeX);
		printBalckText(multi, winSizeX / 2 - typeSizeX / 2, 5 + headerSizeY + typeSizeY, typeSizeY, typeSizeX);
		updateScreen();
		while (SDL_PollEvent(&e)){
			if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)){
				menuRun = false;
				isRun = false;
			}else if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP)
			{
				if (e.key.keysym.sym == SDLK_UP){
					choice.y =  5 + headerSizeY - 5;
					isMulti = false;
				}
				if (e.key.keysym.sym == SDLK_DOWN){
					choice.y =  5 + headerSizeY + typeSizeY - 5;
					isMulti = true;
				}
				if (e.key.keysym.sym == SDLK_RETURN){
					menuRun = false;
				}
			}
		}
	}
}

bool SDL_GraphicWorkerImpl::isMultiplayerGame(){
	return isMulti;
}

void SDL_GraphicWorkerImpl::updatePlayers(){
	SDL_Event	e;
	eDirection resultKey = NON;
	eDirection resultArrows = NON;

	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))
			isRun = false;
		else if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP)
		{
			if (e.key.keysym.sym == SDLK_UP){
				resultArrows = UP;
			}
			if (e.key.keysym.sym == SDLK_DOWN){
				resultArrows = DOWN;
			}
			if (e.key.keysym.sym == SDLK_w){
				resultKey = UP;
			}
			if (e.key.keysym.sym == SDLK_s){
				resultKey = DOWN;
			}
		}
	}
	if (playerArrow != NULL)
		playerArrow->updateState(resultArrows, 0, winSizeY);
	if (playerKeyboard != NULL)
		playerKeyboard->updateState(resultKey, 0, winSizeY);
}

bool SDL_GraphicWorkerImpl::initGame(const std::string title, int sizeX, int sizeY){
	isRun = false;
	
	winSizeY = sizeY;
	winSizeX = sizeX;
	if (framework != NULL && framework->initSDL(title,  sizeX,  sizeY)){
		isRun = true;
		if (playerTexture == NULL)
			playerTexture = framework->loadTexture("Racket.jpeg");
		if (ballTexture == NULL)
			ballTexture = framework->loadTexture("Ball.png");
		framework->loadTTF("KarmaFuture.ttf", 28);
	}
	return isRun;
}

void SDL_GraphicWorkerImpl::drawPlayer(AbstractPlayer &player){
	SDL_Rect rect = {player.getPosX(), player.getPosY(), player.getWidth(), player.getHeight()};
	framework->drawTexture(playerTexture, NULL, &rect);
}

void SDL_GraphicWorkerImpl::drawBall(Ball &ball){
	SDL_Rect rect = {ball.getPosX(), ball.getPosY(), ball.getWidth(), ball.getHeight()};
	framework->drawTexture(ballTexture, NULL, &rect);
	framework->setDrawColor(1, 1, 1);
	framework->drawLine(winSizeX / 2, 0, winSizeX / 2, winSizeY);
}

void SDL_GraphicWorkerImpl::updateScreen(){
	framework->renderPresent(screen);
	framework->setDrawColor(254, 254, 254);	
}

void SDL_GraphicWorkerImpl::clearScreen(){
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

void SDL_GraphicWorkerImpl::delay(int sec){
	SDL_Delay(sec * 1000);
}