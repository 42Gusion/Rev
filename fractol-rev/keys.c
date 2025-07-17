/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stariq <stariq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 01:19:06 by stariq            #+#    #+#             */
/*   Updated: 2024/10/29 16:42:32 by stariq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	key_handler(int keycode, t_fractol *fractol)
{
	if (keycode == 53)
		close_handler(fractol);
	else if (keycode == 4)
		fractol->is_locked = !fractol->is_locked;
	else if (!fractol->is_locked)
	{
		if (keycode == 124 || keycode == 123)
			handle_arrow_keys(fractol, keycode);
		else if (keycode == 125 || keycode == 126)
			handle_up_down_keys(fractol, keycode);
		else if (keycode == 69 || keycode == 78)
			handle_plus_minus_keys(fractol, keycode);
	}
	fractol_render(fractol);
	return (0);
}

void	handle_arrow_keys(t_fractol *fractol, int keycode)
{
	double	shift_amount;

	shift_amount = 0.5 * fractol->zoom;
	if (keycode == 124)
		fractol->shift_x -= shift_amount;
	else if (keycode == 123)
		fractol->shift_x += shift_amount;
}

void	handle_up_down_keys(t_fractol *fractol, int keycode)
{
	double	shift_amount;

	shift_amount = 0.5 * fractol->zoom;
	if (keycode == 125)
		fractol->shift_y -= shift_amount;
	else if (keycode == 126)
		fractol->shift_y += shift_amount;
}

void	handle_plus_minus_keys(t_fractol *fractol, int keycode)
{
	int	iteration_change;

	iteration_change = 0;
	if (keycode == 69)
		iteration_change = 10;
	else if (keycode == 78)
		iteration_change = -10;
	fractol->iterations_defintion += iteration_change;
}
