/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_window.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchbouki <rchbouki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 12:25:29 by thibault          #+#    #+#             */
/*   Updated: 2024/01/06 00:13:04 by rchbouki         ###   ########.fr       */
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
		ft_free_tab(data);
		free(data->player);
		free(data);
		data = NULL;
		ft_close_window(data);
	}
	return (0);
}

/* static int	ft_game_update(void *param)
{
	
} */

void	setup_mlx(t_data *data)
{
	void	*mlx;
	void	*window;

	mlx = mlx_init();
	window = mlx_new_window(mlx, WIDTH, HEIGHT, "CUB3D");
	mlx_hook(window, 17, 0, ft_close_window, NULL);
	mlx_hook(window, 2, 1L<<0, ft_key_hook, data);
	// mlx_loop_hook(mlx, ft_game_update, player);
	ft_draw_minimap(mlx, window, data);
	mlx_loop(mlx);
}
