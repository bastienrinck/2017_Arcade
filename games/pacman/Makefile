NAME	= lib_arcade_pacman.so

CC	= g++

RM	= rm -f

SRCS	= ./Pacman.cpp

CPPFLAGS = -I../../include -I../../interfaces
CPPFLAGS += -W -Wall -Wextra

all: $(NAME)

$(NAME):
	 $(CC) -shared -o $(NAME) -fPIC $(SRCS) $(CPPFLAGS)
	mv $(NAME) ../

clean:

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
