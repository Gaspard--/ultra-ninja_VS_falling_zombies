CPPFLAGS +=	-W -Wall -Wextra
CPPFLAGS +=	-I./include `freetype-config --cflags` -std=c++14 -g3

LDFLAGS = `pkg-config --static --libs glfw3` -lfreetype -lsfml-audio -lsfml-system

NAME = ultra-ninja_VS_falling_zombies

SRCS_CPP = 	source/main.cpp \
		source/my_opengl.cpp \
		source/TextureHandler.cpp \
		source/SoundHandler.cpp \
		source/display.cpp \
		source/render_context.cpp \
		source/render_texture.cpp \
		source/gl3w.cpp \
		source/FreeTypeLib.cpp \
		source/Physics.cpp \
		source/Input.cpp \
		source/Entity.cpp \
		source/Logic.cpp \
		source/Player.cpp \
		source/Enemy.cpp \
		source/EnemyCommon.cpp \
		source/EnemyLarge.cpp \
		source/EnemySmall.cpp \
		source/EnemyShooter.cpp \
		source/Flesh.cpp \
		source/Sword.cpp \
		source/Bullet.cpp \
		source/GUI.cpp

OBJS = 	$(SRCS_CPP:.cpp=.o)

all: $(NAME)

$(NAME):$(OBJS)
	$(CXX) $(OBJS) -o $(NAME) $(LDFLAGS)

grep_todo:
	@grep --color=auto -ir --include "*.cpp" -E "(FIXME|TODO)" . || true
	@grep --color=auto -ir --include "*.hpp" -E "(FIXME|TODO)" . || true

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean
	make all

.PHONY: all clean fclean re grep_todo
