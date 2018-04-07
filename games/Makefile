CC	= g++

RM	= rm -f

SUBDIRS	= pacman nibbler

all:
	for dir in $(SUBDIRS); do \
	$(MAKE) -C $$dir; \
	done

clean:

fclean: clean
	$(RM) *.so

re: fclean all

.PHONY: all clean fclean re $(SUBDIRS)
