/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_player.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchbouki <rchbouki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 23:34:14 by thibault          #+#    #+#             */
/*   Updated: 2024/01/23 19:14:48 by rchbouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void ft_player_direction(t_data *data, char dir)
{
    // Set up FOV
    double fov = 60.0 * M_PI / 180.0; // Convert 60 degrees to radians

    if (dir == 'N')
    {
        data->player->dirX = 0;
        data->player->dirY = -1;
        data->player->planeX = tan(fov / 2.0);  // Extend plane along X-axis
        data->player->planeY = 0;
    }
    else if (dir == 'S')
    {
        data->player->dirX = 0;
        data->player->dirY = 1;
        data->player->planeX = -tan(fov / 2.0);  // Extend plane along X-axis
        data->player->planeY = 0;
    }
    else if (dir == 'W')
    {
        data->player->dirX = -1;
        data->player->dirY = 0;
        data->player->planeX = 0;  // Extend plane along Y-axis
        data->player->planeY = -tan(fov / 2.0);
    }
    else // dir == 'E'
    {
        data->player->dirX = 1;
        data->player->dirY = 0;
        data->player->planeX = 0;  // Extend plane along Y-axis
        data->player->planeY = tan(fov / 2.0);
    }
}

void	ft_player_init(t_data *data)
{
	int			i;
	int			j;
	// double		fov_rad;

	data->player = malloc(sizeof(t_player) * 1);
	if (!data->player)
		return ;
	i = -1;
	while (++i < data->nb_lines)
	{
		j = -1;
        while (data->tab[i][++j])
		{
			if (data->tab[i][j] == 'N' || data->tab[i][j] == 'S' || data->tab[i][j] == 'W' || data->tab[i][j] == 'E')
			{
				ft_player_direction(data, data->tab[i][j]);
				data->player->posX = (double)j + 0.5;  // Center the player in the square
            	data->player->posY = (double)i + 0.5;
				// data->player->planeX = data->player->dirY * tan(fov_rad / 2);
				// data->player->planeY = -data->player->dirX * tan(fov_rad / 2);
				return ;
			}
		}
	}
}

static int mapCollision(t_data *data, double newX, double newY)
{
    int mapX = (int)floor(newX); // Convert the new position to map coordinates
    int mapY = (int)floor(newY);

    // Check if the new position is out of bounds
    if (mapX < 0 || mapX >= WIDTH || mapY < 0 || mapY >= HEIGHT)
        return 1; // Collision with out-of-bounds

    // Check if the new position collides with a wall
    if (data->tab[mapY][mapX] == '1')
        return 1; // Collision with a wall

    // Enhanced check for diagonal collision
    double threshold = 0.07; // Adjust this threshold for sensitivity of diagonal collision
    double fracX = newX - mapX;
    double fracY = newY - mapY;

    if ((fracX > 1 - threshold || fracX < threshold) && 
        (fracY > 1 - threshold || fracY < threshold)) {
        // Check adjacent cells for diagonal collision
        int adjX = (fracX > 1 - threshold) ? 1 : -1;
        int adjY = (fracY > 1 - threshold) ? 1 : -1;

        if (mapX + adjX >= 0 && mapX + adjX < WIDTH && 
            mapY + adjY >= 0 && mapY + adjY < HEIGHT) {
            if (data->tab[mapY][mapX + adjX] == '1' && data->tab[mapY + adjY][mapX] == '1') {
                return 1; // Diagonal collision detected
            }
        }
    }

    // If there's no collision, return 0
    return 0;
}

void updatePlayerPosition(int keycode, t_data *data)
{
    double moveStepX, moveStepY, newPosX, newPosY;

    // Calculate the forward and backward movement steps
    moveStepX = data->player->dirX * MOVE_SPEED;
    moveStepY = data->player->dirY * MOVE_SPEED;

    // Calculate the sideways (strafe) movement steps
    double strafeStepX = data->player->planeX * MOVE_SPEED;
    double strafeStepY = data->player->planeY * MOVE_SPEED;

    // Handle forward and backward movement
    if (keycode == KEY_W || keycode == KEY_S) {
        if (keycode == KEY_S) { // Reverse direction if moving backwards
            moveStepX = -moveStepX;
            moveStepY = -moveStepY;
        }

        newPosX = data->player->posX + moveStepX;
        newPosY = data->player->posY + moveStepY;

        // Perform wall sliding if there's a collision
        if (mapCollision(data, newPosX, newPosY)) {
            if (!mapCollision(data, data->player->posX, newPosY)) {
                // Slide along the Y-axis
                data->player->posY = newPosY;
            } else if (!mapCollision(data, newPosX, data->player->posY)) {
                // Slide along the X-axis
                data->player->posX = newPosX;
            }
        } else {
            // No collision, move freely
            data->player->posX = newPosX;
            data->player->posY = newPosY;
        }
    }

    // Handle strafe movement (left and right)
    if (keycode == KEY_A || keycode == KEY_D) {
        if (keycode == KEY_A) { // Reverse direction if strafing left
            strafeStepX = -strafeStepX;
            strafeStepY = -strafeStepY;
        }

        newPosX = data->player->posX + strafeStepX;
        newPosY = data->player->posY + strafeStepY;

        // Perform wall sliding if there's a collision
        if (mapCollision(data, newPosX, newPosY)) {
            if (!mapCollision(data, data->player->posX, newPosY)) {
                // Slide along the Y-axis
                data->player->posY = newPosY;
            } else if (!mapCollision(data, newPosX, data->player->posY)) {
                // Slide along the X-axis
                data->player->posX = newPosX;
            }
        } else {
            // No collision, move freely
            data->player->posX = newPosX;
            data->player->posY = newPosY;
        }
    }

    // Handle keyboard input for rotation (turning)
	if (keycode == KEY_LEFT) { // Rotate left
        double oldDirX = data->player->dirX;
        data->player->dirX = data->player->dirX * cos(-ROT_SPEED) - data->player->dirY * sin(-ROT_SPEED);
        data->player->dirY = oldDirX * sin(-ROT_SPEED) + data->player->dirY * cos(-ROT_SPEED);

        double oldPlaneX = data->player->planeX;
        data->player->planeX = data->player->planeX * cos(-ROT_SPEED) - data->player->planeY * sin(-ROT_SPEED);
        data->player->planeY = oldPlaneX * sin(-ROT_SPEED) + data->player->planeY * cos(-ROT_SPEED);
    }
    if (keycode == KEY_RIGHT) { // Rotate right
        double oldDirX = data->player->dirX;
        data->player->dirX = data->player->dirX * cos(ROT_SPEED) - data->player->dirY * sin(ROT_SPEED);
        data->player->dirY = oldDirX * sin(ROT_SPEED) + data->player->dirY * cos(ROT_SPEED);

        double oldPlaneX = data->player->planeX;
        data->player->planeX = data->player->planeX * cos(ROT_SPEED) - data->player->planeY * sin(ROT_SPEED);
        data->player->planeY = oldPlaneX * sin(ROT_SPEED) + data->player->planeY * cos(ROT_SPEED);
    }
}
