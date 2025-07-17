/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stariq <stariq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 01:14:55 by stariq            #+#    #+#             */
/*   Updated: 2024/10/29 01:14:57 by stariq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "./mlx/mlx.h"
# include <ApplicationServices/ApplicationServices.h>
# include <ctype.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define ERROR_MESSAGE "Enter Mandelbrot or Julia <v1> <v2> or Burning ship"

# define WIDTH 500
# define HEIGHT 500

# define BLACK 0x000000
# define WHITE 0xFFFFFF
# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF

// Psychedelic colors
# define MAGENTA_BURST 0xFF00FF
# define LIME_SHOCK 0xCCFF00
# define NEON_ORANGE 0xFF6600
# define PSYCHEDELIC_PURPLE 0x660066
# define AQUA_DREAM 0x33CCCC
# define HOT_PINK 0xFF66B2
# define ELECTRIC_BLUE 0x0066FF
# define LAVA_RED 0xFF3300
# define NUDE_PINK 0xF2DADF
# define DEEP_SPACE_BLUE 0x2C2A4A
# define NEBULA_PURPLE 0x6D2F7E
# define COSMIC_PINK 0xD84C73
# define STAR_WHITE 0xF0EADC

typedef struct s_complex
{
	long double	x;
	long double	y;
}				t_complex;

typedef struct s_img
{
	void		*img_ptr;
	char		*pixels_ptr;
	int			bpp;
	int			endian;
	int			line_len;
	double		scale;
}				t_img;

typedef struct s_fractol
{
	char		*name;
	void		*mlx_connection;
	void		*mlx_window;
	t_img		img;
	double		escape_value;
	int			iterations_defintion;
	double		shift_x;
	double		shift_y;
	double		zoom;
	double		julia_x;
	double		julia_y;
	int			is_locked;
}				t_fractol;

typedef struct s_mappingrange
{
	double		n_min;
	double		n_max;
	double		o_min;
	double		o_max;
}				t_mappingrange;

int				ft_strncmp(char *str1, char *str2, unsigned int n);
void			ft_putstr_fd(char *s, int fd);
double			atodbl(char *s);
int				ft_strlen(char *str);
int				parse_julia_param(const char *param);
int				parse_julia(t_fractol *fractal, char **av);
void			fractal_init(t_fractol *fractal);
void			fractol_render(t_fractol *fractol);
double			map(double uns_num, t_mappingrange range);
t_complex		ft_sum(t_complex z1, t_complex z2);
t_complex		ft_square(t_complex z);
int				key_handler(int keycode, t_fractol *fractol);
void			handle_arrow_keys(t_fractol *fractol, int keycode);
void			handle_up_down_keys(t_fractol *fractol, int keycode);
void			handle_plus_minus_keys(t_fractol *fractol, int keycode);
int				close_handler(t_fractol *fractol);
int				mouse_handler(int button, int x, int y, t_fractol *fractol);
int				julia_track(int x, int y, t_fractol *fractal);
int				parse_julia(t_fractol *fractal, char **av);
t_complex		get_mapped_coordinates(int x, int y, t_fractol *fractal);
int				get_color_for_pixel(t_complex z, t_complex c,
					t_fractol *fractal);
void			handle_pixel(int x, int y, t_fractol *fractal);
int				resize_handler(int x, int y, t_fractol *fractol);
void			my_pixel_put(int x, int y, t_img *img, int color);
int				ft_isdigit(int c);
void			mandel_vs_julia(t_complex *z, t_complex *c, t_fractol *fractal);
#endif
