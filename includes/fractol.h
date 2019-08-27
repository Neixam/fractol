/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 22:21:15 by abourenn          #+#    #+#             */
/*   Updated: 2019/07/11 23:09:32 by abourenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"
# include "mlx.h"
# include <math.h>
# include <fcntl.h>

typedef struct	s_comp
{
	float	a;
	float	bi;
}				t_comp;

typedef struct	s_proj
{
	float	xi;
	float	xf;
	float	yi;
	float	yf;
}				t_proj;

typedef struct	s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*img_mod;
	float	len;
	int		profondeur;
	int		w_x;
	int		w_y;
	int		bbp;
	int		s_l;
	int		end;
	float	pos_x;
	float	pos_y;
	float	zoom;
	float	dist_y;
	float	dist_x;
	t_proj	fract;
	t_comp	c;
}				t_mlx;

typedef struct	s_draw
{
	int		dx;
	int		dy;
	int		i;
	int		xinc;
	int		yinc;
	int		cumul;
	int		x;
	int		y;
}				t_draw;


void			draw_seg(t_mlx *mlx, t_proj proj);
void			fill_img(t_mlx *mlx, int x, int y, int color);
void			blank_img(t_mlx *mlx);
void			ft_clear_window(t_mlx *mlx);

#endif
