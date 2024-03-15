/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 07:34:02 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/03/15 06:36:27 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	num_check(const char *av)
{
	int	i;

	i = -1;
	if (av[0] == '-' || av[0] == '+')
		av++;
	while (av[++i])
		if (!(('0' <= av[i] && av[i] <= '9') || av[i] == '.'))
			error_occur(1, 0);
	if (av[1] != '\0' && !(('0' <= av[0] && av[0] <= '1') && av[1] == '.'))
		error_occur(1, 0);
}

void	check_point(int ac, const char *av[])
{
	if (!ft_strcmp(*av, "julia") || !ft_strcmp(*av, "mandelbrot")
		|| !ft_strcmp(*av, "burningship"))
	{
		if (!ft_strcmp(*av, "mandelbrot") && ac == 2)
			return ;
		else if (!ft_strcmp(*av, "burningship") && ac == 2)
			return ;
		else if (!ft_strcmp(*av, "julia") && ac == 4)
		{
			num_check(av[1]);
			num_check(av[2]);
			return ;
		}
	}
	error_occur(1, 0);
}
