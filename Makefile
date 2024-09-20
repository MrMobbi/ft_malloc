
# HOST
ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

# COMPILATION
CC			= gcc
FLAGS		= -Wall -Werror -Wextra -g
LNFLAGS		= -shared
FLAGS_DEBUG	= -fsanitize=address

# EXECUTABLE
NAME		= libft_malloc.so
HOSTLIB		= libft_malloc_$(HOSTTYPE).so
TEST_N		= malloc_test

# PATH
SRCS_PATH	= srcs
OBJS_PATH	= objs
INC_PATH	= -I incl

	### SOURCES FILES ###
SRCS		= malloc.c

TEST_FILES	= malloc.c \
			  main.c \
			  utils.c \

			  # OBJECT FILES

OBJS		= $(addprefix $(OBJS_PATH)/, $(SRCS:.c=.o))

SRCS_TEST	= $(addprefix $(SRCS_PATH)/ $(TEST_FILES))
OBJS_TEST	= $(addprefix $(OBJS_PATH)/, $(TEST_FILES:.c=.o))

# COLORS
RED			= \033[1;31m
GREEN		= \033[1;32m
CYAN		= \033[1;36m
RESET		= \033[0m

# TEXTES
START_TXT		= echo "$(CYAN)=== Compiling lib_malloc ===$(RESET)"
END_TXT			= echo "$(GREEN)=== lib_malloc Compilated ===$(RESET)"
CHARG_LINE_TXT	= echo "$(GREEN)█$(RESET)\c"
CLEAN_TXT		= echo "$(RED) Deleting all files$(RESET)"
FCLEAN_TXT		= echo "$(RED) Deleting $(NAME)$(RESET)"
NL_TXT			= echo ""

# RULES
all:		art tmp $(NAME)

art:
			@echo "TODO art"
			@#tput setaf 2; cat .ascii_art/name; tput setaf default

t:		tmp $(TEST_N)

$(TEST_N):	$(OBJS_TEST)
			$(CC) $(FLAGS_DEBUG) $(FLAGS) -o $@ $(OBJS_TEST)

$(NAME):	$(HOSTLIB)
			@ln -fs $(HOSTLIB) $(NAME)
			@$(NL_TXT)
			@$(END_TXT)

$(HOSTLIB):	$(OBJS) $(DEP)
			$(CC) $(LNFLAGS) $(INCL) -o $@ $(OBJS)

tmp:
			@/bin/mkdir -p objs

$(OBJS_PATH)/%.o:	$(SRCS_PATH)/%.c 
					@/bin/mkdir -p $(@D)
					@$(CC) $(FLAGS) $(FLAGS_DEBUG) $(INC_PATH) -c $< -o $@
					@$(CHARG_LINE_TXT)

clean:
			@$(CLEAN_TXT)
			@echo "TODO clean art"
			@rm -rf $(OBJS_PATH)

fclean:		clean
			@$(FCLEAN_TXT)
			@rm -rf $(NAME) $(HOSTLIB) $(TEST_N)
			@echo "TODO fclean art"
			@$(NL_TXT)

re:			fclean all

rt:			fclean t

tests:
			@# Ensures that the exit status of the command is always considered successful
			@echo "TODO tests"

.PHONY:		clean fclean tmp re all tests
