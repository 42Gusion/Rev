/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stariq <stariq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 01:19:22 by stariq            #+#    #+#             */
/*   Updated: 2024/10/29 01:19:24 by stariq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_complex	get_mapped_coordinates(int x, int y, t_fractol *fractal)
{
	t_complex		z;
	t_mappingrange	range_x;
	t_mappingrange	range_y;

	range_x.n_min = -2;
	range_x.n_max = +2;
	range_x.o_min = 0;
	range_x.o_max = WIDTH;
	z.x = map(x, range_x) * fractal->zoom + fractal->shift_x;
	range_y.n_min = +2;
	range_y.n_max = -2;
	range_y.o_min = 0;
	range_y.o_max = HEIGHT;
	z.y = map(y, range_y) * fractal->zoom + fractal->shift_y;
	return (z);
}

int	iterate_complex(t_complex z, t_complex c, t_fractol *fractal)
{
	int	i;

	i = 0;
	while (i < fractal->iterations_defintion)
	{
		if (ft_strncmp(fractal->name, "julia", 5) == 0)
			z = ft_sum(ft_square(z), c);
		else if (ft_strncmp(fractal->name, "mandelbrot", 10) == 0)
			z = ft_sum(ft_square(z), c);
		else if (ft_strncmp(fractal->name, "burning_ship", 12) == 0)
		{
			z.x = fabsl(z.x);
			z.y = fabsl(z.y);
			z = ft_sum(ft_square(z), c);
		}
		if ((z.x * z.x) + (z.y * z.y) > fractal->escape_value)
			return (i);
		i++;
	}
	return (fractal->iterations_defintion);
}

int	get_color_for_pixel(t_complex z, t_complex c, t_fractol *fractal)
{
	int				iterations;
	t_mappingrange	range_color;

	iterations = iterate_complex(z, c, fractal);
	if (iterations == fractal->iterations_defintion)
		return (BLACK);
	range_color.n_min = AQUA_DREAM;
	range_color.n_max = HOT_PINK;
	range_color.o_min = 0;
	range_color.o_max = fractal->iterations_defintion;
	return (map(iterations, range_color));
}

void	handle_pixel(int x, int y, t_fractol *fractal)
{
	int			color;
	t_complex	z;
	t_complex	c;

	z = get_mapped_coordinates(x, y, fractal);
	mandel_vs_julia(&z, &c, fractal);
	color = get_color_for_pixel(z, c, fractal);
	my_pixel_put(x, y, &fractal->img, color);
}

void	fractol_render(t_fractol *fractol)
{
	int	x;
	int	y;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			handle_pixel(x, y, fractol);
	}
	mlx_put_image_to_window(fractol->mlx_connection, fractol->mlx_window,
		fractol->img.img_ptr, 0, 0);
}
