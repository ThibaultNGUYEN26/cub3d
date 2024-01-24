/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycasting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 21:37:38 by thibault          #+#    #+#             */
/*   Updated: 2024/01/24 20:30:57 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	draw_vertical_line(t_data *data, int x, int draw_start,
		int draw_end, int color)
{
	int	*img;
	int	y;

	img = (int *)data->addr;
	y = draw_start - 1;
	while (++y < draw_end)
	{
		if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
			img[y * WIDTH + x] = color;
	}
}

void	perform_raycasting(t_data *data)
{
	double	raydir_x;
	double	raydir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		tex_index;
	double	wall_x;
	int		tex_width;
	int		tex_x;
	int		tex_y;
	int		tex_height;
	int		d;
	int		color;
	double	camera_x;
	int		x;
	int		y;
	int		side;
	int		hit;

	x = -1;
	while (++x < WIDTH)
	{
		// Calculate position and direction for the ray
		camera_x = 2 * x / (double)WIDTH - 1;
		// x-coordinate in camera space
		raydir_x = data->player->dir_x + data->player->planeX * camera_x;
		raydir_y = data->player->dir_y + data->player->planeY * camera_x;
		// Initialize map coordinates with player's position
		map_x = (int)data->player->pos_x;
		map_y = (int)data->player->pos_y;
		// Length of ray from current position to next x or y-side
		// Length of ray from one x or y-side to next x or y-side
		if (fabs(raydir_x) < 1e-6)
			delta_dist_x = 1e30;
		else
			delta_dist_x = fabs(1 / raydir_x);
		if (fabs(raydir_y) < 1e-6)
			delta_dist_y = 1e30;
		else
			delta_dist_y = fabs(1 / raydir_y);
		// Direction to step in x or y-direction (either +1 or -1)
		hit = 0;// Was there a wall hit?
		// Calculate step and initial sideDist
		if (raydir_x < 0)
		{
			step_x = -1;
			side_dist_x = (data->player->pos_x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - data->player->pos_x) * delta_dist_x;
		}
		if (raydir_y < 0)
		{
			step_y = -1;
			side_dist_y = (data->player->pos_y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - data->player->pos_y) * delta_dist_y;
		}
		// Perform DDA
		while (hit == 0)
		{
			// Jump to next map square, OR in x-direction, OR in y-direction
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
			// Check if ray has hit a wall
			if (map_x >= 0 && map_x < WIDTH && map_y >= 0 && map_y < HEIGHT)
			{
				if (data->tab[map_y][map_x] == '1')
					hit = 1;
			}
			else
				hit = 1;
		}
		// Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		if (side == 0)
			perp_wall_dist = (map_x - data->player->pos_x + (1 - step_x) / 2)
				/ raydir_x;
		else
			perp_wall_dist = (map_y - data->player->pos_y + (1 - step_y) / 2)
				/ raydir_y;
		// Calculate height of line to draw on screen
		line_height = (int)(HEIGHT / perp_wall_dist);
		// Calculate lowest and highest pixel to fill in current stripe
		draw_start = (int)(((double)HEIGHT - (double)line_height) / 2.0);
		if (draw_start < 0)
			draw_start = 0;
		draw_end = line_height / 2 + HEIGHT / 2;
		if (draw_end >= HEIGHT)
			draw_end = HEIGHT - 1;
		// Draw the pixels of the stripe as a vertical line
		// draw_vertical_line(data, x, draw_start, draw_end, color);
		if (side == 0)
		{
			if (step_x > 0)
				tex_index = TEXTURE_EAST;
			else
				tex_index = TEXTURE_WEST;
		}
		else
		{
			if (step_y > 0)
				tex_index = TEXTURE_SOUTH;
			else
				tex_index = TEXTURE_NORTH;
		}
		if (side == 0)
			wall_x = data->player->pos_y + perp_wall_dist * raydir_y;
		else
			wall_x = data->player->pos_x + perp_wall_dist * raydir_x;
		wall_x -= floor(wall_x);
		tex_width = data->texture[tex_index].width;
		tex_x = (int)(wall_x * (double)(tex_width));
		if ((side == 0 && raydir_x < 0) || (side == 1 && raydir_y > 0))
			tex_x = tex_width - tex_x - 1;
		tex_x = tex_x % tex_width;
		tex_height = data->texture[tex_index].height;
		y = draw_start - 1;
		while (++y < draw_end)
		{
			d = y * 256 - HEIGHT * 128 + line_height * 128;
			tex_y = ((d / 256) * tex_height) / line_height;
			if (tex_y < 0)
				tex_y = 0;
			if (tex_y >= tex_height)
				tex_y = tex_height - 1;
			color = data->texture[tex_index].data[tex_y
				* data->texture[tex_index].width + tex_x];
			draw_vertical_line(data, x, y, y + 1, color);
		}
		y = -1;
		while (++y < HEIGHT)
		{
			if (y < draw_start)
				draw_vertical_line(data, x, y, y + 1, data->ceiling_color);
			else if (y > draw_end)
				draw_vertical_line(data, x, y, y + 1, data->floor_color);
		}
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}
