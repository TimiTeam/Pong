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
	TTF_Font	*font; 

public:

	SDL_Framework();
	SDL_Framework(const SDL_Framework& src);
	~SDL_Framework();
	SDL_Framework& operator=(const SDL_Framework& src);
};
#endif
