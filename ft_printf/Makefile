NAME = libftprintf.a
SRCS = ft_printf.c  put_addr.c  put_c.c  put_hex.c  put_nb.c  put_s.c  put_unb.c input_is_valid.c
OBJS = ft_printf.o  put_addr.o  put_c.o  put_hex.o  put_nb.o  put_s.o  put_unb.o input_is_valid.o
CFLAGS = -Wall -Werror -Wextra
CC = cc

all : ${NAME}

${NAME} : ${OBJS}
	ar rcs $@ $^

clean :
	rm -f ${OBJS}

fclean : clean
	rm -f ${NAME}

re : fclean all

.PHONY: all clean fclean re

.SECONDARY: ${OBJS}