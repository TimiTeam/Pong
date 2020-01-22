#ifndef __SDL_GRAPHICWORKERIMPL_HPP
# define __SDL_GRAPHICWORKERIMPL_HPP

# include <iostream>
# include "IGraphicWorker.hpp"
# include "SDL_Framework.hpp"
class SDL_GraphicWorkerImpl : public IGraphicWorker 
{
private: 
	static SDL_GraphicWorkerImpl *selfGW;
	int winSizeX;
	int winSizeY;
	SDL_Framework *framework;
	SDL_Texture	*screen;
	SDL_Texture	*playerTexture;
	SDL_Texture	*ballTexture;
	bool isRun;
	bool isMulti;
	AbstractPlayer *playerArrow;
	AbstractPlayer *playerKeyboard;

	SDL_GraphicWorkerImpl();
	void makeKeysEvent(SDL_Keycode up, SDL_Keycode down, AbstractPlayer &playe);
	void getPlayerInputArrows();
	void getPlayerInputKeyboard();

public:
	SDL_GraphicWorkerImpl(const SDL_GraphicWorkerImpl& src);
	~SDL_GraphicWorkerImpl();
	SDL_GraphicWorkerImpl& operator=(const SDL_GraphicWorkerImpl& src);

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
	void delay(int sec);
	static SDL_GraphicWorkerImpl &getInstance();
	// --------------
};
#endif
