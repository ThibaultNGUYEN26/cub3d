/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 21:28:33 by thibault          #+#    #+#             */
/*   Updated: 2024/01/26 17:081 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	update_player_state(t_data *data)
{
	if (data->forward)
		update_player_position(KEY_W, data);
	if (data->backward)
		update_player_position(KEY_S, data);
	if (data->left)
		update_player_position(KEY_A, data);
	if (data->right)
		update_player_position(KEY_D, data);
	if (data->turn_left)
		update_player_position(KEY_LEFT, data);
	if (data->turn_right)
		update_player_position(KEY_RIGHT, data);
	if (data->forward || data->backward || data->left || data->right
		|| data->turn_left || data->turn_right)
		ft_regenerate(data);
	return (0);
}

static void	ft_mouse_init(int *delta_x, int x, double *sense, t_data *data)
{
	*delta_x = x - data->prev_mouse_x;
	*sense = 0.005;
	data->delta_accumulator += *delta_x;
}

static int	mouse_move(int x, int y, t_data *data)
{
	int			delta_x;
	double		rotation_angle;
	double		sensitivity;

	(void)y;
	ft_mouse_init(&delta_x, x, &sensitivity, data);
	if (++data->frame_count >= 5)
	{
		rotation_angle = data->delta_accumulator * sensitivity;
		data->player->olddir_x = data->player->dir_x;
		data->player->old_plane_x = data->player->plane_x;
		data->player->dir_x = data->player->olddir_x * cos(rotation_angle)
			- data->player->dir_y * sin(rotation_angle);
		data->player->dir_y = data->player->olddir_x * sin(rotation_angle)
			+ data->player->dir_y * cos(rotation_angle);
		data->player->plane_x = data->player->old_plane_x * cos(rotation_angle)
			- data->player->plane_y * sin(rotation_angle);
		data->player->plane_y = data->player->old_plane_x * sin(rotation_angle)
			+ data->player->plane_y * cos(rotation_angle);
		data->delta_accumulator = 0;
		data->frame_count = 0;
		ft_regenerate(data);
	}
	data->prev_mouse_x = x;
	return (0);
}

static void	ft_var_init(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "CUB3D");
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	data->minimap_img = NULL;
	data->forward = 0;
	data->backward = 0;
	data->left = 0;
	data->right = 0;
	data->turn_left = 0;
	data->turn_right = 0;
	data->delta_accumulator = 0;
	data->frame_count = 0;
}

void	ft_mlx_init(t_data *data)
{
	int	x;
	int	y;

	ft_var_init(data);
	mlx_mouse_get_pos(data->mlx, data->win, &x, &y);
	data->prev_mouse_x = x;
	load_texture(data, TEXTURE_NORTH, data->texture->t_north);
	load_texture(data, TEXTURE_SOUTH, data->texture->t_south);
	load_texture(data, TEXTURE_WEST, data->texture->t_west);
	load_texture(data, TEXTURE_EAST, data->texture->t_east);
	mlx_hook(data->win, 17, 0, ft_close_window, NULL);
	mlx_hook(data->win, 2, 1L << 0, ft_key_hook, data);
	mlx_hook(data->win, 3, 1L << 1, ft_key_release_hook, data);
	if (data->bonus)
		mlx_hook(data->win, 6, 1L << 6, mouse_move, data);
	mlx_loop_hook(data->mlx, update_player_state, data);
	ft_player_init(data);
}
