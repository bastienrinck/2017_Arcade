NAME	= lib_arcade_nCurses.so

CC	= g++

RM	= rm -f

SRCS	= ./nCurses.cpp \
	  ../../include/Color.cpp \
	  ../../include/TextBox.cpp \
	  ../../include/PixelBox.cpp

CPPFLAGS = -I../../include -I../../interfaces
CPPFLAGS += -W -Wall -Wextra

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) -shared -o $(NAME) -fPIC $(SRCS) $(CPPFLAGS) -lncurses

clean:
	$(RM)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
