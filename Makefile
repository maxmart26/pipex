NAME = pipex
OBJ = pipex.c\
	  utils.c
OBJ_BONUS = pipex_bonus.c\
			 utils_bonus.c\
			 utils_bonus2.c
CC = cc
CFLAGS = -Wall -Werror -Wextra -g3
LIBFT = libft/libft.a
SRCS = ${OBJ}
SRCS_BONUS = ${OBJ_BONUS}
OBJS = ${SRCS:.c=.o}
OBJS_BONUS = ${SRCS_BONUS:.c=.o}

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

bonus: ${OBJS_BONUS}
	cc ${CFLAGS} ${OBJS_BONUS} ${LIBFT} -o ${NAME}

.PHONY: all clean fclean re