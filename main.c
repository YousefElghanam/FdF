#include "fdf.h"

int	key_win(int key, t_win *win)
{
	ft_printf("key (%d) was pressed\n", key);
	if (key==65307)
	{
		mlx_cleaqr_window(win->mlx, win->win);
		mlx_destroy_window(win->mlx, win->win);
		return_error(1);
	}
	return(0);
}

int	mouse_win(int button, int x, int y)
{
	ft_printf("(%d) key_clicked at %dx%d\n", button, x, y);
	return(0);
}

int	expose_win()
{
	ft_printf("hihihihi\n");
	return(0);
}

int main(void)
{
	void	*mlx_ptr;
	t_win	*win1;

	if(!ft_alloc_list())
		return_error(1);
	mlx_ptr = mlx_init();
	if (!mlx_ptr)
		return_error(1);

	win1 = ft_malloc(sizeof(t_win));
	win1->win = mlx_new_window(mlx_ptr, 800, 600, "Hi, FdF");
	win1->mlx = mlx_ptr;

	mlx_expose_hook(win1->win, expose_win, NULL);
	mlx_mouse_hook(win1->win, mouse_win, NULL);
	mlx_key_hook(win1->win, key_win, win1);
	mlx_loop(mlx_ptr);
}