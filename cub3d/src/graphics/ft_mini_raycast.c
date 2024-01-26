/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_raycast.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchbouki <rchbouki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 23:59:02 by rchbouki          #+#    #+#             */
/*   Updated: 2024/01/26 16:33:45 by rchbouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	init_raycast_mini(t_data *data, t_coord *cd, t_minimap *m, int len)
{
	cd->pos_x = data->player->pos_x;
	cd->pos_y = data->player->pos_y;
	cd->dir_x = data->player->dir_x;
	cd->dir_y = data->player->dir_y;
	m->aspect_ratio = (double)len / (double)data->nb_lines;
	m->width = MAP_SIZE;
	m->height = MAP_SIZE;
	if (m->aspect_ratio > 1)
		m->height = (int)(MAP_SIZE / m->aspect_ratio);
	else
		m->width = (int)(MAP_SIZE * m->aspect_ratio);
	m->img = (int *)data->minimap_addr;
}

static void	mini_loop(t_coord *cd, t_minimap *m, t_data *data, double len)
{
	double	map_x;
	double	map_y;
	double	nb_lines;

	map_x = cd->pos_x;
	map_y = cd->pos_y;
	nb_lines = (double)data->nb_lines;
	while (data->tab[(int)map_y][(int)map_x] != '1')
	{
		map_x += cd->raydir_x * 0.01;
		map_y += cd->raydir_y * 0.01;
		m->x = (int)((map_x - cd->pos_x) * (m->width / len));
		m->y = (int)((map_y - cd->pos_y) * (m->height / nb_lines));
		m->index_x = (int)(data->player->pos_x * (m->width / len)) + m->x;
		m->index_y = (int)(data->player->pos_y * (m->height / nb_lines)) + m->y;
		if ((m->index_x >= 0) && (m->index_x < m->width)
			&& (m->index_y >= 0) && (m->index_y < m->height))
		{
			m->index = m->index_y * m->width + m->index_x;
			m->img[m->index] = 0xFF0000;
		}
		else
			break ;
	}
}

void	raycast_minimap(t_data *data, int longest)
{
	t_coord		coord;
	t_minimap	mini;
	double		step_size;
	double		fov;
	double		angle;

	step_size = 0.01;
	fov = 60 * (M_PI / 180);
	angle = -fov / 2;
	init_raycast_mini(data, &coord, &mini, (double)longest);
	while (angle <= fov / 2)
	{
		coord.raydir_x = coord.dir_x * cos(angle) - coord.dir_y * sin(angle);
		coord.raydir_y = coord.dir_x * sin(angle) + coord.dir_y * cos(angle);
		mini_loop(&coord, &mini, data, longest);
		angle += step_size;
	}
}
