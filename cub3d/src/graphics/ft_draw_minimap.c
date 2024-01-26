/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_minimap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchbouki <rchbouki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 01:49:10 by thibault          #+#    #+#             */
/*   Updated: 2024/01/26 19:56:17 by rchbouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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

static void	ft_fix_line(int longest, t_data *data)
{
	int		i;
	int		j;
	int		current_length;
	char	*extended_line;

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
}

static void	ft_mini_fill(t_minimap *mini, t_data *data, int longest)
{
	int	color;
	int	x;
	int	y;

	y = -1;
	while (++y < mini->height)
	{
		x = -1;
		while (++x < mini->width)
		{
			mini->y = (int)((double)y / mini->height * data->nb_lines);
			mini->x = (int)((double)x / mini->width \
				* ft_strlen(data->tab[mini->y]));
			if (data->tab[mini->y][mini->x] == '1')
				color = 0x000000;
			else
				color = 0xFFFFFF;
			mini->img[y * mini->width + x] = color;
		}
	}
	mini->player_x = (int)(data->player->pos_x * (mini->width \
				/ (double)longest));
	mini->player_y = (int)(data->player->pos_y * (mini->height \
			/ (double)data->nb_lines));
}

static void	minimap_init(t_minimap *mini, int longest, t_data *data)
{
	ft_fix_line(longest, data);
	mini->aspect_ratio = (double)longest / (double)data->nb_lines;
	mini->width = MAP_SIZE;
	mini->height = MAP_SIZE;
	if (mini->aspect_ratio > 1)
		mini->height = (int)(MAP_SIZE / mini->aspect_ratio);
	else
		mini->width = (int)(MAP_SIZE * mini->aspect_ratio);
	if (!data->minimap_img)
	{
		data->minimap_img = mlx_new_image(data->mlx, mini->width,
				mini->height);
		data->minimap_addr = mlx_get_data_addr(data->minimap_img,
				&data->bits_per_pixel, &data->line_length, &data->endian);
	}
	mini->img = (int *)data->minimap_addr;
	ft_mini_fill(mini, data, longest);
}

void	draw_minimap(t_data *data)
{
	int			longest;
	t_minimap	mini;

	longest = ft_longest_line(data);
	ft_fix_line(longest, data);
	minimap_init(&mini, longest, data);
	if (mini.player_x >= 0 && mini.player_x < mini.width
		&& mini.player_y >= 0 && mini.player_y < mini.height)
		mini.img[mini.player_y * mini.width + mini.player_x] = 0xFF0000;
	data->minimap_x = WIDTH - mini.width - 20;
	data->minimap_y = 20;
	mlx_put_image_to_window(data->mlx, data->win, data->minimap_img,
		data->minimap_x, data->minimap_y);
	raycast_minimap(data, longest);
}
