/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchbouki <rchbouki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 17:10:47 by thibault          #+#    #+#             */
/*   Updated: 2024/01/26 19:56:18 by rchbouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char *argv[])
{
	t_data	*data;

	if (argc != 2)
	{
		printf(RED "[Usage]" YELLOW " %s <'map_name'.cub>\n" EOC, argv[0]);
		return (1);
	}
	data = ft_launch_map(argv[1]);
	ft_mlx_init(data);
	ft_regenerate(data);
	mlx_loop(data->mlx);
	return (0);
}
