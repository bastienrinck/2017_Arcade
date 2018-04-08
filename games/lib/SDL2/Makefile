NAME	= lib_arcade_sdl2.so

CC	= g++

RM	= rm -f

SRCS	= ./sdl2.cpp

CPPFLAGS = -I../../include -I../../interfaces
CPPFLAGS += -W -Wall -Wextra

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) -shared -o $(NAME) -fPIC $(SRCS) $(CPPFLAGS) -lSDL2 -lSDL2_ttf
	mv $(NAME) ../
clean:
	$(RM)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
