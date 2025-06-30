NAME = fdf

NAME_BONUS = fdf_bonus

CC = cc

OBJ_DIR = objects/

OBJ_DIR_BONUS = objects_bonus/

LIBS = -lmlx -lXext -lX11 -lm

CFLAGS = -Wall -Wextra -Werror

HEADERS = fdf.h fdf_bonus.h libft/libft.h

SOURCES = parse_utils.c validate_map.c read_map.c parse_map.c draw_map.c draw_utils.c \
			main.c hooks.c draw.c

BONUS_SOURCES = parse_utils.c validate_map.c read_map.c parse_map.c draw_map.c draw_utils.c \
			main_bonus.c hooks_bonus.c draw_bonus.c

OBJECTS = $(SOURCES:%.c=$(OBJ_DIR)%.o)

OBJECTS_BONUS = $(BONUS_SOURCES:%.c=$(OBJ_DIR_BONUS)%.o)

LIBFT = libft/libft.a

all: $(NAME) $(NAME_BONUS)

$(NAME): $(LIBFT) $(OBJECTS)
	$(CC) $(OBJECTS) $(LIBFT) $(LIBS) -o $(NAME)

$(LIBFT):
	make -C libft

$(OBJ_DIR)%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ_DIR):
	mkdir -p $@

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(LIBFT) $(OBJECTS_BONUS)
	$(CC) $(OBJECTS_BONUS) $(LIBFT) $(LIBS) -o $(NAME_BONUS)

$(OBJ_DIR_BONUS)%.o: %.c | $(OBJ_DIR_BONUS)
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ_DIR_BONUS):
	mkdir -p $@

clean:
	rm -rf $(OBJ_DIR) $(OBJ_DIR_BONUS)
	make clean -C libft

fclean:
	rm -rf $(OBJ_DIR) $(OBJ_DIR_BONUS) $(NAME) $(NAME_BONUS)
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re