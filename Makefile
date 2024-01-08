NAME = pipex
OBJ = pipex.c\
	  utils.c
CC = cc
CFLAGS = -Werror -Wextra -Wall -g3
LIBFT = libft/libft.a
SRCS = ${OBJ}

OBJS = ${SRCS:.c=.o}

.c.o :
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${OBJS}
	cc ${CFLAGS} ${OBJS} ${LIBFT} -o ${NAME} 

all: ${NAME}

clean:
	rm -f ${OBJS}

fclean: clean;
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re