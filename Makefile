NAME = so_long

SRCS = main.c flood_fill.c map_checker.c map_maker.c display.c \
       load_images.c movement.c score_output.c \
       utils/ft_strncpy.c utils/ft_strlen.c utils/ft_strncmp.c \
       utils/get_next_line_utils.c utils/get_next_line.c \
       utils/ft_printf.c utils/ft_strrchr.c utils/ft_itoa.c utils/ft_strjoin.c

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

INCLUDES = -Iutils/

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -lmlx -lX11 -lXext -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re