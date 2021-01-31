NAME	   = libft.a

INC_DIR	   = .

SRCS	   = ${wildcard *.c} 

OBJS	   = ${SRCS:.c=.o}

DEPS	   = libft.h

CFLAGS	   = -Wall -Wextra -Werror -I${INC_DIR}

AR	   = ar rc

.c.o :		${DEPS}
		gcc ${CFLAGS} -c $< -o ${<:.c=.o}

all:		${NAME}

$(NAME):	${OBJS}
		${AR} ${NAME} $?

clean:		
		rm -f ${OBJS}

fclean:		clean
		rm -f ${NAME}

re:		fclean all

.PHONY:		all clean fclean re
