/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 21:28:33 by thibault          #+#    #+#             */
/*   Updated: 2024/01/24 18:21:22 by thibault         ###   ########.fr       */
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
		// Assuming there are 4 textures
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
	if (key == KEY_W || key == KEY_S || key == KEY_A || key == KEY_D
		|| key == KEY_LEFT || key == KEY_RIGHT)
	{
		// Redraw the scene with the updated player position
		update_player_position(key, data);
		perform_raycasting(data);
		mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
		draw_minimap(data);
		mlx_put_image_to_window(data->mlx, data->win, data->minimap_img,
			data->minimap_x, data->minimap_y);
	}
	return (0);
}

int	mouse_move(int x, int y, t_data *data)
{
	int		delta_x;
	double	rotation_angle;
	double	olddir_x;
	double	old_plane_x;

	(void)y;
	// Calculate the mouse movement delta
	delta_x = x - data->prev_mouse_x;
	// Apply rotation based on mouse movement
	rotation_angle = delta_x * 0.005;
	// Update the player's view direction vectors
	olddir_x = data->player->dir_x;
	old_plane_x = data->player->planeX;
	data->player->dir_x = olddir_x * cos(rotation_angle) - data->player->dir_y
		* sin(rotation_angle);
	data->player->dir_y = olddir_x * sin(rotation_angle) + data->player->dir_y
		* cos(rotation_angle);
	data->player->planeX = old_plane_x * cos(rotation_angle) - data->player->planeY
		* sin(rotation_angle);
	data->player->planeY = old_plane_x * sin(rotation_angle) + data->player->planeY
		* cos(rotation_angle);
	// Save the new mouse position for the next event
	data->prev_mouse_x = x;
	// Redraw the scene with the updated view direction
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
		// Handle error
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
	load_texture(data, TEXTURE_NORTH, data->texture->t_north);
	load_texture(data, TEXTURE_SOUTH, data->texture->t_south);
	load_texture(data, TEXTURE_WEST, data->texture->t_west);
	load_texture(data, TEXTURE_EAST, data->texture->t_east);
	mlx_hook(data->win, 17, 0, ft_close_window, NULL);
	mlx_hook(data->win, 2, 1L << 0, ft_key_hook, data);
	// mlx_hook(data->win, 6, 1L<<6, mouse_move, data);
	ft_player_init(data);
}
