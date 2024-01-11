/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 21:28:33 by thibault          #+#    #+#             */
/*   Updated: 2024/01/11 02:00:00 by thibault         ###   ########.fr       */
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

static int	ft_key_hook(int key, t_data *data)
{
	if (key == ESC)
	{
        mlx_destroy_image(data->mlx, data->minimap_img);
		mlx_destroy_image(data->mlx, data->img);
		ft_free_tab(data);
		free(data->player);
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

void	ft_mlx_init(t_data *data)
{
    data->mlx = mlx_init();
    data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "CUB3D");
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
	data->minimap_img = NULL;
	mlx_hook(data->win, 17, 0, ft_close_window, NULL);
	mlx_hook(data->win, 2, 1L<<0, ft_key_hook, data);
	ft_player_init(data);
}