/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_window.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchbouki <rchbouki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 12:25:29 by thibault          #+#    #+#             */
/*   Updated: 2024/01/08 19:57:14 by rchbouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	ft_close_window(void *param)
{
	(void)param;
	printf(GREEN "[INFO] " YELLOW "Closing program...\n" EOC);
	exit(0);
	return (0);
}

static int	ft_key_hook(int key, t_data *data)
{
	if (key == ESC)
	{
		mlx_destroy_image(data->mlx, data->img);
		ft_free_tab(data);
		free(data->player);
		free(data);
		data = NULL;
		ft_close_window(data);
	}
	return (0);
}

void	ft_mlx_put_pixel(int x, int y, int color, t_data *data)
{
    char *dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

static int ft_game_update(int key, void *param)
{
    t_data *data;
	
	data = (t_data *)param;
    data->key = key;
    handle_key_event(data->key, data);
    ft_rotate_player(data->key, data->player);
    ft_draw_minimap(data);
    return (0);
}

void	setup_mlx(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "CUB3D");
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
	ft_draw_minimap(data);
	mlx_hook(data->win, 17, 0, ft_close_window, NULL);
	mlx_hook(data->win, 2, 1L<<0, ft_key_hook, data);
	mlx_hook(data->win, 3, 1L<<1, ft_game_update, data);
	mlx_loop(data->mlx);
}
