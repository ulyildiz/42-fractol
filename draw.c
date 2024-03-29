/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 07:33:47 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/03/15 08:50:06 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx/mlx.h"
#include <math.h>

/*double	*decrease_color(int iteration)
{
	double	inr[3];

	inr[0] = iteration % I_XMAX; 0.5
	inr[1] = iteration % N_XMAX; 0.3
	inr[2] = iteration % R_XMAX; 0.1
	return (inr);
}*/

/*
	ikinci renk olayı
	büyük ihtimalle gökkuşağı
	red = sqrt(iteration/MAX_ITER) * 255
	green = (1 - 2 * red)
*/

/*
	precolor1 = iteration - log(log2(sqrt(pixels.re * pixels.re + pixels.im * pixels.im)))
	precolor2 = iteration + 1 - log(log2(sqrt(pixels.re * pixels.re + pixels.im * pixels.im))) + 1
	color = lineer_interpolasyon(precolor1, precolor2,  precolor1 % 1);

	lineer_intepolasyon(precolor1, precolor2, t)
	{
		precolor1 * (1 - t) + precolor2 * t;
	}
*/

static int	get_color(int iteration, int code)
{
	t_byte	red;
	t_byte	green;
	t_byte	blue;
//	double	*rgb;

//	rgb = decrease_color(iteration);
	if (iteration == MAX_ITER)
		return (0);
	if (code == 1)
	{
		red = (sin(iteration * 0.1) + 1) / 2 * 255;
		green = (sin(iteration * 0.01) + 1) / 2 * 255;
		blue = (sin(iteration * 0.001) + 1) / 2 * 255;
	}
	else if (code == 2)
	{
		red = (sin(iteration * 0.1) + 1) / 2 * 255;
		green = (sin(iteration * 0.001) + 1) / 2 * 255;
		blue = (sin(iteration * 0.01) + 1) / 2 * 255;
	}
	else 
	{
		red = (sin(iteration * 0.001) + 1) / 2 * 255;
		green = (sin(iteration * 0.01) + 1) / 2 * 255;
		blue = (sin(iteration * 0.1) + 1) / 2 * 255;
	}
	return (red << 16 | green << 8 | blue);
}

static void	put_pixels(t_screen *window, int x, int y, int color)
{
	int	offset;

	offset = (window->size_line * y) + (x * window->bits_per_pixel / 8);
	*((unsigned int *)(window->img_addr + offset)) = color;
}

static int	choose_formula(t_complex pixels, t_screen *window)
{
	if (window->fract_name[0] == 'j')
		return (calc_for_julia(pixels, window));
	else if (window->fract_name[0] == 'm')
		return (calc_for_mandel(pixels, window));
	else if (window->fract_name[0] == 'b')
		return (calc_for_bship(pixels, window));
	return (-1);
}
#include <time.h>

void	draw_fract(t_screen *window)
{
	clock_t start, end;
    double cpu_time_used;
	int			x;
	int			y;
	t_complex	pixels;
	int			color;

	x = -1;
	while (++x < WIDTH)
	{
		y = -1;
		while (++y < HEIGHT)
		{
			pixels.re = (window->set->min_re + (window->set->max_re
						- window->set->min_re) * x / WIDTH)
				* window->set->zoom_factor;
			pixels.im = (window->set->min_im + (window->set->max_im
						- window->set->min_im) * y / HEIGHT)
				* window->set->zoom_factor;
			color = get_color(choose_formula(pixels, window),
					window->set->color_code);
			window->set->iteration = -1;
			put_pixels(window, x, y, color);
		}
	}
	cpu_time_used = ((double) (end - start));
	printf("Programın çalışma süresi: %f saniye\n", cpu_time_used);
}
