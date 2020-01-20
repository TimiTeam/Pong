#ifndef __SDL_FRAMEWORK_HPP
# define __SDL_FRAMEWORK_HPP

# include <iostream>
# include "SDL_Includes.hpp"

class SDL_Framework
{
private:
	int sizeX;
	int sizeY;
	SDL_Window	*win;
	SDL_Renderer *ren;
	SDL_Texture	 *mainTexture;
	TTF_Font	*font;

public:
	SDL_Framework();
	SDL_Framework(int sizeX, int sizeY);
	SDL_Framework(const SDL_Framework& src);
	~SDL_Framework();
	SDL_Framework& operator=(const SDL_Framework& src);
	bool initSDL();
	void close();
	void drawTexture(SDL_Texture *texture, SDL_Rect *srcRect, SDL_Rect *dstRect);
	void clearScrean();
	bool setRenderTarget(SDL_Texture *target);
	void renderPresent(SDL_Texture *text);
	SDL_Texture *loadTexture(std::string path);
	SDL_Texture *getMainTexture();
};
#endif
