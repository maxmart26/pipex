NAME = pipex
NAME_BONUS = pipex_bonus
INCLUDE = pipex.h
INCLUDE_BONUS = pipex_bonus.h
OBJ = pipex.c\
	  utils.c\
	  utils_2.c
OBJ_BONUS = pipex_bonus.c\
			 utils_bonus.c\
			 utils_bonus2.c\
			 here_doc.c\
			 pipex_bonus_solo.c\
			 multi_pipe.c
CC = cc
CFLAGS = -Wall -Werror -Wextra -g3
LIBFT = libft/libft.a
SRCS = ${OBJ}
SRCS_BONUS = ${OBJ_BONUS}
OBJS = ${SRCS:.c=.o}
OBJS_BONUS = ${SRCS_BONUS:.c=.o}

%.o:%.c ${INCLUDE}
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${SRCS}
	make ${OBJS}
	cc ${CFLAGS} ${OBJS} ${LIBFT} -o ${NAME} 

all: ${NAME}

clean:
	rm -f ${OBJS} ${OBJS_BONUS}

fclean: clean;
	rm -f ${NAME} ${NAME_BONUS}

re: fclean all

bonus: ${OBJS_BONUS} ${INCLUDE_BONUS}
	cc ${CFLAGS} ${OBJS_BONUS} ${LIBFT} -o ${NAME_BONUS}

.PHONY: all clean fclean re