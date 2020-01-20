#include "SDL_Framework.hpp"

SDL_Framework::SDL_Framework()
{
	
}

SDL_Framework::SDL_Framework(int sizeX, int sizeY): sizeX(sizeX), sizeY(sizeY)
{
}

SDL_Framework::SDL_Framework(const SDL_Framework& src)
{
	*this = src;
}

SDL_Framework::~SDL_Framework()
{
	
}

SDL_Framework& SDL_Framework::operator=(const SDL_Framework& src)
{
	if (this != &src){
		this->sizeX = src.sizeX;
		this->sizeY = src.sizeY;
		this->win = src.win;
		this->ren = src.ren;
		this->font = src.font;
		this->mainTexture = src.mainTexture;
	}
	return *this;
}

void SDL_Framework::drawTexture(SDL_Texture *texture, SDL_Rect *srcRect, SDL_Rect *dstRect){
	SDL_RenderCopy(ren, texture, srcRect, dstRect);
}

SDL_Texture *SDL_Framework::loadTexture(std::string path){
	SDL_Texture *ret = NULL;
	SDL_Surface *surf = IMG_Load(path.c_str());
	
	if (surf == NULL){
		std::cout << "Can't locad image: "+path+"\n";
		surf = SDL_CreateRGBSurface(0, sizeX / 4, sizeY / 4, 32,
                                   RMASK, GMASK, BMASK, 0);
	}
	if (surf != NULL){
		ret = SDL_CreateTextureFromSurface(ren, surf);
		SDL_FreeSurface(surf);
	}
	if (ret == NULL)
		std::cout << "Can't create texture\n";
	return ret;
}

bool SDL_Framework::initSDL(){
	bool ret = true;
	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0)
		ret = false;
	else
	{
		win = SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, sizeX, sizeY, SDL_WINDOW_SHOWN | SDL_WINDOW_MOUSE_FOCUS);
		if (win == NULL)
			ret = false;
		else
		{
			ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
			if (ren == NULL)
				ret = false;
			else{
				SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0xFF);
				int flags=IMG_INIT_JPG|IMG_INIT_PNG;
				if(!(IMG_Init(flags) & flags)){
                    ret = false;
                }
				else
					mainTexture = SDL_CreateTexture(ren, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, sizeX, sizeY);
				if (mainTexture == NULL)
					ret = false;
			}
		}
	}
	return ret;
}

void SDL_Framework::close(){
	SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    ren = NULL;
    win = NULL;
    IMG_Quit();
    SDL_Quit();
}

void SDL_Framework::clearScrean(){
	SDL_RenderClear(ren);
}


bool SDL_Framework::setRenderTarget(SDL_Texture *target){
	if( SDL_SetRenderTarget(ren, target) != 0)
		return false;
	return true;
}

void SDL_Framework::renderPresent(SDL_Texture *text){
	drawTexture(text, NULL, NULL);
	SDL_RenderPresent(ren);
}

SDL_Texture *SDL_Framework::getMainTexture(){
	return mainTexture;
}