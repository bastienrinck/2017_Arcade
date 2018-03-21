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

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
