NAME = so_long

# Library paths
LIBFT_DIR = libft/
GNL_DIR = gnl/
PRINTF_DIR = ft_printf/

# Library names
LIBFT = $(LIBFT_DIR)libft.a
GNL = $(GNL_DIR)libgnl.a
PRINTF = $(PRINTF_DIR)libftprintf.a

# GNL source files
GNL_SRCS = $(GNL_DIR)get_next_line.c $(GNL_DIR)get_next_line_utils.c
GNL_OBJS = $(GNL_SRCS:.c=.o)

# Source files for so_long
SRCS = main.c flood_fill.c map_checker.c map_maker.c
OBJS = $(SRCS:.c=.o)

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f

# Include paths for header files
INCLUDES = -I$(LIBFT_DIR) -I$(GNL_DIR) -I$(PRINTF_DIR)

# Library flags for linking
LIBS = -L$(LIBFT_DIR) -lft -L$(GNL_DIR) -lgnl -L$(PRINTF_DIR) -lftprintf

all: $(NAME)

# Make libft and printf
libs:
	@make -C $(LIBFT_DIR)
	@make -C $(PRINTF_DIR)

# Create GNL library
$(GNL): $(GNL_OBJS)
	$(AR) $(GNL) $(GNL_OBJS)

# Compile GNL object files
$(GNL_DIR)%.o: $(GNL_DIR)%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Compile so_long
$(NAME): libs $(GNL) $(OBJS)
	$(CC) $(OBJS) $(LIBS) -o $(NAME)

# Compile object files
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJS) $(GNL_OBJS)
	@make clean -C $(LIBFT_DIR)
	@make clean -C $(PRINTF_DIR)

fclean: clean
	$(RM) $(NAME) $(GNL)
	@make fclean -C $(LIBFT_DIR)
	@make fclean -C $(PRINTF_DIR)

re: fclean all

.PHONY: all clean fclean re libs

#all:
#	cc map_maker.c map_checker.c flood_fill.c main.c gnl/get_next_line.c gnl/get_next_line_utils.c
#libft:
#	make ; make clean