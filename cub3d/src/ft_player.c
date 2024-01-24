/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_player.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 23:34:14 by thibault          #+#    #+#             */
/*   Updated: 2024/01/24 18:30:34 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	ft_player_direction(t_data *data, char dir)
{
	double	fov;

	fov = 60.0 * M_PI / 180.0;
	if (dir == 'N')
	{
		data->player->dir_x = 0;
		data->player->dir_y = -1;
		data->player->planeX = tan(fov / 2.0);
		data->player->planeY = 0;
	}
	else if (dir == 'S')
	{
		data->player->dir_x = 0;
		data->player->dir_y = 1;
		data->player->planeX = -tan(fov / 2.0);
		data->player->planeY = 0;
	}
	else if (dir == 'W')
	{
		data->player->dir_x = -1;
		data->player->dir_y = 0;
		data->player->planeX = 0;
		data->player->planeY = -tan(fov / 2.0);
	}
	else
	{
		data->player->dir_x = 1;
		data->player->dir_y = 0;
		data->player->planeX = 0;
		data->player->planeY = tan(fov / 2.0);
	}
}

void	ft_player_init(t_data *data)
{
	int	i;
	int	j;

	data->player = malloc(sizeof(t_player) * 1);
	if (!data->player)
		return ;
	i = -1;
	while (++i < data->nb_lines)
	{
		j = -1;
		while (data->tab[i][++j])
		{
			if (data->tab[i][j] == 'N' || data->tab[i][j] == 'S'
				|| data->tab[i][j] == 'W' || data->tab[i][j] == 'E')
			{
				ft_player_direction(data, data->tab[i][j]);
				data->player->pos_x = (double)j + 0.5;
				data->player->pos_y = (double)i + 0.5;
				return ;
			}
		}
	}
}

static int	map_collision(t_data *data, double newX, double newY)
{
	int		map_x;
	int		map_y;
	double	frac_x;
	double	frac_y;
	int		adj_x;
	int		adj_y;
	double	threshold;

	map_x = (int)floor(newX);
	map_y = (int)floor(newY);
	if (map_x < 0 || map_x >= WIDTH || map_y < 0 || map_y >= HEIGHT)
		return (1);
	if (data->tab[map_y][map_x] == '1')
		return (1);
	threshold = 0.07;
	frac_x = newX - map_x;
	frac_y = newY - map_y;
	if ((frac_x > 1 - threshold || frac_x < threshold) && (frac_y > 1
			- threshold || frac_y < threshold))
	{
		if (frac_x > 1 - threshold)
			adj_x = 1;
		else
			adj_x = -1;
		if (frac_y > 1 - threshold)
			adj_y = 1;
		else
			adj_y = -1;
		if (map_x + adj_x >= 0 && map_x + adj_x < WIDTH && map_y + adj_y >= 0
			&& map_y + adj_y < HEIGHT)
		{
			if (data->tab[map_y][map_x + adj_x] == '1' && data->tab[map_y
				+ adj_y][map_x] == '1')
			{
				return (1);
			}
		}
	}
	return (0);
}

void	update_player_position(int keycode, t_data *data)
{
	double	strafe_step_x;
	double	strafe_step_y;
	double	olddir_x;
	double	old_plane_x;
	double	move_step_x;
	double	move_step_y;
	double	newpos_x;
	double	newpos_y;

	move_step_x = data->player->dir_x * MOVE_SPEED;
	move_step_y = data->player->dir_y * MOVE_SPEED;
	strafe_step_x = data->player->planeX * MOVE_SPEED;
	strafe_step_y = data->player->planeY * MOVE_SPEED;
	if (keycode == KEY_W || keycode == KEY_S)
	{
		if (keycode == KEY_S)
		{
			move_step_x = -move_step_x;
			move_step_y = -move_step_y;
		}
		newpos_x = data->player->pos_x + move_step_x;
		newpos_y = data->player->pos_y + move_step_y;
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
	if (keycode == KEY_A || keycode == KEY_D)
	{
		if (keycode == KEY_A)
		{
			strafe_step_x = -strafe_step_x;
			strafe_step_y = -strafe_step_y;
		}
		newpos_x = data->player->pos_x + strafe_step_x;
		newpos_y = data->player->pos_y + strafe_step_y;
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
	if (keycode == KEY_LEFT)
	{
		olddir_x = data->player->dir_x;
		data->player->dir_x = data->player->dir_x * cos(-ROT_SPEED)
			- data->player->dir_y * sin(-ROT_SPEED);
		data->player->dir_y = olddir_x * sin(-ROT_SPEED) + data->player->dir_y
			* cos(-ROT_SPEED);
		old_plane_x = data->player->planeX;
		data->player->planeX = data->player->planeX * cos(-ROT_SPEED)
			- data->player->planeY * sin(-ROT_SPEED);
		data->player->planeY = old_plane_x * sin(-ROT_SPEED)
			+ data->player->planeY * cos(-ROT_SPEED);
	}
	if (keycode == KEY_RIGHT)
	{
		olddir_x = data->player->dir_x;
		data->player->dir_x = data->player->dir_x * cos(ROT_SPEED)
			- data->player->dir_y * sin(ROT_SPEED);
		data->player->dir_y = olddir_x * sin(ROT_SPEED) + data->player->dir_y
			* cos(ROT_SPEED);
		old_plane_x = data->player->planeX;
		data->player->planeX = data->player->planeX * cos(ROT_SPEED)
			- data->player->planeY * sin(ROT_SPEED);
		data->player->planeY = old_plane_x * sin(ROT_SPEED)
			+ data->player->planeY * cos(ROT_SPEED);
	}
}
