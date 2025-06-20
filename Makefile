NAME = fdf

CC = cc

OBJ_DIR = objects/

INCLUDE = -I./minilibx-linux -I./libft

LIBS = -L./minilibx-linux -lmlx -lXext -lX11 -lm

CFLAGS = -Wall -Wextra -Werror -g $(INCLUDE)

HEADERS = fdf.h libft/libft.h

SOURCES = main.c utils.c

OBJECTS = $(SOURCES:%.c=$(OBJ_DIR)%.o)

LIBFT = libft/libft.a

all: $(NAME)
	./fdf

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