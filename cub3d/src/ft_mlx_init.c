/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 21:28:33 by thibault          #+#    #+#             */
/*   Updated: 2024/01/25 22:25:29 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	ft_close_window(t_data *data)
{
	(void)data;
	printf(GREEN "[INFO] " YELLOW "Closing program...\n" EOC);
	exit(0);
	return (0);
}

static void	ft_free_utils(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_lines)
		free(data->tab[i]);
	free(data->tab);
	free(data->player);
	free(data);
}

static void	free_textures(t_data *data)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (data->texture[i].img_ptr != NULL)
		{
			mlx_destroy_image(data->mlx, data->texture[i].img_ptr);
			data->texture[i].img_ptr = NULL;
			data->texture[i].data = NULL;
		}
	}
	free(data->texture->t_north);
	free(data->texture->t_south);
	free(data->texture->t_east);
	free(data->texture->t_west);
}

static int	ft_key_hook(int key, t_data *data)
{
	if (key == ESC)
	{
		mlx_destroy_image(data->mlx, data->minimap_img);
		mlx_destroy_image(data->mlx, data->img);
		free_textures(data);
		ft_free_utils(data);
		printf(GREEN "[INFO] " YELLOW "Closing program...\n" EOC);
		exit(0);
	}
	if (key == KEY_W)
		data->forward = 1;
	if (key == KEY_S)
		data->backward = 1;
	if (key == KEY_A)
		data->left = 1;
	if (key == KEY_D)
		data->right = 1;
	if (key == KEY_LEFT)
		data->turn_left = 1;
	if (key == KEY_RIGHT)
		data->turn_right = 1;
	return (0);
}

static int	ft_key_release_hook(int key, t_data *data)
{
	if (key == KEY_W)
		data->forward = 0;
	if (key == KEY_S)
		data->backward = 0;
	if (key == KEY_A)
		data->left = 0;
	if (key == KEY_D)
		data->right = 0;
	if (key == KEY_LEFT)
		data->turn_left = 0;
	if (key == KEY_RIGHT)
		data->turn_right = 0;
	return (0);
}

int	update_player_state(t_data *data)
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
	if (data->forward || data->backward || data->left || data->right || data->turn_left || data->turn_right)
	{
		perform_raycasting(data);
		mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
		draw_minimap(data);
		mlx_put_image_to_window(data->mlx, data->win, data->minimap_img,
			data->minimap_x, data->minimap_y);
	}
	return (0);
}

/* int	update_player_state(t_data *data)
{
	int	action_performed;

	action_performed = 0;
	if (data->forward)
	{
		update_player_position(KEY_W, data);
		action_performed = 1;
	}
	if (data->backward)
	{
		update_player_position(KEY_S, data);
		action_performed = 1;
	}
	if (data->left)
	{
		update_player_position(KEY_A, data);
		action_performed = 1;
	}
	if (data->right)
	{
		update_player_position(KEY_D, data);
		action_performed = 1;
	}
	if (data->turn_left)
	{
		update_player_position(KEY_LEFT, data);
		action_performed = 1;
	}
	if (data->turn_right)
	{
		update_player_position(KEY_RIGHT, data);
		action_performed = 1;
	}
	if (action_performed)
	{
		perform_raycasting(data);
		mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
		draw_minimap(data);
		mlx_put_image_to_window(data->mlx, data->win, data->minimap_img,
			data->minimap_x, data->minimap_y);
	}
	return (0);
} */

int	mouse_move(int x, int y, t_data *data)
{
	int		delta_x;
	double	rotation_angle;
	double	olddir_x;
	double	old_plane_x;
	double	sensitivity;

	(void)y;
	delta_x = x - data->prev_mouse_x;
	sensitivity = 0.005;
	rotation_angle = delta_x * sensitivity;
	olddir_x = data->player->dir_x;
	old_plane_x = data->player->plane_x;
	data->player->dir_x = olddir_x * cos(rotation_angle) - data->player->dir_y
		* sin(rotation_angle);
	data->player->dir_y = olddir_x * sin(rotation_angle) + data->player->dir_y
		* cos(rotation_angle);
	data->player->plane_x = old_plane_x * cos(rotation_angle)
		- data->player->plane_y * sin(rotation_angle);
	data->player->plane_y = old_plane_x * sin(rotation_angle)
		+ data->player->plane_y * cos(rotation_angle);
	data->prev_mouse_x = x;
	perform_raycasting(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	draw_minimap(data);
	mlx_put_image_to_window(data->mlx, data->win, data->minimap_img,
		data->minimap_x, data->minimap_y);
	return (0);
}

void	load_texture(t_data *data, int textureIndex, char *filePath)
{
	data->texture[textureIndex].img_ptr = mlx_xpm_file_to_image(data->mlx,
			filePath, &data->texture[textureIndex].width,
			&data->texture[textureIndex].height);
	if (data->texture[textureIndex].img_ptr == NULL)
	{
		printf("Texture error\n");
		exit(EXIT_FAILURE);
	}
	data->texture[textureIndex].data = (int *)mlx_get_data_addr(data->texture[textureIndex].img_ptr,
			&data->texture[textureIndex].bpp,
			&data->texture[textureIndex].size_line,
			&data->texture[textureIndex].endian);
}

void	ft_mlx_init(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "CUB3D");
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	data->minimap_img = NULL;
	data->prev_mouse_x = -1;
	data->forward = 0;
	data->backward = 0;
	data->left = 0;
	data->right = 0;
	data->turn_left = 0;
	data->turn_right = 0;
	load_texture(data, TEXTURE_NORTH, data->texture->t_north);
	load_texture(data, TEXTURE_SOUTH, data->texture->t_south);
	load_texture(data, TEXTURE_WEST, data->texture->t_west);
	load_texture(data, TEXTURE_EAST, data->texture->t_east);
	mlx_hook(data->win, 17, 0, ft_close_window, NULL);
	mlx_hook(data->win, 2, 1L << 0, ft_key_hook, data);
	mlx_hook(data->win, 3, 1L << 1, ft_key_release_hook, data);
	mlx_hook(data->win, 6, 1L << 6, mouse_move, data);
	mlx_loop_hook(data->mlx, update_player_state, data);
	ft_player_init(data);
}
