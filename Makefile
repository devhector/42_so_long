SRC = src
OBJ_PATH = obj
LIBFT_PATH = libft
LIB_PATH = lib

NAME = so_long
LIBFT = $(LIBFT_PATH)/libft.a
SO_LONG = $(SRC)/so_long.c
HEADER = $(LIB_PATH)/so_long.h
HEADER_GNL = $(LIB_PATH)/get_next_line.h

CC = @clang
RM = @rm -rf
FLAGS = -Wall -Wextra -Werror -g
MLXFLAGS = -lX11 -lmlx -lXext -lm

FUNCS = img_creator.c key_hooks.c map_generator.c map_printer.c\
		map_validator_utils.c map_validator.c move.c get_next_line.c

SRCS = $(addprefix $(SRC)/, $(FUNCS))

OBJS = $(SRCS:$(SRC)/%.c=$(OBJ_PATH)/%.o)

all: $(NAME)

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)

$(LIBFT):
	$(MAKE) -C $(LIBFT_PATH) bonus

$(OBJ_PATH)/%.o: $(SRC)/%.c $(HEADER) $(HEADER_GNL)
	@echo "Compiling $(<)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(LIBFT) $(OBJ_PATH) $(OBJS) $(SO_LONG)
	$(CC) $(FLAGS) $(OBJS) $(SO_LONG) -o $(NAME) $(LIBFT) $(MLXFLAGS)

clean:
	@echo "Cleaning so_long"
	$(MAKE) -C $(LIBFT_PATH) clean
	$(RM) $(OBJ_PATH)

fclean:	clean
	@echo "Cleaning so_long header"
	$(MAKE) -C $(LIBFT_PATH) fclean
	$(RM) $(NAME)

re: fclean all

.PHONY:	all re clean fclean