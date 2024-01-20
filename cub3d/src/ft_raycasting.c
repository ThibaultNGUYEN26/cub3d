/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycasting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 21:37:38 by thibault          #+#    #+#             */
/*   Updated: 2024/01/20 20:26:12 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	drawVerticalLine(t_data *data, int x, int drawStart, int drawEnd,
		int color)
{
	int *img = (int *)data->addr; // Utiliser data->addr
	for (int y = drawStart; y < drawEnd; y++)
	{
		if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
		{
			img[y * WIDTH + x] = color;
		}
	}
}

void performRaycasting(t_data *data) {
    // int color;
	/* data->floor_color = 0x006400; // Dark Green
	data->ceiling_color = 0x87CEFA; // Sky Blue */

    // color = 0x000000;
    for (int x = 0; x < WIDTH; x++) {
        // Calculate position and direction for the ray
        double cameraX = 2 * x / (double)WIDTH - 1; // x-coordinate in camera space
        double rayDirX = data->player->dirX + data->player->planeX * cameraX;
        double rayDirY = data->player->dirY + data->player->planeY * cameraX;

        // Initialize map coordinates with player's position
        int mapX = (int)data->player->posX;
        int mapY = (int)data->player->posY;

        // Length of ray from current position to next x or y-side
        double sideDistX;
        double sideDistY;

        // Length of ray from one x or y-side to next x or y-side
        double deltaDistX = fabs(rayDirX) < 1e-6 ? 1e30 : fabs(1 / rayDirX);
        double deltaDistY = fabs(rayDirY) < 1e-6 ? 1e30 : fabs(1 / rayDirY);

        double perpWallDist;

        // Direction to step in x or y-direction (either +1 or -1)
        int stepX;
        int stepY;

        int hit = 0; // Was there a wall hit?
        int side; // Was a NS or a EW wall hit?

        // Calculate step and initial sideDist
        if (rayDirX < 0) {
            stepX = -1;
            sideDistX = (data->player->posX - mapX) * deltaDistX;
        } else {
            stepX = 1;
            sideDistX = (mapX + 1.0 - data->player->posX) * deltaDistX;
        }
        if (rayDirY < 0) {
            stepY = -1;
            sideDistY = (data->player->posY - mapY) * deltaDistY;
        } else {
            stepY = 1;
            sideDistY = (mapY + 1.0 - data->player->posY) * deltaDistY;
        }

        // Perform DDA
        while (hit == 0) {
            // Jump to next map square, OR in x-direction, OR in y-direction
            if (sideDistX < sideDistY) {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            } else {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            // Check if ray has hit a wall
            if (mapX >= 0 && mapX < WIDTH && mapY >= 0 && mapY < HEIGHT) {
                if (data->tab[mapY][mapX] == '1') { // Note the swap of mapX and mapY
                    hit = 1;
                }
            } else {
                hit = 1; // If out of bounds, treat it as a wall hit to prevent infinite loop
            }
        }

        // Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
        if (side == 0) perpWallDist = (mapX - data->player->posX + (1 - stepX) / 2) / rayDirX;
        else           perpWallDist = (mapY - data->player->posY + (1 - stepY) / 2) / rayDirY;

        // Calculate height of line to draw on screen
        int lineHeight = (int)(HEIGHT / perpWallDist);

        // Calculate lowest and highest pixel to fill in current stripe
        int drawStart = (int)(((double)HEIGHT - (double)lineHeight) / 2.0);
        if (drawStart < 0) drawStart = 0;
        int drawEnd = lineHeight / 2 + HEIGHT / 2;
        if (drawEnd >= HEIGHT) drawEnd = HEIGHT - 1;

        // Draw the pixels of the stripe as a vertical line
        // drawVerticalLine(data, x, drawStart, drawEnd, color);

        int texIndex;
        if (side == 0) texIndex = (stepX > 0) ? TEXTURE_EAST : TEXTURE_WEST;
        else texIndex = (stepY > 0) ? TEXTURE_SOUTH : TEXTURE_NORTH;

        double wallX; 
        if (side == 0) wallX = data->player->posY + perpWallDist * rayDirY;
        else wallX = data->player->posX + perpWallDist * rayDirX;
        wallX -= floor(wallX);
        int texWidth = data->texture[texIndex].width;

        // x coordinate on the texture
        int texX = (int)(wallX * (double)(texWidth));
        if((side == 0 && rayDirX < 0) || (side == 1 && rayDirY > 0)) {
            texX = texWidth - texX - 1;
        }
        texX = texX % texWidth;
        int texHeight = data->texture[texIndex].height;
        for (int y = drawStart; y < drawEnd; y++) {
            int d = y * 256 - HEIGHT * 128 + lineHeight * 128;
            int texY = ((d * texHeight) / lineHeight) / 256;
            if (texY < 0) texY = 0;
            if (texY >= texHeight) texY = texHeight - 1;
            
            int color = data->texture[texIndex].data[texY * data->texture[texIndex].width + texX];
            drawVerticalLine(data, x, y, y + 1, color);
        }
		for (int y = 0; y < HEIGHT; y++) {
            if (y < drawStart) {
                // Above the wall, draw the ceiling
                drawVerticalLine(data, x, y, y + 1, data->ceiling_color);
            } else if (y > drawEnd) {
                // Below the wall, draw the floor
                drawVerticalLine(data, x, y, y + 1, data->floor_color);
            }
        }
    }

    // After drawing all the vertical lines for every x, put the image to the window
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}
