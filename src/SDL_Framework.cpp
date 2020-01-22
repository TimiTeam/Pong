#include "SDL_Framework.hpp"

SDL_Framework::SDL_Framework()
{
	win = NULL;
	ren = NULL;
	mainTexture = NULL;
	font = NULL;
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
	}
	else{
		ret = SDL_CreateTextureFromSurface(ren, surf);
		SDL_FreeSurface(surf);
		if (ret == NULL)
			std::cout << "Can't create texture\n";
	}
	return ret;
}


bool SDL_Framework::loadTTF(std::string path, int size){
	font = TTF_OpenFont(path.c_str(), size);
	if (font == NULL){
		std::cout << "Can't open font: "+path+": "+std::string(TTF_GetError())+"\n";
		return false;
	}
	return true;
}

SDL_Texture *SDL_Framework::createTextTexture(std::string str, int r, int g, int b){
	SDL_Texture *result = NULL;
	SDL_Surface *surf = NULL; 
	if (font != NULL){
		SDL_Color col = {r, g, b, 0};
		surf = TTF_RenderText_Solid(font, str.c_str(), col);
		if (surf != NULL){
			result = SDL_CreateTextureFromSurface(ren, surf);
			SDL_FreeSurface(surf);
		}
		else
			std::cout << "Can't create texture: "+std::string(TTF_GetError())+"\n";
	}
	else
		std::cout << "Missing fond\n";
	return result;
}

bool SDL_Framework::initSDL(const std::string title, int sizeX, int sizeY){
	bool ret = true;


	this->sizeX = sizeX;
	this->sizeY = sizeY;
	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0){
		std::cout << "Can't init SDL: "+std::string(SDL_GetError())+"\n";
		ret = false;
	}
	else
	{
		win = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, sizeX, sizeY, SDL_WINDOW_SHOWN | SDL_WINDOW_MOUSE_FOCUS);
		if (win == NULL){
			std::cout << "Can't create window: "+std::string(SDL_GetError())+"\n";
			ret = false;
		}
		else
		{
			ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
			if (ren == NULL){
				std::cout << "Can't create renderer: "+std::string(SDL_GetError())+"\n";
				ret = false;
			}
			else{
				SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0xFF);
				int flags = IMG_INIT_PNG;
				if(!(IMG_Init(flags) & flags)){
					std::cout << "Can't init SDL IMG: "+std::string(IMG_GetError())+"\n";
                    ret = false;
                }
				else
					mainTexture = SDL_CreateTexture(ren, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, sizeX, sizeY);
				if (mainTexture == NULL){
					std::cout << "Can't create main texture: "+std::string(SDL_GetError())+"\n";
					ret = false;
				}else
				{
					if(TTF_Init() == -1){
						ret = false;
						std::cout << "Can't init SDL TTF : "+std::string(TTF_GetError())+"\n";
					}
				}
			}
		}
	}
	return ret;
}

void SDL_Framework::close(){
	if (ren != NULL){
		SDL_DestroyRenderer(ren);
		ren = NULL;
	}
	if (win != NULL){
    	SDL_DestroyWindow(win);
		win = NULL;
	}
	if (mainTexture != NULL){
		SDL_DestroyTexture(mainTexture);
		mainTexture = NULL;
	}
	TTF_Quit();
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