/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_minimap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 01:49:10 by thibault          #+#    #+#             */
/*   Updated: 2024/01/19 15:48:03 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void draw_minimap(t_data *data) {
    // Calculate the aspect ratio of the map and the size of the minimap
    double map_aspect_ratio = (double)data->longest_line / (double)data->nb_lines;
    int minimap_width = MAP_SIZE;
    int minimap_height = (int)(MAP_SIZE / map_aspect_ratio);

    // Create the minimap image if it doesn't exist or if its size is incorrect
    if (!data->minimap_img)
    {
        data->minimap_img = mlx_new_image(data->mlx, minimap_width, minimap_height);
        data->minimap_addr = mlx_get_data_addr(data->minimap_img, &data->bits_per_pixel, &data->line_length, &data->endian);
    }

    int *img = (int *)data->minimap_addr;

    // Draw the minimap
    for (int y = 0; y < minimap_height; y++) {
        for (int x = 0; x < minimap_width; x++) {
            // Calculate the corresponding map coordinate
            int map_x = (int)(x * (data->longest_line / (double)minimap_width));
            int map_y = (int)(y * (data->nb_lines / (double)minimap_height));

            // Draw walls and empty spaces differently
            int color = (data->tab[map_y][map_x] == '1') ? 0x000000 : 0xFFFFFF;
            img[y * minimap_width + x] = color;
        }
    }

    // Draw the player on the minimap
    int player_minimap_x = (int)(data->player->posX * (minimap_width / (double)data->longest_line));
    int player_minimap_y = (int)(data->player->posY * (minimap_height / (double)data->nb_lines));

    // Check bounds for player position on minimap
    if (player_minimap_x >= 0 && player_minimap_x < minimap_width && 
        player_minimap_y >= 0 && player_minimap_y < minimap_height) {
        img[player_minimap_y * minimap_width + player_minimap_x] = 0xFF0000; // Red for the player
    }

    // Calculate the position for the minimap (top right corner)
    data->minimap_x = WIDTH - minimap_width - 20;
    data->minimap_y = 20;

    // Display the minimap on the window
    mlx_put_image_to_window(data->mlx, data->win, data->minimap_img, data->minimap_x, data->minimap_y);
    raycastMinimap(data);
}

void raycastMinimap(t_data *data) {
    double posX = data->player->posX;
    double posY = data->player->posY;
    double dirX = data->player->dirX;
    double dirY = data->player->dirY;
    
    int minimap_width = MAP_SIZE; // Use the actual minimap width
    int minimap_height = (int)(MAP_SIZE / ((double)data->longest_line / (double)data->nb_lines)); // Use the actual minimap height
    int *img = (int *)data->minimap_addr;

    // Adjust the step size for more accurate ray casting
    double stepSize = 0.01; // Adjust this value as needed
    double maxRayLength = 5.0; // Adjust based on your map size

    // Iterate through rays within the FOV
    double fov = M_PI / 4; // Example: 45 degrees FOV
    for (double angle = -fov / 2; angle <= fov / 2; angle += stepSize) {
        double rayDirX = dirX * cos(angle) - dirY * sin(angle);
        double rayDirY = dirX * sin(angle) + dirY * cos(angle);

        double mapX = posX;
        double mapY = posY;

        double rayLength = 0.0; // Initialize ray length

        // Ray casting loop
        while (data->tab[(int)mapY][(int)mapX] != '1' && rayLength < maxRayLength) {
            mapX += rayDirX * stepSize;
            mapY += rayDirY * stepSize;

            // Calculate the corresponding minimap coordinates relative to the player's position
            int minimapX = (int)((mapX - posX) * (minimap_width / (double)data->longest_line));
            int minimapY = (int)((mapY - posY) * (minimap_height / (double)data->nb_lines));

            // Calculate the position on the minimap to draw the ray
            int minimapIndexX = (int)(data->player->posX * (minimap_width / (double)data->longest_line)) + minimapX;
            int minimapIndexY = (int)(data->player->posY * (minimap_height / (double)data->nb_lines)) + minimapY;

            // Check bounds for minimap position
            if (minimapIndexX >= 0 && minimapIndexX < minimap_width && minimapIndexY >= 0 && minimapIndexY < minimap_height) {
                int minimapIndex = minimapIndexY * minimap_width + minimapIndexX;
                img[minimapIndex] = 0xFF0000; // Set pixel color for the ray
            }

            // Update ray length
            rayLength += stepSize;
        }
    }
}
