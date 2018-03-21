NAME	= lib_arcade_SFML.so

CC	= g++

RM	= rm -f

SRCS	= ./SFML.cpp \
	  ../../include/Color.cpp \
	  ../../include/TextBox.cpp \
	  ../../include/PixelBox.cpp

CPPFLAGS = -I../../include -I../../interfaces
CPPFLAGS += -W -Wall -Wextra

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) -shared -o $(NAME) -fPIC $(SRCS) $(CPPFLAGS)

clean:
	$(RM)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
