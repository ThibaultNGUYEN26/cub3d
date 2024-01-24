/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 17:10:47 by thibault          #+#    #+#             */
/*   Updated: 2024/01/24 18:21:22 by thibault         ###   ########.fr       */
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
	// printf("NO : %s\n", data->texture->t_north);
	// printf("SO : %s\n", data->texture->t_south);
	// printf("WE : %s\n", data->texture->t_west);
	// printf("EA : %s\n", data->texture->t_east);
	// printf("F : %d\n", data->floor_color);
	// printf("C : %d\n", data->ceiling_color);
	// ft_player_init(data); // Seems you're calling this inside ft_mlx_init
	ft_mlx_init(data);
	perform_raycasting(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	draw_minimap(data);
	mlx_put_image_to_window(data->mlx, data->win, data->minimap_img,
		data->minimap_x, data->minimap_y);
	mlx_loop(data->mlx);
	return (0);
}
