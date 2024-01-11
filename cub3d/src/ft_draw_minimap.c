/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_minimap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 01:49:10 by thibault          #+#    #+#             */
/*   Updated: 2024/01/11 02:10:40 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void draw_minimap(t_data *data) {
    // Create the minimap image if it doesn't exist
    if (!data->minimap_img) {
    	data->minimap_img = mlx_new_image(data->mlx, MAP_SIZE, MAP_SIZE);
        data->minimap_addr = mlx_get_data_addr(data->minimap_img, &data->bits_per_pixel, &data->line_length, &data->endian);
    }
	int *img = (int *)data->minimap_addr;

    // Draw the minimap
    for (int y = 0; y < MAP_SIZE; y++) {
        for (int x = 0; x < MAP_SIZE; x++) {
            // Calculate the corresponding map coordinate
            int map_x = (int)(x * (data->longest_line / (double)MAP_SIZE));
            int map_y = (int)(y * (data->nb_lines / (double)MAP_SIZE));

            // Draw walls and empty spaces differently
            int color = (data->tab[map_y][map_x] == '1') ? 0x000000 : 0xFFFFFF;
			if (y * MAP_SIZE + x < MAP_SIZE * MAP_SIZE)
            	img[y * MAP_SIZE + x] = color;
        }
    }

    // Draw the player on the minimap
    int player_minimap_x = (int)(data->player->posX * (MAP_SIZE / (double)data->longest_line));
    int player_minimap_y = (int)(data->player->posY * (MAP_SIZE / (double)data->nb_lines));

    // Check bounds for player position on minimap
    if (player_minimap_x >= 0 && player_minimap_x < MAP_SIZE && 
        player_minimap_y >= 0 && player_minimap_y < MAP_SIZE) {
        img[player_minimap_y * MAP_SIZE + player_minimap_x] = 0xFF0000; // Red for the player
    }

    // Calculate the position for the minimap (top right corner)
    data->minimap_x = WIDTH - MAP_SIZE;
	data->minimap_y = 0;
	raycastMinimap(data);
}

void raycastMinimap(t_data *data) {
    double posX = data->player->posX;
    double posY = data->player->posY;
    double dirX = data->player->dirX;
    double dirY = data->player->dirY;

    int *img = (int *)data->minimap_addr;

    // Adjust the step size for more accurate ray casting
    double stepSize = 0.01; // Adjust this value as needed
    double maxRayLength = 0.5; // Maximum ray length (adjust as needed)

    // Iterate through rays
    for (double angle = -M_PI / 6; angle <= M_PI / 6; angle += stepSize) {
        double rayDirX = dirX * cos(angle) - dirY * sin(angle);
        double rayDirY = dirX * sin(angle) + dirY * cos(angle);

        double mapX = posX;
        double mapY = posY;

        double rayLength = 0.0; // Initialize ray length

        // Ray casting loop
        while (data->tab[(int)mapY][(int)mapX] != '1' && rayLength < maxRayLength) {
            mapX += rayDirX * 0.01; // Adjust the step size as needed
            mapY += rayDirY * 0.01;

            // Calculate the corresponding minimap coordinates relative to the player's position
            int minimapX = (int)((mapX - posX) * (MAP_SIZE / data->longest_line));
            int minimapY = (int)((mapY - posY) * (MAP_SIZE / data->nb_lines));

            // Calculate the position on the minimap to draw the ray
            int minimapIndexX = (int)(data->player->posX * (MAP_SIZE / (double)data->longest_line)) + minimapX;
            int minimapIndexY = (int)(data->player->posY * (MAP_SIZE / (double)data->nb_lines)) + minimapY;

            // Check bounds for minimap position
            if (minimapIndexX >= 0 && minimapIndexX < MAP_SIZE && minimapIndexY >= 0 && minimapIndexY < MAP_SIZE) {
                int minimapIndex = minimapIndexY * MAP_SIZE + minimapIndexX;
                img[minimapIndex] = 0xFF0000; // Set pixel color to green for the ray
            }

            // Update ray length
            rayLength += 0.001; // Adjust the step size as needed
        }
    }
}


