/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_minimap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 14:56:29 by thibault          #+#    #+#             */
/*   Updated: 2024/01/06 17:05:55 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_player *ft_player_init(void)
{
	t_player *player;

	player = malloc(sizeof(t_player) * 1);
	if (!player)
		return (NULL);
	player->posX = 0;
	player->posY = 0;
	player->dirX = 0;
	player->dirX = 0;
	player->oldDirX = 0;
	player->oldDirY = 0;
	player->rotSpeed = 0.05;
	return (player);`
}

static void ft_player_direction(t_player *player, char dir)
{
	if (dir == 'N')
	{
		player->dirX = 0;
		player->dirY = -1;
	}
	else if (dir == 'S')
	{
		player->dirX = 0;
		player->dirY = 1;
	}
	else if (dir == 'W')
	{
		player->dirX = -1;
		player->dirY = 0;
	}
	else
	{
		player->dirX = 1;
		player->dirY = 0;
	}
}

void handle_key_event(int key, t_player *player)
{
	if (key == KEY_W)
	{
		player->posX += player->dirX * MOVE_SPEED;
		player->posY += player->dirY * MOVE_SPEED;
	}
	else if (key == KEY_S)
	{
		player->posX -= player->dirX * MOVE_SPEED;
		player->posY -= player->dirY * MOVE_SPEED;
	}
	else if (key == KEY_A)
	{
		player->posX -= player->dirX * MOVE_SPEED;
		player->posY += player->dirY * MOVE_SPEED;
	}
	else if (key == KEY_D)
	{
		player->posX += player->dirX * MOVE_SPEED;
		player->posY -= player->dirY * MOVE_SPEED;
	}
}

static void ft_rotate_player(t_player *player)
{
	if (key == KEY_LEFT)
	{
		player->oldDirX = player->dirX;
		player->dirX = player->dirX * cos(-player->rotSpeed) - player->dirY * sin(-player->rotSpeed);
		player->dirY = player->oldDirX * sin(-player->rotSpeed) + player->dirY * cos(-player->rotSpeed);
	}
	else if (key == KEY_RIGHT)
	{
		player->oldDirX = player->dirX;
		player->dirX = player->dirX * cos(player->rotSpeed) - player->dirY * sin(player->rotSpeed);
		player->dirY = player->oldDirX * sin(player->rotSpeed) + player->dirY * cos(player->rotSpeed);
	}
}

static void	ft_minimap(void *mlx, void *window, t_data *data, t_player *player)
{
	int	color;
	int	i;
	int	j;
	int	dx;
	int	dy;

	i = -1;
	while (++i < data->nb_lines)
	{
		for (j = 0; j < data->longest_line; j++) {
			if (data->tab[i][j] == '1')
				color = 0x404040;
			else
				color = 0xFFFFFF;

			for (dy = 0; dy < 8; dy++) {
				for (dx = 0; dx < 8; dx++) {
					mlx_pixel_put(mlx, window, j * 8 + dx, i * 8 + dy, color);
				}
			}
		}
	}
	int playerX = (int)(player->posX * 8);
	int playerY = (int)(player->posY * 8);
	for (dy = 0; dy < 8; dy++) {
		for (dx = 0; dx < 8; dx++) {
			mlx_pixel_put(mlx, window, playerX + dx, playerY + dy, 0xFF0000);
		}
	}
}


void	ft_draw_minimap(void *mlx, void *window, t_data *data, t_player *player)
{
	ft_minimap(mlx, window, data, player);
}
