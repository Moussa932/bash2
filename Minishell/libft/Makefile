CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -I./includes
NAME    = libft.a
SRCS    =       ft_isspace.c ft_memchr.c ft_strchr.c ft_strrchr.c \
                        ft_atoi.c ft_itoa.c ft_memcmp.c ft_strcmp.c ft_strtrim.c \
                        ft_bzero.c ft_lstadd_back.c ft_memcpy.c ft_strdup.c ft_substr.c \
                        ft_calloc.c ft_lstadd_front.c ft_memmove.c ft_striteri.c ft_tolower.c \
                        ft_free.c ft_lstclear.c ft_memset.c ft_strjoin.c ft_toupper.c \
                        ft_freetab.c ft_lstdelone.c ft_printf/ft_printf.c ft_strlcat.c get_next_line.c \
                        ft_isalnum.c ft_lstiter.c ft_putchar_fd.c ft_strlcpy.c \
                        ft_isalpha.c ft_lstlast.c ft_putendl_fd.c ft_strlen.c \
                        ft_isascii.c ft_lstmap.c ft_putnbr_fd.c ft_strmapi.c \
                        ft_isdigit.c ft_lstnew.c ft_putstr_fd.c ft_strncmp.c \
                        ft_isprint.c ft_lstsize.c ft_split.c ft_strnstr.c \
                        ft_printf/printf_putadress.c ft_printf/printf_putnbr.c ft_printf/printf_strlen.c \
                        ft_printf/printf_convertbasex.c ft_printf/printf_putchar.c ft_printf/printf_putstr.c

OBJS    = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@ar crs $(NAME) $^

./%.o: ./%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)

fclean:	clean
	@rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
