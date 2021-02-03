NAME		= minishell
INC_DIR		= .
SRC_DIR		= .
CC			= gcc
SRCS		= cmd.c free_dpointer.c ft_getch.c ft_realloc.c  parse_dollar.c \
			  parse_dquote.c parse_line.c parse_squote.c parse_utils.c get_abs_path_command.c \
			  get_abs_path_command2.c minishell_utils.c ft_env.c ft_pwd.c ft_echo.c ft_cd.c ft_export.c \
			  error_handler.c free_cmd.c ft_exit.c ft_unset.c main.c executor/executor.c set_last_red_file.c \
			  signal_handler.c
OBJS		= $(SRCS:.c=.o)
LIBFT_DIR	= libft
LIBS		= -L$(LIBFT_DIR) -lft
DEBUG		= -D DEBUG
DEPS		= minishell.h executor/executor.h
CFLAGS		= -Wall -Wextra -Werror -I$(INC_DIR) -I$(LIBFT_DIR) -I executor
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
