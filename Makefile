
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
HOSTLIB		= libft_malloc.so
NAME		= libft_malloc_$(HOSTTYPE).so

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
LINK_TXT		= printf "$(CYAN)=== Linking lib_malloc ===\n$(RESET)"
END_TXT			= printf "$(GREEN)=== lib_malloc Compilated ===\n$(RESET)"
LINK_END_TXT	= printf "$(GREEN)=== lib_malloc have been linked ===\n$(RESET)"
CHARG_LINE_TXT	= printf "$(GREEN)█$(RESET)"
CLEAN_TXT		= printf "$(RED) Deleting all files\n$(RESET)"
FCLEAN_TXT		= printf "$(RED) Deleting $(NAME)\n$(RESET)"
NL_TXT			= printf "\n"

# RULES
all:		art tmp start $(NAME) link

start:
			@$(START_TXT)

art:
			@tput setaf 2; cat doc/ascii_art/project; tput sgr0
			@tput setaf 2; cat doc/ascii_art/name; tput sgr0


$(NAME):	$(OBJS)
			@$(NL_TXT)
			@$(CC) $(FLAGS_SHARED) $(OBJS) -o $(NAME)
			@$(END_TXT)

link:
			@$(LINK_TXT)
			ln -sf $(NAME) $(HOSTLIB)
			@$(LINK_END_TXT)

tmp:
			@/bin/mkdir -p objs

$(OBJS_PATH)/%.o:	$(SRCS_PATH)/%.c 
					@/bin/mkdir -p $(@D)
					@$(CC) $(FLAGS) $(FLAGS_LIB) $(INC_PATH) -c $< -o $@
					@$(CHARG_LINE_TXT)

clean:
			@$(CLEAN_TXT)
			@tput setaf 1; cat doc/ascii_art/trash; tput sgr0
			@rm -rf test
			@rm -rf test1
			@rm -rf test2
			@rm -rf test3
			@rm -rf test4
			@rm -rf test5
			@rm -rf $(OBJS_PATH)

fclean:		clean
			@$(FCLEAN_TXT)
			@rm -rf $(NAME) $(HOSTLIB) $(TEST_N)
			@$(NL_TXT)

re:			fclean all

rt:			fclean all test t

test:
			cp test_folder/test.c test.c
			gcc -o test test.c -L. -lft_malloc && ./run_linux.sh ./test
			@rm test.c test

test0:
			cp test_folder/test0.c test0.c
			gcc -o test0 test0.c && ./run_linux.sh /usr/bin/time -v ./test0
			@rm test0.c test0

test1:
			cp test_folder/test1.c test1.c
			gcc -o test1 test1.c && /usr/bin/time -v ./test1
			./run_linux.sh /usr/bin/time -v ./test1
			@rm test1.c test1

test2:
			cp test_folder/test2.c test2.c
			gcc -o test2 test2.c && ./run_linux.sh /usr/bin/time -v ./test2
			@rm test2.c test2

test3:
			cp test_folder/test3.c test3.c
			gcc -o test3 test3.c -L. -lft_malloc && ./run_linux.sh ./test3
			@rm test3.c test3

test4:
			cp test_folder/test4.c test4.c
			gcc -o test4 test4.c -L. -lft_malloc && ./run_linux.sh ./test4
			@rm test4.c test4

test5:
			cp test_folder/test5.c test5.c
			gcc -o test5 test5.c -L. -lft_malloc && ./run_linux.sh ./test5
			@rm test5.c test5

.PHONY:		clean fclean tmp re all test test0 test1 test2 link
