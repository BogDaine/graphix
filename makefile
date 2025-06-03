NAME		:=	main.exe
LIBS		:=				\
		glew				\
		glfw3				\
		glu32				\
		gdi32				\
		opengl32			\

INCLUDES	:=								\
		include/							\
		include/GL							\
		include/glfw						\
		common/include/gl_boilerplate		\
		
PROJECTS	:=								\
		shaderplayground					\

INCLUDES	:= $(addprefix -I, $(INCLUDES))
LIBS		:= $(addprefix -l, $(LIBS))
PROJECTS	:= $(addprefix projects\, $(PROJECTS))

#$(info $(PROJECTS))
#$(info $(LIBS))
			
BUILD_DIR	:= .build
LIB_DIR		:= lib/
SRC_DIR		:= src
SRCS		:=			\
	main.cpp			\
	window.cpp			\

IMGUI_DIR	:= thirdparty\\imgui
IMGUI_SRCS	:=	$(wildcard $(IMGUI_DIR)/*.cpp)
IMGUI_SRCS	+=	$(IMGUI_DIR)\\backends\\imgui_impl_glfw.cpp
IMGUI_SRCS	+=	$(IMGUI_DIR)\\backends\\imgui_impl_opengl3.cpp
#IMGUI_SRCS	+=	$(IMGUI_DIR)\\backends\\imgui_impl_win32.cpp

IMGUI_OBJ	:=	$(IMGUI_SRCS:%.cpp=$(BUILD_DIR)\\%.o)

$(info $(IMGUI_SRCS))
$(info $(IMGUI_OBJ))

OBJS		:= $(SRCS:%.cpp=$(BUILD_DIR)\\%.o)

OBJS += $(BUILD_DIR)\ShaderGL.o

$(info $(OBJS))

SRCS		:= $(SRCS:%=$(SRC_DIR)\\%)
SRCS += 	common\gl_boilerplate\src\ShaderGL.cpp

DEPS		:= $(OBJS:%.o=%.d)


#commands
RM 			:= del
#DIR_DUP		:= mkdir -p
AR 			:= ar
ARFLAGS 	:= -r -c -s
#libs are archives of objects :)

CXX			:= g++
CFLAGS		:= 
#CFLAGS		:= -Wall -Wextra -Werror
CPPFLAGS	:= -MMD -MP $(INCLUDES)
CPPFLAGS += -DGLEW_STATIC
#-DGLEW_STATIC
LDFLAGS		:= -L$(LIB_DIR)

#program: $(OBJECTS)
#	g++ -o build\program $(OBJECTS) -I $(INCLUDES) lib64/\
#	$(LIBS)

all: $(NAME) projects

test:
$(info $(OBJS))
$(info $(SRCS))


$(NAME): glew imgui_glfw $(OBJS)
#	$(CXX) $(CFLAGS) $(CPPFLAGS) $(OBJS) -o $(NAME)
	$(CXX) $(CFLAGS) $(CPPFLAGS) $(OBJS) $(LDFLAGS) $(LIBS) -o $(NAME)
	$(info $(@) is ready)

$(BUILD_DIR)\\%.o: $(SRC_DIR)\\%.cpp
	if not exist $(@D) mkdir $(@D)

	$(CXX) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
	$(info $(*))


$(BUILD_DIR)\ShaderGL.o: common\gl_boilerplate\src\ShaderGL.cpp
	if not exist $(@D) mkdir $(@D)
	$(CXX) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

projects		:	$(PROJECTS)
#	for dir in $(PROJECTS) do echo yes echo yes
$(PROJECTS)		:
	$(MAKE)	-C $@


glew			:		$(BUILD_DIR)\glew.o
	$(AR) $(ARFLAGS)  -o $(LIB_DIR)lib$@.a $(BUILD_DIR)\glew.o


$(BUILD_DIR)\glew.o: $(SRC_DIR)\glew.c
	if not exist $(@D) mkdir $(@D)
	$(CXX) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

imgui_glfw	:		$(IMGUI_OBJ)
	$(AR) $(ARFLAGS)  -o $(LIB_DIR)lib$@.a $<

$(IMGUI_OBJ)	:		$(IMGUI_SRCS)
	if not exist $(@D) mkdir $(@D)
	$(CXX) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

-include $(DEPS)

clean:
	$(RM) $(OBJS) $(DEPS)
	$(info $(DEPS))
	$(info cleaning...)

clean_projects:

fclean: clean
	$(RM) $(NAME)
re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY	: projects $(PROJECTS)