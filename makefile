NAME		:=	playground.exe
LIBS		:=				\
		glfw3				\
		glu32				\
		gdi32				\
		opengl32			\

INCLUDES	:=								\
		include/							\
		include/GL							\
		include/glfw						\
		common/include/gl_boilerplate		\
		

INCLUDES	:= $(addprefix -I, $(INCLUDES))
LIBS		:= $(addprefix -l, $(LIBS))

$(info $(LIBS))
			
BUILD_DIR	:= .build

SRC_DIR		:= src
SRCS		:=			\
	main.cpp			\
	window.cpp			\
#	shader.cpp
#glew.c

OBJS		:= $(SRCS:%.cpp=$(BUILD_DIR)\\%.o)
OBJS += $(BUILD_DIR)\glew.o
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
LDFLAGS		:= -Llib64/

#program: $(OBJECTS)
#	g++ -o build\program $(OBJECTS) -I $(INCLUDES) lib64/\
#	$(LIBS)

all: $(NAME)

test:
$(info $(OBJS))
$(info $(SRCS))


$(NAME):$(OBJS)
#	$(CXX) $(CFLAGS) $(CPPFLAGS) $(OBJS) -o $(NAME)
	$(CXX) $(CFLAGS) $(CPPFLAGS) $(OBJS) $(LDFLAGS) $(LIBS) -o $(NAME)
	$(info $(@) is ready)

$(BUILD_DIR)\\%.o: $(SRC_DIR)\\%.cpp
	if not exist $(@D) mkdir $(@D)

	$(CXX) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
	$(info $(*))

$(BUILD_DIR)\glew.o: $(SRC_DIR)\glew.c
	if not exist $(@D) mkdir $(@D)
	$(CXX) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

$(BUILD_DIR)\ShaderGL.o: common\gl_boilerplate\src\ShaderGL.cpp
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