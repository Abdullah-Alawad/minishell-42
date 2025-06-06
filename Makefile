NAME = minishell

CC = cc
CFLAGS = -Wall -Werror -Wextra

RM = rm -f

SRC_DIR = srcs
OBJ_DIR = objs

SRCS = ${SRC_DIR}/main.c ${SRC_DIR}/lexer.c ${SRC_DIR}/lexing_utils.c ${SRC_DIR}/quotes.c \
		${SRC_DIR}/frees.c ${SRC_DIR}/lexing_utils2.c ${SRC_DIR}/env.c ${SRC_DIR}/parse.c \
		${SRC_DIR}/parse_utils.c ${SRC_DIR}/expander.c ${SRC_DIR}/expand_utils.c ${SRC_DIR}/expand_dollar.c \
		${SRC_DIR}/execution.c ${SRC_DIR}/exit.c ${SRC_DIR}/cd.c  ${SRC_DIR}/cd_utils.c \
		${SRC_DIR}/env_command.c ${SRC_DIR}/export.c ${SRC_DIR}/export_utils.c ${SRC_DIR}/unset.c \
		${SRC_DIR}/echo.c ${SRC_DIR}/externals.c ${SRC_DIR}/externals_utils.c ${SRC_DIR}/externals_utils2.c \
		${SRC_DIR}/lexing_utils3.c ${SRC_DIR}/redirections.c ${SRC_DIR}/redirections2.c ${SRC_DIR}/pwd.c \
		${SRC_DIR}/execution_utils.c ${SRC_DIR}/lexing_utils4.c ${SRC_DIR}/env_utils.c ${SRC_DIR}/parse_utils2.c \
		${SRC_DIR}/export_utils2.c ${SRC_DIR}/frees2.c ${SRC_DIR}/expand_utils2.c

OBJS = ${SRCS:${SRC_DIR}/%.c=${OBJ_DIR}/%.o}

${OBJ_DIR}/%.o: ${SRC_DIR}/%.c minishell.h
	@mkdir -p ${dir $@}
	${CC} ${CFLAGS} -g -c $< -o $@

all: libft ${NAME}

libft:
	make -C libft

${NAME}: ${OBJS}
		${CC} ${CFLAGS} ${MAIN_OBJ} ${OBJS} -g -Llibft -lft -lreadline -o ${NAME}

clean:
		${RM} ${OBJS}
		rm -rf ${OBJ_DIR}
		make -C libft fclean

fclean: clean
		${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re libft
