NAME		= minishell
INC_DIR		= executor
SRC_DIR		= .
CC			= gcc
SRCS		= $(wildcard *.c)
SRCS		+= ./executor/executor.c
OBJS		= $(SRCS:.c=.o)
LIBFT_DIR	= libft
LIBS		= -L$(LIBFT_DIR) -lft
DEBUG		= -D DEBUG
DEPS		= minishell.h ./executor/executor.h
CFLAGS		= -Wall -Wextra -Werror -I$(INC_DIR) -I$(LIBFT_DIR) -I.
SMAKE		= make -s

%.o:		%.c $(DEPS)
			$(CC) $(CFLAGS) -c $< -o $@

all:		$(NAME)

libft:
			make -C $(LIBFT_DIR)

$(NAME):	$(OBJS)
			$(SMAKE) libft
			$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

test:		CFLAGS += $(DEBUG)
test:		$(NAME)
			./$(NAME) 

clean:
			rm -rf $(OBJS)
			$(SMAKE) clean -C $(LIBFT_DIR)

fclean:		clean
			rm -rf $(NAME)
			$(SMAKE) fclean -C $(LIBFT_DIR)

re:			fclean all

.PHONY:		all clean fclean re libft
