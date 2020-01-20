#include "SDL_GraphicWorkerImpl.hpp"

SDL_GraphicWorkerImpl::SDL_GraphicWorkerImpl()
{
	isRun = true;
	framework.initSDL();
	screen = framework.getMainTexture();
}

SDL_GraphicWorkerImpl::SDL_GraphicWorkerImpl(const SDL_GraphicWorkerImpl& src)
{
	*this = src;
}

SDL_GraphicWorkerImpl::~SDL_GraphicWorkerImpl()
{
	
}

SDL_GraphicWorkerImpl& SDL_GraphicWorkerImpl::operator=(const SDL_GraphicWorkerImpl& src)
{
	return *this;
}

bool SDL_GraphicWorkerImpl::isRunGame(){
	return isRun;
}


eDirection SDL_GraphicWorkerImpl::getPlayerInput(){
	SDL_Event	e;
	eDirection result = NON;

	while (SDL_PollEvent(&e) && isRun)
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
	return result;
}


bool SDL_GraphicWorkerImpl::initGame(){
	return true;
}

void SDL_GraphicWorkerImpl::drawPlayer(AbstractPlayer &player){
	framework.setRenderTarget(screen);
	framework.drawTexture(playerTexture, NULL, NULL);
	framework.setRenderTarget(NULL);
}

void SDL_GraphicWorkerImpl::drawBall(Ball ball){
	framework.setRenderTarget(screen);
	framework.drawTexture(ballTexture, NULL, NULL);
	framework.setRenderTarget(NULL);
}

void SDL_GraphicWorkerImpl::updateScreen(){
	framework.drawTexture(screen, NULL, NULL);
	framework.renderPresent(screen);
}

void SDL_GraphicWorkerImpl::clearScreen(){
	framework.clearScrean();
}

void SDL_GraphicWorkerImpl::closeGame(){
	SDL_DestroyTexture(screen);
	SDL_DestroyTexture(ballTexture);
	SDL_DestroyTexture(playerTexture);
	framework.close();
}