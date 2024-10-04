
# HOST
ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

# COMPILATION
CC				= gcc 
FLAGS			= -Wall -Werror -Wextra
FLAGS_LIB		= -fpic -fPIC
FLAGS_SHARED	= -shared
FLAGS_DEBUG		= -g -fsanitize=address

# EXECUTABLE
NAME		= libft_malloc.so
HOSTLIB		= libft_malloc_$(HOSTTYPE).so

# PATH
SRCS_PATH	= srcs
OBJS_PATH	= objs
INC_PATH	= -I incl

	### SOURCES FILES ###
FILES		= malloc.c \
			  utils.c \
			  utils_malloc.c \
			  utils_free.c \
			  utils_realloc.c \
			  show_mem.c \
			  ft_new_chunk.c \
			  ft_printf.c \

			  # OBJECT FILES

SRCS		= $(addprefix $(SRCS_PATH)/, $(FILES))
OBJS		= $(addprefix $(OBJS_PATH)/, $(FILES:.c=.o))

# COLORS
RED			= \033[1;31m
GREEN		= \033[1;32m
CYAN		= \033[1;36m
RESET		= \033[0m

# TEXTES
START_TXT		= printf "$(CYAN)=== Compiling lib_malloc ===\n$(RESET)"
END_TXT			= printf "$(GREEN)=== lib_malloc Compilated ===\n$(RESET)"
CHARG_LINE_TXT	= printf "$(GREEN)█$(RESET)"
CLEAN_TXT		= printf "$(RED) Deleting all files\n$(RESET)"
FCLEAN_TXT		= printf "$(RED) Deleting $(NAME)\n$(RESET)"
NL_TXT			= printf "\n"

# RULES
all:		art tmp $(NAME) link

art:
			@echo "TODO art"
			@#tput setaf 2; cat .ascii_art/name; tput setaf default


$(NAME):	$(OBJS)
			@$(CC) $(FLAGS_SHARED) $(OBJS) -o $(NAME) 

link:
			@ln -sf $(NAME) $(HOSTLIB)

tmp:
			@/bin/mkdir -p objs

$(OBJS_PATH)/%.o:	$(SRCS_PATH)/%.c 
					@/bin/mkdir -p $(@D)
					@$(CC) $(FLAGS) $(FLAGS_LIB) $(INC_PATH) -c $< -o $@
					@$(CHARG_LINE_TXT)

clean:
			@$(CLEAN_TXT)
			@echo "TODO clean art"
			@rm -rf $(OBJS_PATH)

fclean:		clean
			@$(FCLEAN_TXT)
			@rm -rf $(NAME) $(HOSTLIB) $(TEST_N)
			@rm -rf test
			@echo "TODO fclean art"
			@$(NL_TXT)

re:			fclean all

rt:			fclean all test t

test:
			$(CC) $(FLAGS) -o test test.c -L. -lft_malloc -I./incl

t:
			LD_LIBRARY_PATH=. ./test

.PHONY:		clean fclean tmp re all test link
