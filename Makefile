NAME = Pong

SRCS :=	AbstractPlayer.cpp  \
	Ball.cpp  \
	BotPlayerImpl.cpp  \
	main.cpp  \
	Pong.cpp  \
	Racket.cpp  \
	SDL_Framework.cpp  \
	SDL_GraphicWorkerImpl.cpp \
	UserPlayerImpl.cpp

DIR_SRC := $(CURDIR)/src
DIR_OBJ := $(CURDIR)/obj

OBJS := $(SRCS:.cpp=.o)

OBJS := $(addprefix $(DIR_OBJ)/, $(OBJS))
SRCS := $(addprefix $(DIR_SRC)/, $(SRCS))

FLAGS = -Wall -Wextra -Werror

FLAGS = 

ifeq ($(UNAME_S),Darwin)

	CC :=			clang
	SDL2_INC =      -I $(CURDIR)/frameworks/SDL2.framework/Headers/ \
                    -I $(CURDIR)/frameworks/SDL2_mixer.framework/Headers \
                    -I $(CURDIR)/frameworks/SDL2_ttf.framework/Headers/ \
                    -I $(CURDIR)/frameworks/SDL2_image.framework/Headers/
	SDL2_FLAGS =
	FLAG_F =        -F frameworks
	SDL2_LINK =     -rpath frameworks -framework SDL2 -framework SDL2_mixer -framework SDL2_image -framework SDL2_ttf

endif

ifeq ($(UNAME_S),Linux)
	CC :=           gcc
    SDL2_INC =
    SDL2_FLAGS =  
    FLAG_F =
    SDL2_LINK =  `sdl2-config --cflags --libs` -lSDL2 -lSDL2_gfx -lSDL2_image -lSDL2_ttf -lSDL2_mixer 
    OTHER_FLAGS =       -pthread
endif

CC = clang++

all: $(NAME)

$(LIBFT_A):
	@make -C libft/

$(DIR_OBJ):
	@mkdir -p $(DIR_OBJ)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(SDL2_LINK) $(MATH_LINK) $(SDL2_INC) -o $@ $^ 

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.cpp | $(DIR_OBJ)
	$(CC) $(FLAGS) $(SDL2_INC) $(SDL2_FLAGS) -c $< -o $@

clean:
	/bin/rm -rf $(OBJS)
	/bin/rm -rf $(DIR_OBJ)

fclean: clean
	/bin/rm -rf $(NAME)

re: fclean all

.PHONY: all fclean clean re
