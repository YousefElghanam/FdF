NAME = fdf

CC = cc

OBJ_DIR = objects/

LIBS = -lmlx -lXext -lX11 -lm

CFLAGS = -Wall -Wextra -Werror

HEADERS = fdf.h libft/libft.h

SOURCES = main_bonus.c utils.c validate_map.c read_map.c parse_map.c

BONUS = main_bonus.c

OBJECTS = $(SOURCES:%.c=$(OBJ_DIR)%.o)

LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJECTS) $(HEADERS)
	$(CC) $(OBJECTS) $(LIBFT) $(LIBS) -o $(NAME)

$(LIBFT):
	make -C libft

$(OBJ_DIR)%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf $(OBJECTS)
	make clean -C libft

fclean:
	rm -rf $(OBJECTS) $(NAME)
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re