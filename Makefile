NAME = Pong

UNAME_S := $(shell uname -s)

SRCS :=	AbstractPlayer.cpp  \
	Ball.cpp  \
	BotPlayerImpl.cpp  \
	main.cpp  \
	Pong.cpp  \
	SDL_Framework.cpp  \
	SDL_GraphicWorkerImpl.cpp \
	UserPlayerImpl.cpp \
	PlayerFactory.cpp

DIR_SRC := $(CURDIR)/src
DIR_OBJ := $(CURDIR)/obj

OBJS := $(SRCS:.cpp=.o)

OBJS := $(addprefix $(DIR_OBJ)/, $(OBJS))
SRCS := $(addprefix $(DIR_SRC)/, $(SRCS))

FLAGS = -Wall -Wextra -Werror

FLAGS = 

ifeq ($(UNAME_S),Darwin)
	CC :=			clang++
	SDL2_INC =      -I $(CURDIR)/frameworks/SDL2.framework/Headers/ \
                    -I $(CURDIR)/frameworks/SDL2_mixer.framework/Headers \
                    -I $(CURDIR)/frameworks/SDL2_ttf.framework/Headers/ \
                    -I $(CURDIR)/frameworks/SDL2_image.framework/Headers/
	SDL2_FLAGS =
	FLAG_F =        -F frameworks
	SDL2_LINK =     -rpath frameworks -framework SDL2 -framework SDL2_mixer -framework SDL2_image -framework SDL2_ttf
endif

ifeq ($(UNAME_S),Linux)
	CC :=           g++
    SDL2_INC =
    SDL2_FLAGS =   `sdl2-config --cflags`
    FLAG_F =
    SDL2_LINK =     `sdl2-config --libs` -lSDL2_ttf -lSDL2_image -lSDL2_mixer
    OTHER_FLAGS =       -pthread
endif

all: $(NAME)

$(LIBFT_A):
	@make -C libft/

$(DIR_OBJ):
	@mkdir -p $(DIR_OBJ)

$(NAME): $(OBJS)
	$(CC) -o $@ $^ $(FLAG_F) $(SDL2_LINK) $(SDL2_INC)

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.cpp | $(DIR_OBJ)
	$(CC) -g $(FLAGS) -c -o $@ $^ $(FLAG_F) $(SDL2_INC) $(SDL2_FLAGS)

clean:
	/bin/rm -rf $(OBJS)
	/bin/rm -rf $(DIR_OBJ)

fclean: clean
	/bin/rm -rf $(NAME)

re: fclean all

.PHONY: all fclean clean re
