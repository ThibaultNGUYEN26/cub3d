/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_window.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 12:25:29 by thibault          #+#    #+#             */
/*   Updated: 2024/01/05 23:25:00 by thibault         ###   ########.fr       */
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

static int	ft_key_hook(int key, void *param)
{
	if (key == ESC)
		ft_close_window(param);
	return (0);
}

/* static int	ft_game_update(void *param)
{
	
} */

void	setup_mlx(t_data *data, t_player *player)
{
	void	*mlx;
	void	*window;

	mlx = mlx_init();
	window = mlx_new_window(mlx, WIDTH, HEIGHT, "CUB3D");
	mlx_hook(window, 17, 0, ft_close_window, NULL);
	mlx_hook(window, 2, 1L<<0, ft_key_hook, NULL);
	// mlx_loop_hook(mlx, ft_game_update, player);
	ft_draw_minimap(mlx, window, data, player);
	mlx_loop(mlx);
}
