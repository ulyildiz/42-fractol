/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 07:33:29 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/03/15 07:29:17 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx/mlx.h"

static void	image_shifting(int keycode, t_screen *window)
{
	if (keycode == UP)
	{
		window->set->max_im -= 0.6 * window->set->zoom_factor;
		window->set->min_im -= 0.6 * window->set->zoom_factor;
	}
	else if (keycode == DOWN)
	{
		window->set->max_im += 0.6 * window->set->zoom_factor;
		window->set->min_im += 0.6 * window->set->zoom_factor;
	}
	else if (keycode == RIGHT)
	{
		window->set->max_re -= 0.6 * window->set->zoom_factor;
		window->set->min_re -= 0.6 * window->set->zoom_factor;
	}
	else if (keycode == LEFT)
	{
		window->set->min_re += 0.6 * window->set->zoom_factor;
		window->set->max_re += 0.6 * window->set->zoom_factor;
	}
}

static int	key_event(int keycode, t_screen *window)
{
	if (keycode == ESC)
		free_all(window);
	else if (keycode == UP || keycode == LEFT || keycode == RIGHT
		|| keycode == DOWN)
		image_shifting(keycode, window);
	else if (keycode == ENTER)
	{
		window->set->color_code++;
		if (window->set->color_code == 4)
			window->set->color_code = 0;
	}
	else if (keycode == R_OPTION)
		window->motion = !window->motion;
	draw_fract(window);
	mlx_put_image_to_window(window->mlx_ptr, window->win_ptr, window->img_ptr,
		0, 0);
	return (0);
}

static int	closing(t_screen *window)
{
	free_all(window);
	return (0);
}

static int	mouse_event(int keycode, int x, int y, t_screen *window)
{
	x = y;
	if (keycode == SCROLL_UP)
		window->set->zoom_factor *= 0.9;
	else if (keycode == SCROLL_DOWN)
		window->set->zoom_factor *= 1.1;
	draw_fract(window);
	mlx_put_image_to_window(window->mlx_ptr, window->win_ptr, window->img_ptr,
		0, 0);
	return (0);
}

static int	motion_event(int x, int y, t_screen *window)
{
	if (window->fract_name[0] == 'j' && window->motion)
	{
		window->set->c.re = (window->set->min_re + (window->set->max_re
					- window->set->min_re) * x / WIDTH);
		window->set->c.im = (window->set->min_im + (window->set->max_im
					- window->set->min_im) * y / HEIGHT);
		draw_fract(window);
		mlx_put_image_to_window(window->mlx_ptr, window->win_ptr,
			window->img_ptr, 0, 0);
	}
	return (0);
}

void	hook_event(t_screen *window)
{
	mlx_hook(window->win_ptr, 2, 0, key_event, window);
	mlx_hook(window->win_ptr, 17, 1, closing, window);
	mlx_hook(window->win_ptr, 4, 1L<<4, mouse_event, window);
	mlx_hook(window->win_ptr, 6, 1L<<4, motion_event, window);
}
