/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 21:28:33 by thibault          #+#    #+#             */
/*   Updated: 2024/01/20 20:19:40 by thibault         ###   ########.fr       */
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

void freeTextures(t_data *data) {
    for (int i = 0; i < 4; i++) { // Assuming there are 4 textures
        if (data->texture[i].img_ptr != NULL) {
            mlx_destroy_image(data->mlx, data->texture[i].img_ptr);
            data->texture[i].img_ptr = NULL;
            data->texture[i].data = NULL;
        }
    }
}

static int	ft_key_hook(int key, t_data *data)
{
	if (key == ESC)
	{
        mlx_destroy_image(data->mlx, data->minimap_img);
		mlx_destroy_image(data->mlx, data->img);
		ft_free_tab(data);
		free(data->player);
        freeTextures(data);
		free(data);
		printf(GREEN "[INFO] " YELLOW "Closing program...\n" EOC);
		exit(0);
	}
	if (key == KEY_W || key == KEY_S || key == KEY_A || key == KEY_D || key == KEY_LEFT || key == KEY_RIGHT)
    {
        // Redraw the scene with the updated player position
        updatePlayerPosition(key, data);
        performRaycasting(data);
        mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
		draw_minimap(data);
		mlx_put_image_to_window(data->mlx, data->win, data->minimap_img, data->minimap_x, data->minimap_y);
    }
	return (0);
}

int mouse_move(int x, int y, t_data *data) {
	(void)y;
    // Calculate the mouse movement delta
    int deltaX = x - data->prev_mouse_x;

    // Apply rotation based on mouse movement
    double rotationAngle = deltaX * 0.005;

    // Update the player's view direction vectors
    double oldDirX = data->player->dirX;
    double oldPlaneX = data->player->planeX;
    data->player->dirX = oldDirX * cos(rotationAngle) - data->player->dirY * sin(rotationAngle);
    data->player->dirY = oldDirX * sin(rotationAngle) + data->player->dirY * cos(rotationAngle);
    data->player->planeX = oldPlaneX * cos(rotationAngle) - data->player->planeY * sin(rotationAngle);
    data->player->planeY = oldPlaneX * sin(rotationAngle) + data->player->planeY * cos(rotationAngle);

    // Save the new mouse position for the next event
    data->prev_mouse_x = x;

    // Redraw the scene with the updated view direction
    performRaycasting(data);
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
    draw_minimap(data);
    mlx_put_image_to_window(data->mlx, data->win, data->minimap_img, data->minimap_x, data->minimap_y);

    return 0;
}

void loadTexture(t_data *data, int textureIndex, char *filePath) {
    data->texture[textureIndex].img_ptr = mlx_xpm_file_to_image(data->mlx, filePath, 
                                                                &data->texture[textureIndex].width, 
                                                                &data->texture[textureIndex].height);
    if (data->texture[textureIndex].img_ptr == NULL) {
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
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
	data->minimap_img = NULL;
	data->prev_mouse_x = -1;
    /* data->texture->t_north = "./textures/42.xpm";
    data->texture->t_south = "./textures/peach.xpm";
    data->texture->t_west = "./textures/luigi.xpm";
    data->texture->t_east = "./textures/bowser.xpm"; */
    loadTexture(data, TEXTURE_NORTH, data->texture->t_north);
    loadTexture(data, TEXTURE_SOUTH, data->texture->t_south);
    loadTexture(data, TEXTURE_WEST, data->texture->t_west);
    loadTexture(data, TEXTURE_EAST, data->texture->t_east);
	mlx_hook(data->win, 17, 0, ft_close_window, NULL);
	mlx_hook(data->win, 2, 1L<<0, ft_key_hook, data);
	// mlx_hook(data->win, 6, 1L<<6, mouse_move, data);
	ft_player_init(data);
}