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
		source/Input.cpp \
		source/Entity.cpp \
		source/Logic.cpp \
		source/Player.cpp \
		source/Enemy.cpp \
		source/EnemyCommon.cpp \
		source/GUI.cpp

OBJS = 	$(SRCS_CPP:.cpp=.o)

all: grep_todo $(NAME)

$(NAME):$(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

grep_todo:
	@grep --color=auto -ir --include "*.cpp" -E "(FIXME|TODO)" . || true
	@grep --color=auto -ir --include "*.hpp" -E "(FIXME|TODO)" . || true

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re grep_todo
