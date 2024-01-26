/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 21:20:10 by thibnguy          #+#    #+#             */
/*   Updated: 2024/01/26 21:48:40 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	main(int argc, char *argv[])
{
	t_data	*data;

	if (argc != 2)
	{
		printf(RED "[Usage]" YELLOW " %s <'map_name'.cub>\n" EOC, argv[0]);
		return (1);
	}
	data = ft_launch_map(argv[1]);
	data->bonus = 1;
	ft_mlx_init(data);
	ft_regenerate(data);
	mlx_loop(data->mlx);
	return (0);
}
