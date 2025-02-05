NAME = so_long

# Directory paths
LIBFT_DIR = libft/
GNL_DIR = gnl/
PRINTF_DIR = ft_printf/
UTILS_DIR = utils/

# Library names
LIBFT = $(LIBFT_DIR)libft.a
GNL = $(GNL_DIR)libgnl.a
PRINTF = $(PRINTF_DIR)libftprintf.a

# GNL source files
GNL_SRCS = $(GNL_DIR)get_next_line.c $(GNL_DIR)get_next_line_utils.c
GNL_OBJS = $(GNL_SRCS:.c=.o)

# Utils source files
UTILS_SRCS = $(UTILS_DIR)ft_strncpy.c
UTILS_OBJS = $(UTILS_SRCS:.c=.o)

# Source files for so_long
SRCS = main.c flood_fill.c map_checker.c map_maker.c display.c
OBJS = $(SRCS:.c=.o)

# All object files combined
ALL_OBJS = $(OBJS) $(GNL_OBJS) $(UTILS_OBJS)

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f

# Include paths for header files
INCLUDES = -I$(LIBFT_DIR) -I$(GNL_DIR) -I$(PRINTF_DIR) -I$(UTILS_DIR)

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

# Compile utils object files
$(UTILS_DIR)%.o: $(UTILS_DIR)%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Compile GNL object files
$(GNL_DIR)%.o: $(GNL_DIR)%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Compile so_long
$(NAME): libs $(GNL) $(UTILS_OBJS) $(OBJS)
	$(CC) $(ALL_OBJS) $(LIBS) -lmlx -lX11 -lXext -o $(NAME)

# Compile main object files
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(ALL_OBJS)
	@make clean -C $(LIBFT_DIR)
	@make clean -C $(PRINTF_DIR)

fclean: clean
	$(RM) $(NAME) $(GNL)
	@make fclean -C $(LIBFT_DIR)
	@make fclean -C $(PRINTF_DIR)

re: fclean all

.PHONY: all clean fclean re libs