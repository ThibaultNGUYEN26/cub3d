/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_minimap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 01:49:10 by thibault          #+#    #+#             */
/*   Updated: 2024/01/24 21:05:10 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	ft_longest_line(t_data *data)
{
	int	i;
	int	j;
	int	longest;

	longest = 0;
	i = -1;
	while (++i < data->nb_lines)
	{
		j = ft_strlen(data->tab[i]);
		if (longest < j)
			longest = j;
	}
	return (longest);
}

void	draw_minimap(t_data *data)
{
	int		longest;
	int		current_length;
	double	map_aspect_ratio;
	int		minimap_width;
	int		minimap_height;
	int		*img;
	int		map_y;
	int		map_x;
	int		color;
	int		player_minimap_x;
	int		player_minimap_y;
	int		i;
	char	*extended_line;
	int		y;
	int		x;
	int		j;

	longest = ft_longest_line(data);
	i = -1;
	while (++i < data->nb_lines)
	{
		current_length = ft_strlen(data->tab[i]);
		if (current_length < longest)
		{
			extended_line = ft_strdup2(longest, data->tab[i]);
			j = current_length - 1;
			while (++j < longest)
				extended_line[j] = '1';
			extended_line[longest] = '\0';
			free(data->tab[i]);
			data->tab[i] = extended_line;
		}
	}
	map_aspect_ratio = (double)longest / (double)data->nb_lines;
	minimap_width = MAP_SIZE;
	minimap_height = MAP_SIZE;
	if (map_aspect_ratio > 1)
		minimap_height = (int)(MAP_SIZE / map_aspect_ratio);
	else
		minimap_width = (int)(MAP_SIZE * map_aspect_ratio);
	if (!data->minimap_img)
	{
		data->minimap_img = mlx_new_image(data->mlx, minimap_width,
				minimap_height);
		data->minimap_addr = mlx_get_data_addr(data->minimap_img,
				&data->bits_per_pixel, &data->line_length, &data->endian);
	}
	img = (int *)data->minimap_addr;
	y = -1;
	while (++y < minimap_height)
	{
		x = -1;
		while (++x < minimap_width)
		{
			map_y = (int)((double)y / minimap_height * data->nb_lines);
			map_x = (int)((double)x / minimap_width
					* ft_strlen(data->tab[map_y]));
			if (data->tab[map_y][map_x] == '1')
				color = 0x000000;
			else
				color = 0xFFFFFF;
			img[y * minimap_width + x] = color;
		}
	}
	player_minimap_x = (int)(data->player->pos_x * (minimap_width
				/ (double)longest));
	player_minimap_y = (int)(data->player->pos_y * (minimap_height
				/ (double)data->nb_lines));
	if (player_minimap_x >= 0 && player_minimap_x < minimap_width
		&& player_minimap_y >= 0 && player_minimap_y < minimap_height)
		img[player_minimap_y * minimap_width + player_minimap_x] = 0xFF0000;
	data->minimap_x = WIDTH - minimap_width - 20;
	data->minimap_y = 20;
	mlx_put_image_to_window(data->mlx, data->win, data->minimap_img,
		data->minimap_x, data->minimap_y);
	raycast_minimap(data);
}

void	raycast_minimap(t_data *data)
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	int		longest;
	double	map_aspect_ratio;
	int		minimap_width;
	int		minimap_height;
	int		*img;
	double	step_size;
	double	fov;
	double	angle;
	double	raydir_x;
	double	raydir_y;
	double	map_x;
	double	map_y;
	int		minimap_x;
	int		minimap_y;
	int		minimap_index_x;
	int		minimap_index_y;
	int		minimap_index;

	pos_x = data->player->pos_x;
	pos_y = data->player->pos_y;
	dir_x = data->player->dir_x;
	dir_y = data->player->dir_y;
	longest = ft_longest_line(data);
	map_aspect_ratio = (double)longest / (double)data->nb_lines;
	minimap_width = MAP_SIZE;
	minimap_height = MAP_SIZE;
	if (map_aspect_ratio > 1)
		minimap_height = (int)(MAP_SIZE / map_aspect_ratio);
	else
		minimap_width = (int)(MAP_SIZE * map_aspect_ratio);
	img = (int *)data->minimap_addr;
	step_size = 0.01;
	fov = 60 * (M_PI / 180);
	angle = -fov / 2;
	while (angle <= fov / 2)
	{
		raydir_x = dir_x * cos(angle) - dir_y * sin(angle);
		raydir_y = dir_x * sin(angle) + dir_y * cos(angle);
		map_x = pos_x;
		map_y = pos_y;
		while (data->tab[(int)map_y][(int)map_x] != '1')
		{
			map_x += raydir_x * step_size;
			map_y += raydir_y * step_size;
			minimap_x = (int)((map_x - pos_x) * (minimap_width
						/ (double)longest));
			minimap_y = (int)((map_y - pos_y) * (minimap_height
						/ (double)data->nb_lines));
			minimap_index_x = (int)(data->player->pos_x * (minimap_width
						/ (double)longest)) + minimap_x;
			minimap_index_y = (int)(data->player->pos_y * (minimap_height
						/ (double)data->nb_lines)) + minimap_y;
			if (minimap_index_x >= 0 && minimap_index_x < minimap_width
				&& minimap_index_y >= 0 && minimap_index_y < minimap_height)
			{
				minimap_index = minimap_index_y * minimap_width
					+ minimap_index_x;
				img[minimap_index] = 0xFF0000;
			}
			else
				break ;
		}
		angle += step_size;
	}
}
