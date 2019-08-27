/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboilea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 17:19:29 by anboilea          #+#    #+#             */
/*   Updated: 2019/07/12 00:20:45 by abourenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	fill_img(t_mlx *mlx, int x, int y, int color)
{
	if (mlx->w_x * mlx->w_y * 4 < (x * 4) + (y * mlx->s_l) ||
		(x * 4) + (y * mlx->s_l) < 0 || x  >= mlx->w_x  || x < 0)
		return ;
	mlx->img_mod[x * 4 + y * mlx->s_l + 2] = color / 0x10000;
	mlx->img_mod[(x * 4) + (y * mlx->s_l) + 1] = (color / 0x100) % 0x100;
	mlx->img_mod[(x * 4) + (y * mlx->s_l)] = color % 0x100;
}

void	blank_img(t_mlx *mlx)
{
	int		x;
	int		y;
	
	x = 0;
	while (x < mlx->w_x)
	{
		y = 0;
		while (y < mlx->w_y)
		{
			fill_img(mlx, x, y, 0);
			y++;
		}
		x++;
	}
}

void	ft_clear_window(t_mlx *mlx)
{
	blank_img(mlx);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr, 0, 0);
}

void	fill_seg(t_draw *seg, t_proj proj)
{
	seg->x = proj.xi;
	seg->y = proj.yi;
	seg->dx = proj.xf - proj.xi;
	seg->dy = proj.yf - proj.yi;
	seg->xinc = (seg->dx > 0) ? 1 : -1;
	seg->yinc = (seg->dy > 0) ? 1 : -1;
	seg->dx = abs(seg->dx);
	seg->dy = abs(seg->dy);
}

void	draw_seg_2(t_mlx *mlx, t_draw seg)
{
	seg.cumul = seg.dx / 2;
	seg.i = 1;
	while (seg.i <= seg.dx)
	{
		seg.x += seg.xinc;
		seg.cumul += seg.dy;
		if (seg.cumul >= seg.dx)
		{
			seg.cumul -= seg.dx;
			seg.y += seg.yinc;
		}
		if (seg.x <= mlx->w_x && seg.x >= 0 && seg.y >= 0 && seg.y <= mlx->w_y)
			fill_img(mlx, seg.x, seg.y, 0xFF00FF);
		seg.i++;
	}
}

void	draw_seg(t_mlx *mlx, t_proj proj)
{
	t_draw	seg;

	fill_seg(&seg, proj);
	if (seg.x <= mlx->w_x && seg.x >= 0 && seg.y >= 0 && seg.y <= mlx->w_y)
		fill_img(mlx, seg.x, seg.y, 0xFF00FF);
	if (seg.dx > seg.dy)
		draw_seg_2(mlx, seg);
	else
	{
		seg.cumul = seg.dy / 2;
		seg.i = 1;
		while (seg.i <= seg.dy)
		{
			seg.y += seg.yinc;
			seg.cumul += seg.dx;
			if (seg.cumul >= seg.dy)
			{
				seg.cumul -= seg.dy;
				seg.x += seg.xinc;
			}
			if (seg.x <= mlx->w_x && seg.x >= 0 && seg.y >= 0 && seg.y <= mlx->w_y)
				fill_img(mlx, seg.x, seg.y, 0xFF00FF);
			seg.i++;
		}
	}
}
