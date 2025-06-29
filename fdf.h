#ifndef FDF_H
# define FDF_H

# include "libft/libft.h"
# include "mlx.h"
# include "math.h"
# include "fcntl.h"

# define WIDTH 1920
# define HEIGHT 1080
# define PI 3.14159265358979323846
# define COS30 0.8660254f
# define SIN30 0.5f

typedef struct s_line
{
	int	x1;
	int	x2;
	int	y1;
	int	y2;
	int	sx;
	int	sy;
	int	dx;
	int	dy;
	int	err;
	int	e2;
}	t_line;

typedef struct s_co
{
	float	raw_x;
	float	raw_y;
	float	raw_z;
	float	cx;
	float	cy;
	float	rot_x;
	float	rot_y;
	float	cos;
	float	sin;
	float	iso_x;
	float	iso_y;
}	t_co;

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int	pixel_x;
	int	pixel_y;
	int	color;
}	t_point;

typedef struct s_map
{
	int		height;
	int		width;
	float	scale;
	float	z_scale;
	float	angle;
	float	org_angle;
	float	c_angle_x;
	float	c_angle_y;
	int		pos_x;
	int		pos_y;
	int		mouse_pos_x;
	int		mouse_pos_y;
	int		org_pos_x;
	int		org_pos_y;
	int		drag_move;
	int		drag_rotate;
	t_point	***points;
}	t_map;

typedef struct s_img
{
	void	*ptr;
	char	*pixels;
	int		bpp;
	int		size_len;
	int		endian;
}	t_img;

typedef struct s_win
{
	void	*mlx;
	void	*win;
	t_img	*img;
	t_img	*b_img;
	t_map	*map;
}	t_win;

/* utils.c */
int		is_valid_point(char *str);
size_t	count_strings(char **arr);
void	*ft_check_add(void *ptr, int list_num, int error_num);
void	add_split_ptrs(char **arr, int list_num);

/* read_map.c */
t_map	*read_map(int argc, char **argv);

/* parse_map.c */
int		open_parse_map(t_map *map, char **argv, size_t line_count);

/* validate_map.c */
size_t	validate_map(int fd);

/* main.c */
int	draw_to_image(t_win *win);

#endif