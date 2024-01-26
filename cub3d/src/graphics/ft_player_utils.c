/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_player_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchbouki <rchbouki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 19:48:44 by rchbouki          #+#    #+#             */
/*   Updated: 2024/01/26 19:56:32 by rchbouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	corner_coll(t_data *data, t_collision coll, double x, double y)
{
	double	threshold;

	threshold = 0.07;
	coll.frac_x = x - coll.map_x;
	coll.frac_y = y - coll.map_y;
	if ((coll.frac_x > 1 - threshold || coll.frac_x < threshold)
		&& (coll.frac_y > 1 - threshold || coll.frac_y < threshold))
	{
		if (coll.frac_x > 1 - threshold)
			coll.adj_x = 1;
		else
			coll.adj_x = -1;
		if (coll.frac_y > 1 - threshold)
			coll.adj_y = 1;
		else
			coll.adj_y = -1;
		if (coll.map_x + coll.adj_x >= 0 && coll.map_x + coll.adj_x < WIDTH
			&& coll.map_y + coll.adj_y >= 0 && coll.map_y + coll.adj_y < HEIGHT)
		{
			if (data->tab[coll.map_y][coll.map_x + coll.adj_x] == '1'
				&& data->tab[coll.map_y + coll.adj_y][coll.map_x] == '1')
				return (1);
		}
	}
	return (0);
}

static int	map_collision(t_data *data, double new_x, double new_y)
{
	t_collision	coll;

	coll.map_x = (int)floor(new_x);
	coll.map_y = (int)floor(new_y);
	if (coll.map_x < 0 || coll.map_x >= WIDTH || coll.map_y < 0
		|| coll.map_y >= HEIGHT || data->tab[coll.map_y][coll.map_x] == '1')
		return (1);
	if (corner_coll(data, coll, new_x, new_y))
		return (1);
	return (0);
}

static void	ft_player_move(t_data *data, double step_x, double step_y)
{
	double	newpos_x;
	double	newpos_y;

	newpos_x = data->player->pos_x + step_x;
	newpos_y = data->player->pos_y + step_y;
	if (map_collision(data, newpos_x, newpos_y))
	{
		if (!map_collision(data, data->player->pos_x, newpos_y))
			data->player->pos_y = newpos_y;
		else if (!map_collision(data, newpos_x, data->player->pos_y))
			data->player->pos_x = newpos_x;
	}
	else
	{
		data->player->pos_x = newpos_x;
		data->player->pos_y = newpos_y;
	}
}

static void	ft_player_rotate(t_data *data, int factor)
{
	data->player->olddir_x = data->player->dir_x;
	data->player->dir_x = data->player->dir_x * cos(ROT_SPEED * factor)
		- data->player->dir_y * sin(ROT_SPEED * factor);
	data->player->dir_y = data->player->olddir_x * sin(ROT_SPEED * factor)
		+ data->player->dir_y * cos(ROT_SPEED * factor);
	data->player->old_plane_x = data->player->plane_x;
	data->player->plane_x = data->player->plane_x * cos(ROT_SPEED * factor)
		- data->player->plane_y * sin(ROT_SPEED * factor);
	data->player->plane_y = data->player->old_plane_x * sin(ROT_SPEED * factor)
		+ data->player->plane_y * cos(ROT_SPEED * factor);
}

void	update_player_position(int keycode, t_data *data)
{
	data->player->move_step_x = data->player->dir_x * MOVE_SPEED;
	data->player->move_step_y = data->player->dir_y * MOVE_SPEED;
	data->player->strafe_step_x = data->player->plane_x * MOVE_SPEED;
	data->player->strafe_step_y = data->player->plane_y * MOVE_SPEED;
	if (keycode == KEY_W)
		ft_player_move(data, data->player->move_step_x, \
	data->player->move_step_y);
	else if (keycode == KEY_S)
		ft_player_move(data, -data->player->move_step_x, \
	-data->player->move_step_y);
	else if (keycode == KEY_A)
		ft_player_move(data, -data->player->strafe_step_x, \
	-data->player->strafe_step_y);
	else if (keycode == KEY_D)
		ft_player_move(data, data->player->strafe_step_x, \
	data->player->strafe_step_y);
	else if (keycode == KEY_LEFT)
		ft_player_rotate(data, -1);
	else if (keycode == KEY_RIGHT)
		ft_player_rotate(data, 1);
}
