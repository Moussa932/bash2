CC      = gcc -g3
CFLAGS  = -Wall -Wextra -Werror -MMD -I./includes -I./libft/includes -I./parser -I./builtins -I./redirection -I./execution -I./signals
NAME    = minishell
SRCS    = builtins/export_utils.c builtins/ft_cd.c builtins/ft_echo.c builtins/ft_env.c \
            builtins/ft_exit.c builtins/ft_export.c builtins/ft_pwd.c builtins/ft_unset.c \
            clean/exit_shell.c clean/free.c \
            execution/exec.c execution/exec2.c execution/path_cmd.c \
            parser/expanser_utils.c parser/expanser_utils2.c parser/expanser.c parser/expanser2.c \
            parser/lexer_utils.c parser/lexer.c parser/quote.c \
            redirection/command_utils.c redirection/command.c redirection/heredoc.c \
            signals/signal.c signals/signal2.c main.c
OBJS	= $(SRCS:.c=.o) 
LIBFT	= libft/libft.a
VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=ignore.txt
DEPEND = $(OBJS:.o=.d)

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

${NAME}: ${LIBFT} ${OBJS}  # Ajout de ${LIBFT} comme dépendance
	${CC} ${CFLAGS} ${OBJS} -o ${NAME} ${LIBFT} -lreadline

${LIBFT}:
	make -C libft

all:	${NAME} 

-include	$(DEPEND)

clean:
	rm -f ${OBJS} ${DEPEND}
	make -C libft clean

fclean: clean
	rm -f ${NAME}
	make -C libft fclean

re:	fclean all

valgrind: ${NAME}
	valgrind $(VALGRIND_FLAGS) ./${NAME}

.PHONY:	all clean fclean re valgrind
