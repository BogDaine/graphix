NAME		:=	shaderplayground.exe
LIBS		:=				\
		glew				\
		glfw3				\
		glu32				\
		gdi32				\
		opengl32			\

INCLUDES	:=									\
		include									\
		headers									\
		../../include							\
		../../include/glfw						\
		../../common/include/gl_boilerplate		\
		
GLBP_SRC_DIR	:= ../../common/gl_boilerplate\src

INCLUDES	:= $(addprefix -I, $(INCLUDES))
LIBS		:= $(addprefix -l, $(LIBS))
LIB_DIR		:= ../../lib/
			
BUILD_DIR	:= .build

SRC_DIR		:= src
SRCS		:=				\
	shaderplayground.cpp	\
	windowstuff.cpp			\
	input.cpp				\
	openglstuff.cpp			\
	appinfo.cpp				\
							\
	render.cpp				\
	UniformBlockGL.cpp		\
	ShaderGL.cpp			\
#	shader.cpp
#glew.c

OBJS		:= $(SRCS:%.cpp=$(BUILD_DIR)\\%.o)
#OBJS += $(BUILD_DIR)\ShaderGL.o

$(info $(OBJS))

SRCS		:= $(SRCS:%=$(SRC_DIR)\\%)
#SRCS += 	..\..\common\gl_boilerplate\src\ShaderGL.cpp

DEPS		:= $(OBJS:%.o=%.d)


#commands
RM 			:= del
AR 			:= ar
ARFLAGS 	:= -r -c -s

#flags

CXX			:= g++
CFLAGS		:= -Wall
#CFLAGS		:= -Wall -Wextra -Werror
CPPFLAGS	:= -MMD -MP $(INCLUDES)
CPPFLAGS += -DGLEW_STATIC
LDFLAGS		:= -L$(LIB_DIR)

all: $(NAME)

$(NAME)		:	$(OBJS)
	$(CXX) $(CFLAGS) $(CPPFLAGS) $(OBJS) $(LDFLAGS) $(LIBS) -o $(NAME)

$(BUILD_DIR)\\%.o: $(SRC_DIR)\\%.cpp
	if not exist $(@D) mkdir $(@D)
	$(CXX) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

$(BUILD_DIR)\\%.o: $(GLBP_SRC_DIR)\\%.cpp
	if not exist $(@D) mkdir $(@D)
	$(CXX) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<


test:
	$(MAKE) -C ../../ test
#$(info $(OBJS))

-include $(DEPS)

clean:
	$(RM) $(OBJS) $(DEPS)
	$(info $(DEPS))
	$(info cleaning...)
fclean: clean
	$(RM) $(NAME)
re:
	$(MAKE) fclean
	$(MAKE) all