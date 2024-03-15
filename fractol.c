/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 07:33:45 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/03/15 07:01:56 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx/mlx.h"
#include <stdlib.h>

static void	setup_window(t_screen *window)
{
	window->mlx_ptr = mlx_init();
	if (!window->mlx_ptr)
		error_occur(2, window);
	window->win_ptr = mlx_new_window(window->mlx_ptr, WIDTH, HEIGHT,
			window->fract_name);
	if (!window->win_ptr)
		error_occur(2, window);
	window->img_ptr = mlx_new_image(window->mlx_ptr, WIDTH, HEIGHT);
	if (!window->img_ptr)
		error_occur(2, window);
	window->img_addr = mlx_get_data_addr(window->img_ptr,
			&(window->bits_per_pixel), &(window->size_line), &(window->endian));
	if (!window->img_addr)
		error_occur(2, window);
}

static int	init_fract(t_screen *window, const char *av[])
{
	t_set	*fract;

	fract = (t_set *)malloc(sizeof(t_set));
	if (!fract)
		return (0);
	if (!ft_strcmp("julia", window->fract_name))
	{
		fract->c.re = atoi_point(av[2]);
		fract->c.im = atoi_point(av[3]);
	}
	fract->min_re = -2;
	fract->max_re = 2;
	fract->max_im = 2;
	fract->min_im = -2;
	fract->iteration = -1;
	fract->zoom_factor = 1;
	fract->color_code = 0;
	window->set = fract;
	return (1);
}

int	main(int argc, const char **argv)
{
	t_screen	window;

	if (argc < 2)
		return (1);
	check_point(argc, argv + 1);
	window.fract_name = ft_strdup(argv[1]);
	window.motion = 0;
	if (!window.fract_name)
		return (1);
	if (!init_fract(&window, argv))
		return (free(window.fract_name), 1);
	setup_window(&window);
	draw_fract(&window);
	mlx_put_image_to_window(window.mlx_ptr, window.win_ptr, window.img_ptr, 0,
		0);
	hook_event(&window);
	mlx_loop(window.mlx_ptr);
	return (0);
}
