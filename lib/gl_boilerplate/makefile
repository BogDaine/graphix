NAME 		:= libbreakfast.a
CXX 		:= g++


#preprocessor flags
CPPFLAGS	:= -MMD -MP -I include
ARFLAGS 	:= -r -c -s

#compiler flags
CFLAGS 		:= -Wall -Wextra -Werror


LDFLAGS		:=



SRC_DIR 		:= src
BUILD_DIR		:= .build
SRCS 			:=			\
		 kitchen\table.cpp	\
		 kitchen\chair.cpp	\
		 food\bread.cpp		\
		 food\egg.cpp

SRCS			:= $(SRCS:%=$(SRC_DIR)\\%)
#$(info $(SRCS))
#$(info $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o))
OBJS := $(SRCS:$(SRC_DIR)\\%.cpp=$(BUILD_DIR)\\%.o)
DEPS := $(OBJS:.o=.d)
$(INFO $(DEPS))
#$(info $(OBJS))

#commands
RM 			:= del
#DIR_DUP		:= mkdir -p
AR 			:= ar
#libs are archives of objects :)

all: $(NAME)

$(NAME):$(OBJS)
#@echo "Breakfast is ready!"
#	$(CXX) $(CFLAGS) $(CPPFLAGS) $(OBJS) -o $(NAME)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)
	$(info $(@) is ready)

$(BUILD_DIR)\\%.o: $(SRC_DIR)\\%.cpp
	if not exist $(@D) mkdir $(@D)
#"mkdir" $(@D)
#pentru gnu mkdir, dar trebuie sa fie in variabile cred//??
#	$(info subdir is $(@D))
#	$(info mkdir -p $(@D))
	$(CXX) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
#	$(CXX) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
	$(info $(*))
#	$(info created $(@))

.PHONY: clean fclean re

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