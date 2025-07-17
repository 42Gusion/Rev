/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stariq <stariq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 01:15:48 by stariq            #+#    #+#             */
/*   Updated: 2024/10/29 16:42:15 by stariq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	handle_invalid_arguments(void)
{
	ft_putstr_fd(ERROR_MESSAGE, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

static bool	is_valid_fractal_name(char *name)
{
	return (ft_strncmp(name, "mandelbrot", 10) == 0 || ft_strncmp(name,
			"burning_ship", 12) == 0 || ft_strncmp(name, "julia", 5) == 0);
}

static void	handle_julia_fractal(t_fractol *fractal, char **av)
{
	if (!parse_julia(fractal, av))
		exit(EXIT_FAILURE);
	fractal_init(fractal);
	fractol_render(fractal);
	mlx_loop(fractal->mlx_connection);
}

static void	handle_other_fractals(t_fractol *fractal)
{
	fractal_init(fractal);
	fractol_render(fractal);
	mlx_loop(fractal->mlx_connection);
}

int	main(int ac, char **av)
{
	t_fractol	fractal;

	if ((ac != 2 && ac != 4) || (ac == 4 && ft_strncmp(av[1], "julia", 5) != 0))
		return (handle_invalid_arguments());
	fractal.name = av[1];
	if (is_valid_fractal_name(fractal.name))
	{
		if (ac == 2)
		{
			if (ft_strncmp(av[1], "julia", 5) == 0)
			{
				ft_putstr_fd("Please provide both Julia parameters.\n",
					STDERR_FILENO);
				return (0);
			}
			handle_other_fractals(&fractal);
		}
		else
			handle_julia_fractal(&fractal, av);
	}
	else
		return (handle_invalid_arguments());
	return (0);
}
