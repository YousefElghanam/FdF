#include "libft/libft.h"
#include "minilibx-linux/mlx.h"

typedef struct s_map
{
	int		num;
	char	*name;
}	t_map;

typedef struct s_win
{
	void	*mlx;
	void	*win;
}	t_win;