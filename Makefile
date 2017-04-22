CC =	g++

RM =	rm -f

CPPFLAGS +=	-W -Wall -Wextra
CPPFLAGS +=	-I./include `freetype-config --cflags` -std=c++14 -g3

LDFLAGS = `pkg-config --static --libs glfw3` -lfreetype

NAME = ultra-ninja_VS_falling_zombies

SRCS_CPP = 	source/main.cpp \
		source/my_opengl.cpp \
		source/display.cpp \
		source/render_context.cpp \
		source/gl3w.cpp \
		source/FreeTypeLib.cpp \
		source/Physics.cpp \
		source/Entity.cpp

OBJS = 	$(SRCS_CPP:.cpp=.o)

all: $(NAME)

$(NAME):$(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
