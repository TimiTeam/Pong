#ifndef __SDL_FRAMEWORK_HPP
# define __SDL_FRAMEWORK_HPP

# include <iostream>
# include "SDL_Includes.hpp"

class SDL_Framework
{
private:
	static SDL_Texture *renderTexture;
	int sizeX;
	int sizeY;
	SDL_Window	*win;
	SDL_Renderer *ren;
	TTF_Font	*font;

public:
	SDL_Framework();
	SDL_Framework(const SDL_Framework& src);
	~SDL_Framework();
	SDL_Framework& operator=(const SDL_Framework& src);
	bool initSDL(const std::string title, int sizeX, int sizeY);
	void close();
	void drawTexture(SDL_Texture *texture, SDL_Rect *srcRect, SDL_Rect *dstRect);
	void clearScrean();
	bool setRenderTarget(SDL_Texture *target);
	void renderPresent(SDL_Texture *text);
	SDL_Texture *loadTexture(std::string path);
	SDL_Texture *createTextTexture(std::string str, int r, int g, int b);
	SDL_Texture *getMainTexture();
	void setDrawColor(unsigned char r, unsigned  char g, unsigned char b);
	void drawLine(int x1, int y1, int x2, int y2);
	bool loadTTF(std::string pth, int size);
	void drawRectArea(SDL_Rect *rect);
};
#endif
