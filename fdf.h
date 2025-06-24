#include "libft/libft.h"
#include "mlx.h"
#include "math.h"
#include "fcntl.h"

#define WIDTH 1920
#define HEIGHT 1080

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int	color;
}	t_point;

typedef struct s_map
{
	int		height;
	int		width;
	t_point	***points;
}	t_map;

typedef struct s_img
{
	char	*pixels;
	int		bpp;
	int		size_len;
	int		endian;
}	t_img;

typedef struct s_win
{
	void	*mlx;
	void	*win;
	void	*img;
	t_map	*map;
}	t_win;

/* utils.c */
int		is_valid_point(char *str);
size_t	count_strings(char **arr);
void	*check_add_ptr(void *ptr, int list_num, int error_num);
void	add_split_ptrs(char **arr, int list_num);

/* read_map.c */
t_map	*read_map(int argc, char **argv);

/* parse_map.c */
int		open_parse_map(t_map *map, char **argv, size_t line_count);

/* validate_map.c */
size_t	validate_map(int fd);
