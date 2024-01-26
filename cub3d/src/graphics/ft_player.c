/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_player.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchbouki <rchbouki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 23:34:14 by thibault          #+#    #+#             */
/*   Updated: 2024/01/26 19:56:19 by rchbouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	ft_player_direction(t_data *data, char dir)
{
	data->player->dir_x = 0;
	data->player->dir_y = 0;
	data->player->plane_x = 0;
	data->player->plane_y = 0;
	if (dir == 'N')
	{
		data->player->dir_y = -1;
		data->player->plane_x = tan((60.0 * M_PI / 180.0) / 2.0);
	}
	else if (dir == 'S')
	{
		data->player->dir_y = 1;
		data->player->plane_x = -tan((60.0 * M_PI / 180.0) / 2.0);
	}
	else if (dir == 'W')
	{
		data->player->dir_x = -1;
		data->player->plane_y = -tan((60.0 * M_PI / 180.0) / 2.0);
	}
	else
	{
		data->player->dir_x = 1;
		data->player->plane_y = tan((60.0 * M_PI / 180.0) / 2.0);
	}
}

void	ft_player_init(t_data *data)
{
	int	i;
	int	j;

	data->player = malloc(sizeof(t_player) * 1);
	if (!data->player)
		return ;
	i = -1;
	while (++i < data->nb_lines)
	{
		j = -1;
		while (data->tab[i][++j])
		{
			if (data->tab[i][j] == 'N' || data->tab[i][j] == 'S'
				|| data->tab[i][j] == 'W' || data->tab[i][j] == 'E')
			{
				ft_player_direction(data, data->tab[i][j]);
				data->player->pos_x = (double)j + 0.5;
				data->player->pos_y = (double)i + 0.5;
				return ;
			}
		}
	}
}
