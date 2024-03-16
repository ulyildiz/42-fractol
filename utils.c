/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 07:33:19 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/03/13 07:34:37 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 == *s2 && *s1 != '\0' && *s2 != '\0')
	{
		s1++;
		s2++;
	}
	return ((*s1) - (*s2));
}

double	atoi_point(const char *str)
{
	double	res;
	double	div;
	int		sign;

	div = 0.1;
	sign = 1;
	res = 0;
	while (*str == ' ' || (9 <= *str && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str != '.' && ('0' <= *str && *str <= '9'))
		res = (res * 10.0) + (*(str++) - '0');
	if (*str == '.')
		str++;
	while ('0' <= *str && *str <= '9')
	{
		res += (*(str++) - '0') * div;
		div *= 0.1;
	}
	return (res * sign);
}

char	*ft_strdup(const char *s1)
{
	char	*s2;
	int		i;

	i = 0;
	while (s1[i])
		i++;
	s2 = (char *)malloc(i + 1);
	if (!s2)
		return (0);
	i = 0;
	while (s1[i] != '\0')
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}
