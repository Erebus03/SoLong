NAME = so_long

# Directory paths
PRINTF_DIR = ft_printf/
UTILS_DIR = utils/

# Library names
PRINTF = $(PRINTF_DIR)libftprintf.a
UTILS = $(UTILS_DIR)libutils.a

# Utils source files
UTILS_SRCS = utils/ft_strncpy.c utils/ft_strlen.c utils/ft_strncmp.c \
				utils/get_next_line_utils.c utils/get_next_line.c
UTILS_OBJS = $(UTILS_SRCS:.c=.o)

# Source files for so_long
SRCS = main.c flood_fill.c map_checker.c map_maker.c display.c load_images.c free_images.c movement.c
OBJS = $(SRCS:.c=.o)

# All object files combined
ALL_OBJS = $(OBJS) $(UTILS_OBJS)

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f

# Include paths for header files
INCLUDES = -I$(PRINTF_DIR) -I$(UTILS_DIR)

# Library flags for linking
LIBS = -L$(PRINTF_DIR) -lftprintf -L$(UTILS_DIR) -lutils

all: $(NAME)

# Make printf
libs: $(UTILS)
	@make -C $(PRINTF_DIR)

# Create utils library
$(UTILS): $(UTILS_OBJS)
	$(AR) $(UTILS) $(UTILS_OBJS)

# Compile utils object file
$(UTILS_DIR)%.o: $(UTILS_DIR)%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Compile so_long
$(NAME): libs $(UTILS_OBJS) $(OBJS)
	$(CC) $(ALL_OBJS) $(LIBS) -lmlx -lX11 -lXext -o $(NAME)

# Compile main object files
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@


#	REMOVE THIS SHIT
testmap: libs
	cc map_maker.c map_checker.c tests/testmap.c flood_fill.c $(LIBS)  -o tests/testmap

clean:
	$(RM) $(ALL_OBJS)
	@make clean -C $(PRINTF_DIR)

fclean: clean
	$(RM) $(NAME)
	@make fclean -C $(PRINTF_DIR)

re: fclean all

.PHONY: all clean fclean re libs