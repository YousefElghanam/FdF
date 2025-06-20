#include "libft.h"
#include "mlx.h"
#include "math.h"

#define WIDTH 1600
#define HEIGHT 900

typedef struct s_map
{
	int		num;
	char	*name;
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
}	t_win;
