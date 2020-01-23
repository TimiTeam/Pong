#ifndef __SDL_GRAPHICWORKERIMPL_HPP
# define __SDL_GRAPHICWORKERIMPL_HPP

# include <iostream>
# include "IGraphicWorker.hpp"
# include "SDL_Framework.hpp"
# include <map>

# define FRAME_VALUES 10

class SDL_GraphicWorkerImpl : public IGraphicWorker 
{
private: 
	static SDL_GraphicWorkerImpl *selfGW;
	std::map<SDL_Keycode, Uint32> hooksEvent;
	int winSizeX;
	int winSizeY;
	SDL_Framework *framework;
	SDL_Texture	*screen;
	SDL_Texture	*playerTexture;
	SDL_Texture	*ballTexture;
	bool isRun;
	bool isMulti;
	Uint32 frametimes[FRAME_VALUES];
	Uint32 frametimelast;
	Uint32 framecount;
	long long framespersecond;
	AbstractPlayer *playerArrow;
	AbstractPlayer *playerKeyboard;

	SDL_GraphicWorkerImpl();

public:
	SDL_GraphicWorkerImpl(const SDL_GraphicWorkerImpl& src);
	~SDL_GraphicWorkerImpl();
	SDL_GraphicWorkerImpl& operator=(const SDL_GraphicWorkerImpl& src);

	static SDL_GraphicWorkerImpl &getInstance();

	// IGraphicWorker
	bool initGame(const std::string title, int sizeX, int sizeY);
	bool isRunGame();
	void updatePlayers();
	void printMenu();
	bool isMultiplayerGame();
	void printBalckText(std::string text, int posX, int posY, int height, int width);
	void setPlayerOnArrows(AbstractPlayer &player);
	void setPlayerOnKeyboard(AbstractPlayer &player);
	void drawPlayer(AbstractPlayer &player);
	void drawBall(Ball &ball);
	void clearScreen();
	void updateScreen();
	void closeGame();
	void initFPS();
	int getFPS();
	void delay(int mSec);
	void getUserInput();
	// --------------
};
#endif
