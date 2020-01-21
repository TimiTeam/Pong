#ifndef __SDL_GRAPHICWORKERIMPL_HPP
# define __SDL_GRAPHICWORKERIMPL_HPP

# include <iostream>
# include "IGraphicWorker.hpp"
# include "SDL_Framework.hpp"
class SDL_GraphicWorkerImpl : public IGraphicWorker 
{
private: 
	static SDL_GraphicWorkerImpl *selfGW;
	int winsizeX;
	int winSizeY;
	SDL_Framework *framework;
	SDL_Texture	*screen;
	SDL_Texture	*playerTexture;
	SDL_Texture	*ballTexture;
	bool isRun;
	SDL_GraphicWorkerImpl();
	AbstractPlayer *listner;

public:
	SDL_GraphicWorkerImpl(const SDL_GraphicWorkerImpl& src);
	~SDL_GraphicWorkerImpl();
	SDL_GraphicWorkerImpl& operator=(const SDL_GraphicWorkerImpl& src);

	// IGraphicWorker
	bool initGame(const std::string title, int sizeX, int sizeY);
	bool isRunGame();
	void setKeyListner(AbstractPlayer &player);
	void getPlayerInput();
	void drawPlayer(AbstractPlayer &player);
	void drawBall(Ball ball);
	void clearScreen();
	void updateScreen();
	void closeGame();
	static SDL_GraphicWorkerImpl &getInstance();
	// --------------
};
#endif
