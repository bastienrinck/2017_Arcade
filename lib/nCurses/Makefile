NAME	= lib_arcade_ncurses.so

CC	= g++

RM	= rm -f

SRCS	= ./NCurses.cpp

CPPFLAGS = -I../../include -I../../interfaces
CPPFLAGS += -W -Wall -Wextra

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) -shared -o $(NAME) -fPIC $(SRCS) $(CPPFLAGS) -lncurses
	mv $(NAME) ../

clean:
	$(RM)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
