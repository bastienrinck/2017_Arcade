NAME	= lib_arcade_nibbler.so

CC	= g++

RM	= rm -f

SRCS	= ./Nibbler.cpp

CPPFLAGS = -I../../include -I../../interfaces
CPPFLAGS += -W -Wall -Wextra

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) -shared -o $(NAME) -fPIC $(SRCS) $(CPPFLAGS)
	mv $(NAME) ../
clean:

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
