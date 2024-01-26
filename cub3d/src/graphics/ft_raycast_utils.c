/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchbouki <rchbouki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 18:52:18 by rchbouki          #+#    #+#             */
/*   Updated: 2024/01/26 19:56:16 by rchbouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_utils(t_dda *dda, int a, double b, int test)
{
	if (test)
	{
		dda->step_x = a;
		dda->side_dist_x = b * dda->delta_dist_x;
	}
	else
	{
		dda->step_y = a;
		dda->side_dist_y = b * dda->delta_dist_y;
	}
}

void	dda_loop_utils(t_dda *dda, int test)
{
	if (test)
	{
		dda->side_dist_x += dda->delta_dist_x;
		dda->map_x += dda->step_x;
		dda->side = 0;
	}
	else
	{
		dda->side_dist_y += dda->delta_dist_y;
		dda->map_y += dda->step_y;
		dda->side = 1;
	}
}

void	tex_index_init(t_dda *dda, t_tex_dda *tex, int test)
{
	if (test)
	{
		if (dda->step_x > 0)
			tex->tex_index = TEXTURE_EAST;
		else
			tex->tex_index = TEXTURE_WEST;
	}
	else
	{
		if (dda->step_y > 0)
			tex->tex_index = TEXTURE_SOUTH;
		else
			tex->tex_index = TEXTURE_NORTH;
	}
}

void	draw_vertical_line(t_data *data, int x, int draw_start, int color)
{
	int	y;
	int	*img;
	int	draw_end;

	draw_end = draw_start + 1;
	img = (int *)data->addr;
	y = draw_start - 1;
	while (++y < draw_end)
	{
		if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
			img[y * WIDTH + x] = color;
	}
}
