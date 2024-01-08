/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_minimap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchbouki <rchbouki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 14:56:29 by thibault          #+#    #+#             */
/*   Updated: 2024/01/08 19:56:18 by rchbouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void ft_player_direction(t_data *data, char dir)
{
	if (dir == 'N')
	{
		data->player->dirX = 0;
		data->player->dirY = -1;
	}
	else if (dir == 'S')
	{
		data->player->dirX = 0;
		data->player->dirY = 1;
	}
	else if (dir == 'W')
	{
		data->player->dirX = -1;
		data->player->dirY = 0;
	}
	else
	{
		data->player->dirX = 1;
		data->player->dirY = 0;
	}
}

void	ft_player_init(t_data *data)
{
	int			i;
	int			j;

	data->player = malloc(sizeof(t_player) * 1);
	if (!data->player)
		return ;
	data->player->oldDirX = 0;
	data->player->oldDirY = 0;
	data->player->rotSpeed = 0.05;
	i = -1;
	while (++i < data->nb_lines)
	{
		j = -1;
		while (++j < data->longest_line)
		{
			if (data->tab[i][j] == 'N' || data->tab[i][j] == 'S' || data->tab[i][j] == 'W' || data->tab[i][j] == 'E')
			{
				ft_player_direction(data, data->tab[i][j]);
				data->player->posX = j;
				data->player->posY = i;
				return ;
			}
		}
	}
}

void handle_key_event(int key, t_data *data)
{
	float	moveX;
	float	moveY;
	int		newPosX;
	int		newPosY;

	moveX = 0;
	moveY = 0;
	if (key == KEY_W)
	{
		moveX += data->player->dirX * MOVE_SPEED;
		moveY += data->player->dirY * MOVE_SPEED;
	}
	else if (key == KEY_S)
	{
		moveX -= data->player->dirX * MOVE_SPEED;
		moveY -= data->player->dirY * MOVE_SPEED;
	}
	else if (key == KEY_D)
	{
		moveX -= data->player->dirY * MOVE_SPEED;
		moveY += data->player->dirX * MOVE_SPEED;
	}
	else if (key == KEY_A)
	{
		moveX += data->player->dirY * MOVE_SPEED;
		moveY -= data->player->dirX * MOVE_SPEED;
	}
	newPosX = (int)(data->player->posX + moveX);
	newPosY = (int)(data->player->posY + moveY);
	if (newPosX >= 0 && newPosX < data->longest_line && newPosY >= 0 && newPosY < data->nb_lines)
	{
        if (data->tab[newPosY][newPosX] != '1')
		{
            data->player->posX += moveX;
            data->player->posY += moveY;
        }
    }
}

void ft_rotate_player(int key, t_player *player)
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

static void mlx_pixel_put_line(t_data *data, int x0, int y0, int x1, int y1, int color)
{
	int dx = abs(x1 - x0);
	int sx = x0 < x1 ? 1 : -1;
	int dy = -abs(y1 - y0);
	int sy = y0 < y1 ? 1 : -1;
	int err = dx + dy; /* error value e_xy */
	while (1) {
		ft_mlx_put_pixel(x0, y0, color, data);
		// mlx_pixel_put(mlx, win, x0, y0, color);
		if (x0 == x1 && y0 == y1) break;
		int e2 = 2 * err;
		if (e2 >= dy) { /* e_xy+e_x > 0 */
			err += dy;
			x0 += sx;
		}
		if (e2 <= dx) { /* e_xy+e_y < 0 */
			err += dx;
			y0 += sy;
		}
	}
}

static void ft_draw_fov_line(t_data *data, int length, float fov_angle, int num_rays) {
    float angle_step = fov_angle / (num_rays - 1);
    float start_angle = -fov_angle / 2; // Start at the left edge of the FOV

    for (int i = 0; i < num_rays; ++i) {
        float current_angle = start_angle + i * angle_step;
        float rayDirX = data->player->dirX * cos(current_angle) - data->player->dirY * sin(current_angle);
        float rayDirY = data->player->dirX * sin(current_angle) + data->player->dirY * cos(current_angle);

        // Initialize ray end point with player's position
        float rayPosX = data->player->posX;
        float rayPosY = data->player->posY;

        for (int j = 0; j < length; ++j) {
            int mapX = (int)(rayPosX);
            int mapY = (int)(rayPosY);

            // Check for collision with a wall
            if (mapX < 0 || mapX >= data->longest_line || mapY < 0 || mapY >= data->nb_lines || data->tab[mapY][mapX] == '1') {
                break; // Stop drawing this ray because we've hit a wall or are out of bounds
            }

            // Move the ray end point one step further
            rayPosX += rayDirX;
            rayPosY += rayDirY;
        }

        // Draw the line from the player to the final ray position
        mlx_pixel_put_line(data, data->player->posX * SCALE + SCALE / 2, data->player->posY * SCALE + SCALE / 2, (int)rayPosX * SCALE + SCALE / 2, (int)rayPosY * SCALE + SCALE / 2, 0xFF0000); // Red color for the rays
    }
}

void ft_minimap(t_data *data)
{
	int	color;
	int	i;
	int	j;

	color = 0x000000;
	i = -1;
	while (++i < data->nb_lines)
	{
		j = -1;
		while (++j < data->longest_line)
		{
			if (data->tab[i][j] == '1')
				color = 0x404040;
			else
				color = 0xFFFFFF;
			for (int si = 0; si < SCALE; si++)
            {
                for (int sj = 0; sj < SCALE; sj++)
					ft_mlx_put_pixel(j * SCALE + sj, i * SCALE + si, color, data);
			}
		}
	}
}

void draw_circle(t_data *data, int centerX, int centerY, int radius, int color) {
	centerX *= SCALE;
    centerY *= SCALE;
    radius *= SCALE / 2;
    for (int y = -radius; y <= radius; y++) {
        for (int x = -radius; x <= radius; x++) {
            if (x * x + y * y <= radius * radius) {
                ft_mlx_put_pixel(centerX + x + SCALE / 2, centerY + y + SCALE / 2, color, data);
            }
        }
    }
}

void	ft_draw_minimap(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img);
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
	ft_minimap(data);
	draw_circle(data, data->player->posX, data->player->posY, 1, 0xFF0000);
    ft_draw_fov_line(data, FOV_LENGTH, 60.0f * (M_PI / 180.0f), 20);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}
