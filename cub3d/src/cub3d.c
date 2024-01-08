/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 17:10:47 by thibault          #+#    #+#             */
/*   Updated: 2024/01/08 14:17:58 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int main(int argc, char *argv[])
{
	t_data		*data;

	data = NULL;
	if (argc != 2)
	{
		printf(RED "[Usage]" YELLOW " %s <'map_name'.cub>\n" EOC, argv[0]);
		return (1);
	}
	else
	{
		data = ft_launch_map(argv[1]);
		ft_player_init(data);
	}
	setup_mlx(data);
	return (0);
}
