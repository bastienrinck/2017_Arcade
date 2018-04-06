NAME	= arcade

CC	= g++

RM	= rm -f

SRCS	= ./src/main.cpp \
	  ./src/core/core.cpp \
	  ./include/TextBox.cpp	\
	  ./include/PixelBox.cpp \
	  ./include/Color.cpp

OBJS	= $(SRCS:.cpp=.o)

LDFLAGS = -ldl
CPPFLAGS = -I./interfaces -I./templates -I./include
CPPFLAGS += -W -Wall -Wextra

all: $(NAME)

$(NAME): core games graphicals

core:	$(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS) -rdynamic

games:
	$(MAKE) -C games

graphicals:
	$(MAKE) -C lib

clean:
	$(RM) $(OBJS)
	$(MAKE) -C games clean
	$(MAKE) -C lib clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C games fclean
	$(MAKE) -C lib fclean

re: fclean all

.PHONY: all clean fclean re core games graphicals
