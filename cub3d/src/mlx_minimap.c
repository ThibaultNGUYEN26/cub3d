/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_minimap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 14:56:29 by thibault          #+#    #+#             */
/*   Updated: 2024/01/08 14:28:09 by thibault         ###   ########.fr       */
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

static void ft_draw_fov_line(t_data *data, int length, float fov_angle, int num_rays, int scale_factor) {
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
        mlx_pixel_put_line(data, data->player->posX * scale_factor + scale_factor / 2, data->player->posY * scale_factor + scale_factor / 2, (int)rayPosX * scale_factor + scale_factor / 2, (int)rayPosY * scale_factor + scale_factor / 2, 0xFF0000); // Red color for the rays
    }
}

static void ft_minimap(t_data *data)
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
			ft_mlx_put_pixel(j, i, color, data);
		}
	}
}

static void ft_mlx_put_pixel_scaled(char *addr, int x, int y, int color, int bpp, int line_length) {
    char *dst = addr + (y * line_length + x * (bpp / 8));
    *(unsigned int *)dst = color;
}

static void scale_minimap(t_data *data, int scale_factor) {
    // Create a new image for the scaled minimap
    void *scaled_img = mlx_new_image(data->mlx, WIDTH * scale_factor, HEIGHT * scale_factor);
    int scaled_bpp, scaled_line_length, scaled_endian;
    char *scaled_addr = mlx_get_data_addr(scaled_img, &scaled_bpp, &scaled_line_length, &scaled_endian);

    // Loop through each pixel of the original image and draw a scale_factor x scale_factor square
    // at the corresponding location in the scaled image
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            int original_pixel_index = (y * data->line_length + x * (data->bits_per_pixel / 8));
            int color = ((unsigned char)data->addr[original_pixel_index + 2] << 16) |
                        ((unsigned char)data->addr[original_pixel_index + 1] << 8) |
                        (unsigned char)data->addr[original_pixel_index];

            // Draw a square of scale_factor x scale_factor in the scaled image
            for (int dy = 0; dy < scale_factor; ++dy) {
                for (int dx = 0; dx < scale_factor; ++dx) {
                    int scaled_x = x * scale_factor + dx;
                    int scaled_y = y * scale_factor + dy;
                    ft_mlx_put_pixel_scaled(scaled_addr, scaled_x, scaled_y, color, scaled_bpp, scaled_line_length);
                }
            }
        }
    }

    // Replace the original image with the scaled one
    mlx_destroy_image(data->mlx, data->img); // Clean up the original image
    data->img = scaled_img;
    data->addr = scaled_addr;
    data->bits_per_pixel = scaled_bpp;
    data->line_length = scaled_line_length;
    data->endian = scaled_endian;
}

void clear_buffer(t_data *data)
{
	memset(data->addr, 0, WIDTH * HEIGHT * (data->bits_per_pixel / 8));
}

void draw_player_and_rays(t_data *data, int scale_factor) {
    // Draw the player at 1:1 pixel size at the correct position
    int playerX = data->player->posX * scale_factor;
    int playerY = data->player->posY * scale_factor;
	for (int dy = 0; dy < scale_factor; ++dy) {
        for (int dx = 0; dx < scale_factor; ++dx)
    		ft_mlx_put_pixel(playerX + dx, playerY + dy, 0xFF0000, data); // PLAYER_COLOR is the color you want for the player
	}

    // Draw the rays at 1:1 pixel size
    ft_draw_fov_line(data, FOV_LENGTH, 60.0f * (M_PI / 180.0f), 20, scale_factor); // This function needs to be adapted to draw without scaling
}

void	ft_draw_minimap(t_data *data)
{
	clear_buffer(data);
	ft_minimap(data);
	scale_minimap(data, 8);
	draw_player_and_rays(data, 8);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}
