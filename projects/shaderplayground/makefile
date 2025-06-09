NAME		:=	shaderplayground.exe
LIBS		:=				\
		glew				\
		glfw3				\
		glu32				\
		gdi32				\
		opengl32			\
#		imgui_glfw			\

INCLUDES	:=									\
		include									\
		headers									\
		../../include							\
		../../include/glfw						\
		../../thirdparty/imgui					\
		../../thirdparty/imgui/backends			\
		../../common							\
		../../common/include/gl_boilerplate		\
		
GLBP_SRC_DIR	:= ../../common/gl_boilerplate/src
COMMON_DIR		:= ../../common

INCLUDES	:= $(addprefix -I, $(INCLUDES))
LIBS		:= $(addprefix -l, $(LIBS))
LIB_DIR		:= ../../lib/
			

IMGUI_DIR	:= ../../thirdparty/imgui
IMGUI_SRCS	:=	$(wildcard $(IMGUI_DIR)/*.cpp)

IMGUI_SRCS	+=	$(IMGUI_DIR)/backends/imgui_impl_glfw.cpp
IMGUI_SRCS	+=	$(IMGUI_DIR)/backends/imgui_impl_opengl3.cpp

IMGUI_OBJ	:=	$(IMGUI_SRCS:$(IMGUI_DIR)/backends/%.cpp=$(BUILD_DIR)%.o)
IMGUI_OBJ	:=	$(IMGUI_OBJ:$(IMGUI_DIR)/%.cpp=$(BUILD_DIR)%.o)


BUILD_DIR	:= .build

SRC_DIR		:= src
SRCS		:=				\
	shaderplayground.cpp	\
	windowstuff.cpp			\
	input.cpp				\
	openglstuff.cpp			\
	appinfo.cpp				\
	UI.cpp					\
							\
	render.cpp				\
	UniformBlockGL.cpp		\
	ShaderGL.cpp			\
							\
	myutils.cpp				\

$(info	$(IMGUI_SRCS))
IMGUI_OBJ	:=	$(IMGUI_OBJ:%.o=$(BUILD_DIR)/%.o)

#SRCS	+= $(IMGUI_SRCS:%.cpp=%.o)


OBJS		:= $(SRCS:%.cpp=$(BUILD_DIR)\\%.o)
OBJS		+= $(IMGUI_OBJ)

$(info :::OBJECTS::: )
$(info $(OBJS))
$(info --------------- )
SRCS		:= $(SRCS:%=$(SRC_DIR)\\%)

DEPS		:= $(OBJS:%.o=%.d)


#commands
RM 			:= del
AR 			:= ar
ARFLAGS 	:= -r -c -s

#flags

CXX			:= g++
CFLAGS		:= -Wall
#CFLAGS		:= -Wall -Wextra -Werror
# -g
CPPFLAGS	:= -std=c++17 -MMD -MP $(INCLUDES)
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

$(BUILD_DIR)\\%.o: $(COMMON_DIR)\\%.cpp
	if not exist $(@D) mkdir $(@D)
	$(CXX) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

$(BUILD_DIR)/%.o: $(IMGUI_DIR)/%.cpp
	if not exist $(@D) mkdir $(@D)
	$(CXX) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

$(BUILD_DIR)/%.o: $(IMGUI_DIR)/backends/%.cpp
#if not exist $(@D) mkdir $(@D)
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