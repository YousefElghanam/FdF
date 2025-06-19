NAME = fdf

CC = cc

INCLUDE = -I./minilibx-linux -I./libft

LIBS = -L./minilibx-linux -lmlx -lXext -lX11 -lm

CFLAGS = -Wall -Wextra -Werror -g $(INCLUDE)

HEADERS = fdf.h libft/libft.h

SOURCES = main.c

OBJECTS = $(SOURCES:.c=.o)

LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -g $(SOURCES) $(LIBFT) -o $(NAME) $(LIBS)

$(LIBFT):
	make -C libft
	make clean -C libft

clean:
	rm -rf $(OBJECTS)
	make clean -C libft

fclean:
	rm -rf $(OBJECTS) $(NAME)
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re