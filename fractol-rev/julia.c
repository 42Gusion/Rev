/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stariq <stariq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 01:17:37 by stariq            #+#    #+#             */
/*   Updated: 2024/10/29 16:42:25 by stariq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	parse_julia(t_fractol *fractal, char **av)
{
	if (av[2] == NULL || av[3] == NULL)
	{
		ft_putstr_fd("Please provide both Julia parameters.\n", STDERR_FILENO);
		return (0);
	}
	if (!parse_julia_param(av[2]) || !parse_julia_param(av[3]))
	{
		ft_putstr_fd("Invalid Julia parameters", STDERR_FILENO);
		return (0);
	}
	fractal->julia_x = atodbl(av[2]);
	fractal->julia_y = atodbl(av[3]);
	if (fractal->julia_x < -2 || fractal->julia_x > 2 || fractal->julia_y < -2
		|| fractal->julia_y > 2)
	{
		ft_putstr_fd("Julia parameters should be between -2 and 2.\n",
			STDERR_FILENO);
		return (0);
	}
	return (1);
}

int	parse_julia_param(const char *param)
{
	int	dp_count;
	int	length;
	int	valid;
	int	i;

	dp_count = 0;
	length = (int)strlen(param);
	valid = 1;
	i = 0;
	while (i < length)
	{
		if (param[i] == '.')
			dp_count++;
		else if (!ft_isdigit(param[i]) && (param[i] != '-' || i != 0))
		{
			valid = 0;
			break ;
		}
		i++;
	}
	if (dp_count > 1)
		valid = 0;
	return (valid);
}

int	julia_track(int x, int y, t_fractol *fractol)
{
	t_mappingrange	range_x;
	t_mappingrange	range_y;

	if (!ft_strncmp(fractol->name, "julia", 5) && !fractol->is_locked)
	{
		range_x.n_min = -2;
		range_x.n_max = +2;
		range_x.o_min = 0;
		range_x.o_max = WIDTH;
		fractol->julia_x = map(x, range_x) * fractol->zoom;
		range_y.n_min = +2;
		range_y.n_max = -2;
		range_y.o_min = 0;
		range_y.o_max = HEIGHT;
		fractol->julia_y = map(y, range_y) * fractol->zoom;
		fractol_render(fractol);
	}
	return (0);
}
