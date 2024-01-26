/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycasting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchbouki <rchbouki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 18:48:00 by rchbouki          #+#    #+#             */
/*   Updated: 2024/01/26 19:58:40 by rchbouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	ft_init_raycast(t_dda *dda, t_data *data, int x)
{
	dda->camera_x = 2 * x / (double)WIDTH - 1;
	dda->raydir_x = data->player->dir_x + data->player->plane_x * dda->camera_x;
	dda->raydir_y = data->player->dir_y + data->player->plane_y * dda->camera_x;
	dda->map_x = (int)data->player->pos_x;
	dda->map_y = (int)data->player->pos_y;
	if (fabs(dda->raydir_x) < 1e-6)
		dda->delta_dist_x = 1e30;
	else
		dda->delta_dist_x = fabs(1 / dda->raydir_x);
	if (fabs(dda->raydir_y) < 1e-6)
		dda->delta_dist_y = 1e30;
	else
		dda->delta_dist_y = fabs(1 / dda->raydir_y);
	dda->hit = 0;
	if (dda->raydir_x < 0)
		init_utils(dda, -1, data->player->pos_x - dda->map_x, 1);
	else
		init_utils(dda, 1, dda->map_x + 1.0 - data->player->pos_x, 1);
	if (dda->raydir_y < 0)
		init_utils(dda, -1, data->player->pos_y - dda->map_y, 0);
	else
		init_utils(dda, 1, dda->map_y + 1.0 - data->player->pos_y, 0);
}

static void	dda_init_loop(t_dda *dda, t_data *data)
{
	double	x;
	double	y;

	while (dda->hit == 0)
	{
		if (dda->side_dist_x < dda->side_dist_y)
			dda_loop_utils(dda, 1);
		else
			dda_loop_utils(dda, 0);
		if (dda->map_x >= 0 && dda->map_x < WIDTH
			&& dda->map_y >= 0 && dda->map_y < HEIGHT)
		{
			if (data->tab[dda->map_y][dda->map_x] == '1')
				dda->hit = 1;
		}
		else
			dda->hit = 1;
	}
	x = (dda->map_x - data->player->pos_x + (1 - dda->step_x) / 2);
	y = (dda->map_y - data->player->pos_y + (1 - dda->step_y) / 2);
	if (dda->side == 0)
		dda->wall_dist = x / dda->raydir_x;
	else
		dda->wall_dist = y / dda->raydir_y;
}

static void	init_textures(t_data *data, t_dda *dda, t_tex_dda *tex)
{
	dda->line_height = (int)(HEIGHT / dda->wall_dist);
	dda->draw_start = (int)(((double)HEIGHT - (double)dda->line_height) / 2.0);
	if (dda->draw_start < 0)
		dda->draw_start = 0;
	dda->draw_end = dda->line_height / 2 + HEIGHT / 2;
	if (dda->draw_end >= HEIGHT)
		dda->draw_end = HEIGHT - 1;
	if (dda->side == 0)
		tex_index_init(dda, tex, 1);
	else
		tex_index_init(dda, tex, 0);
	if (dda->side == 0)
		dda->wall_x = data->player->pos_y + dda->wall_dist * dda->raydir_y;
	else
		dda->wall_x = data->player->pos_x + dda->wall_dist * dda->raydir_x;
	dda->wall_x -= floor(dda->wall_x);
	tex->tex_width = data->texture[tex->tex_index].width;
	tex->tex_x = (int)(dda->wall_x * (double)(tex->tex_width));
	if ((dda->side == 0 && dda->raydir_x < 0)
		|| (dda->side == 1 && dda->raydir_y > 0))
		tex->tex_x = tex->tex_width - tex->tex_x - 1;
	tex->tex_x = tex->tex_x % tex->tex_width;
	tex->tex_height = data->texture[tex->tex_index].height;
}

static void	ft_draw(t_dda *dda, t_tex_dda *tex, t_data *data, int x)
{
	int	color;
	int	y;
	int	tex_y;

	y = dda->draw_start - 1;
	while (++y < dda->draw_end)
	{
		tex->d = y * 256 - HEIGHT * 128 + dda->line_height * 128;
		tex_y = (unsigned int)((tex->d / 256) * tex->tex_height);
		tex->tex_y = tex_y / dda->line_height;
		if (tex->tex_y >= (unsigned int)tex->tex_height)
			tex->tex_y = tex->tex_height - 1;
		color = data->texture[tex->tex_index].data[tex->tex_y
			* data->texture[tex->tex_index].width + tex->tex_x];
		draw_vertical_line(data, x, y, color);
	}
	y = -1;
	while (++y < HEIGHT)
	{
		if (y < dda->draw_start)
			draw_vertical_line(data, x, y, data->ceiling_color);
		else if (y > dda->draw_end)
			draw_vertical_line(data, x, y, data->floor_color);
	}
}

void	perform_raycasting(t_data *data)
{
	t_tex_dda		tex;
	t_dda			dda;
	int				x;

	x = -1;
	while (++x < WIDTH)
	{
		ft_init_raycast(&dda, data, x);
		dda_init_loop(&dda, data);
		init_textures(data, &dda, &tex);
		ft_draw(&dda, &tex, data, x);
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}
