#ifndef SDL_INCLUDES_HPP
# define SDL_INCLUDES_HPP

# ifdef __APPLE__

#  include <SDL.h>
#  include <SDL_mixer.h>
#  include <SDL_ttf.h>
#  include <SDL_image.h>
#  define RMASK 0
#  define GMASK 0
#  define BMASK 0
# endif

# ifdef __linux__

#  include <SDL2/SDL.h>
#  include <SDL2/SDL_mixer.h>
#  include <SDL2/SDL_ttf.h>
#  include <SDL2/SDL_image.h>
#  if SDL_BYTEORDER == SDL_BIG_ENDIAN
#   define RMASK 0xff000000
#   define GMASK 0x00ff0000
#   define BMASK 0x0000ff00
#  else
#   define RMASK 0x000000ff
#   define GMASK 0x0000ff00
#   define BMASK 0x00ff0000
#  endif
# endif

#endif