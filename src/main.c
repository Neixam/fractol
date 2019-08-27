/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 22:18:10 by abourenn          #+#    #+#             */
/*   Updated: 2019/07/28 00:49:59 by abourenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		ft_putusage(void)
{
	ft_putstr("./fractol [name fractale]\n: Mandelbrot, Julia, Randi\n");
	return (1);
}

void	draw_droite(t_proj *oui, int size, float angle, int boo)
{
	if (boo == 0)
	{
		oui->xf = oui->xi + size * cos(angle);
		oui->yf = oui->yi - size * sin(angle);
	}
	if (boo == 1)
	{
		oui->xi = oui->xf;
		oui->yi = oui->yf;
	}
}

int		power(int nb, int pow)
{
	if (pow == 0)
		return (1);
	return (nb * power(nb, pow - 1));
}

int		deep(int size, int div)
{
	int		i;

	i = 1;
	while (size / power(div, i) > div)
		i++;
	return (i);
}

void	draw_fractoul(t_mlx *mlx, int size, float angle)
{
	if (size < (mlx->len * mlx->zoom) / power(3, mlx->profondeur))
		return ;
	draw_droite(&(mlx->fract), size, angle, 0);
	draw_fractoul(mlx, size / 3, angle);
	if (size / 3 < (mlx->len * mlx->zoom) / power(3, mlx->profondeur))
		draw_seg(mlx, mlx->fract);
	draw_droite(&(mlx->fract), size, angle, 1);
	draw_droite(&(mlx->fract), size, angle + M_PI / 3, 0);
	draw_fractoul(mlx, size / 3, angle + M_PI / 3);
	if (size / 3 < (mlx->len * mlx->zoom) / power(3, mlx->profondeur))
		draw_seg(mlx, mlx->fract);
	draw_droite(&(mlx->fract), size, angle + M_PI / 3, 1);
	draw_droite(&(mlx->fract), size, angle - M_PI / 3, 0);
	draw_fractoul(mlx, size / 3, angle - M_PI / 3);
	if (size / 3 < (mlx->len * mlx->zoom) / power(3, mlx->profondeur))
		draw_seg(mlx, mlx->fract);
	draw_droite(&(mlx->fract), size, angle - M_PI / 3, 1);
	draw_droite(&(mlx->fract), size, angle, 0);
	draw_fractoul(mlx, size / 3, angle);
	if (size / 3 < (mlx->len * mlx->zoom) / power(3, mlx->profondeur))
		draw_seg(mlx, mlx->fract);
	draw_droite(&(mlx->fract), size, angle, 1);
}

void	draw_elfract(t_mlx *mlx, int size, float angle, int i, float angle_end)
{
//	t_proj	yes;

	if (angle <= angle_end || i > 3)
		return ;
	draw_fractoul(mlx, size / 3, angle);
//	yes.xi = oui->xi;
//	yes.xf = oui->xf;
//	yes.yi = oui->yi;
//	yes.yf = oui->yf;
//	if (angle - 2*M_PI / 3 > angle_end)
//		draw_elfract(mlx, size, angle + M_PI / 3, i + 1, angle_end - M_PI / 3);
	draw_elfract(mlx, size, angle - 2*M_PI / 3, i + 1, angle_end);
}

int		julia_zn(t_mlx *mlx, int zero, t_comp z)
{
	float	tmp;

	if (zero > 100)
		return (-1);
	if ((z.a * z.a) + (z.bi * z.bi) >= 4)
		return (zero);
	tmp = z.a;
	z.a = ((z.a * z.a) - (z.bi * z.bi)) + mlx->c.a;
	z.bi = (2 * tmp * z.bi) + mlx->c.bi;
	return (julia_zn(mlx, zero + 1, z));
}

void	affiche_julia(t_mlx *mlx, t_comp *z)
{
	z->a = -2;
	while (z->a <= 2)
	{
		z->bi = -1.5;
		mlx->fract.xi = mlx->pos_x + (z->a * mlx->zoom);
		if (mlx->pos_x + (z->a * mlx->zoom) >= 0 && mlx->pos_x + (z->a * mlx->zoom) < mlx->w_x)
			while (z->bi <= 1.5)
			{
				if (mlx->pos_y - (z->bi * mlx->zoom) >= 0 && mlx->pos_y - (z->bi * mlx->zoom) < mlx->w_y)
					if (julia_zn(mlx, 0, *z) == 1)
					{
						fill_img(mlx, mlx->pos_x + (z->a * mlx->zoom), mlx->pos_y - (z->bi * mlx->zoom), 0xFF00FF);
		mlx->fract.yi = mlx->pos_y - (z->bi * mlx->zoom);
							mlx->fract.yf = mlx->pos_y - (z->bi * mlx->zoom);
					}
				z->bi += 0.1;
			}
		z->a += 0.1;
		mlx->fract.xf = mlx->pos_x + (z->a * mlx->zoom);
		draw_seg(mlx, mlx->fract);
	}
}

void	affiche_juulia(t_mlx *mlx)
{
	int		x;
	int 	y;
	t_comp	z;
	int		iter;

	x = 0;
	while (x < mlx->w_x)
	{
		y = 0;
		z.a = (mlx->pos_x - x) / mlx->zoom;
		while (y < mlx->w_y)
		{
			z.bi = (mlx->pos_y - y) / mlx->zoom;
			if ((iter = julia_zn(mlx, 0, z)) == -1)
				fill_img(mlx, x, y, 0);
			else
				fill_img(mlx, x, y, 0xABCDEF * iter);
			//	fill_img(mlx, x, y, 0x33525);
			y++;
		}
		x++;
	}
}

int		deal_key(int key, t_mlx *mlx)
{
//	t_comp	z;

	ft_putnbr(key);
	ft_putchar('\n');
	if (key == 8)
		mlx->c.a += 0.001;
	if (key == 32)	
		mlx->c.a -= 0.001;
	if (key == 31)	
		mlx->c.bi += 0.001;
	if (key == 15)
		mlx->c.bi -= 0.001;
	if (key == 123)
	{
		mlx->pos_x += 1;
	}
	if (key == 124)
	{
		mlx->pos_x -= 1;
	}
	if (key == 125)
	{
		mlx->pos_y -= 1;
	}
	if (key == 126)
	{
		mlx->pos_y += 1;
	}
	if (key == 69)
	{
		mlx->zoom /= 0.9;
		mlx->pos_y -= ((mlx->w_y / 2) - mlx->pos_y) / mlx->zoom;
		mlx->pos_x -= ((mlx->w_x / 2) - mlx->pos_x) / mlx->zoom;
		mlx->profondeur = deep(mlx->len * mlx->zoom, 3);
	}
	if (key == 78)
	{
		mlx->zoom *= 0.9;
		mlx->pos_y += ((mlx->w_y / 2) - mlx->pos_y) / mlx->zoom;
		mlx->pos_x += ((mlx->w_x / 2) - mlx->pos_x) / mlx->zoom;
		mlx->profondeur = deep(mlx->len * mlx->zoom, 3);
	}
	if (key == 53)
		exit(EXIT_SUCCESS);
	ft_clear_window(mlx);
//	mlx_destroy_image(mlx->mlx_ptr, mlx->img_ptr);
//	mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, mlx->w_x, mlx->w_y);
//	mlx->img_mod = mlx_get_data_addr(mlx->img_ptr, &(mlx->bbp), &(mlx->s_l), &(mlx->end));
//	draw_elfract(mlx, mlx->len * mlx->zoom, 0.0, 0, - 2 * M_PI);
	affiche_juulia(mlx);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr, 0, 0);
	return (1);
}

int		main(int ac, char **av)
{
	t_mlx	mlx;

	if (ac != 2)
		return (ft_putusage());
	mlx.mlx_ptr = mlx_init();
	mlx.w_x = 400;
	mlx.w_y = 400;
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, mlx.w_x, mlx.w_y, av[0]);
	mlx.len = mlx.w_x * 0.2;
	mlx.profondeur = deep(mlx.len, 3);
	mlx.zoom = 1;
	mlx.c.a = -0.85;
	mlx.c.bi = 0.2;
	mlx.pos_x = mlx.w_x / 2;
	mlx.pos_y = mlx.w_y / 2;
	mlx.img_ptr = mlx_new_image(mlx.mlx_ptr, mlx.w_x, mlx.w_y);
	mlx.img_mod = mlx_get_data_addr(mlx.img_ptr, &(mlx.bbp), &(mlx.s_l), &(mlx.end));
	mlx_hook(mlx.win_ptr, 2, 0, deal_key, &mlx);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}
