#ifndef __SDL_GRAPHICWORKERIMPL_HPP
# define __SDL_GRAPHICWORKERIMPL_HPP

# include <iostream>
# include "IGraphicWorker.hpp"
# include "SDL_Framework.hpp"

class SDL_GraphicWorkerImpl : public IGraphicWorker 
{
private:
	SDL_Texture	*screen;
	SDL_Texture	*playerTexture;
	SDL_Texture	*ballTexture;
	SDL_Framework framework;
	bool isRun;

public:
	SDL_GraphicWorkerImpl();
	SDL_GraphicWorkerImpl(const SDL_GraphicWorkerImpl& src);
	~SDL_GraphicWorkerImpl();
	SDL_GraphicWorkerImpl& operator=(const SDL_GraphicWorkerImpl& src);

	// IGraphicWorker
	bool initGame();
	bool isRunGame();
	eDirection getPlayerInput();
	void drawPlayer(AbstractPlayer &player);
	void drawBall(Ball ball);
	void clearScreen();
	void updateScreen();
	void closeGame();
	// --------------
};
#endif
