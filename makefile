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
#	shader.cpp
#glew.c

OBJS		:= $(SRCS:%.cpp=$(BUILD_DIR)\\%.o)
#OBJS += $(BUILD_DIR)\glew.o
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


$(NAME): glew $(OBJS)
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

.PHONY	: projects $(PROJECTS)