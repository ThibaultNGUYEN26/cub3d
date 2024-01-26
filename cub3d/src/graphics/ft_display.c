/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 17:45:41 by rchbouki          #+#    #+#             */
/*   Updated: 2024/01/26 21:37:54 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	load_texture(t_data *data, int texture_index, char *file_path)
{
	void	*tex_img;
	int		bpp;
	int		size_line;
	int		endian;

	data->texture[texture_index].img_ptr = mlx_xpm_file_to_image(data->mlx,
			file_path, &data->texture[texture_index].width,
			&data->texture[texture_index].height);
	if (data->texture[texture_index].img_ptr == NULL)
	{
		printf("Texture error\n");
		exit(EXIT_FAILURE);
	}
	tex_img = data->texture[texture_index].img_ptr;
	bpp = data->texture[texture_index].bpp;
	size_line = data->texture[texture_index].size_line;
	endian = data->texture[texture_index].endian;
	data->texture[texture_index].data = (int *)mlx_get_data_addr(tex_img, \
	&bpp, &size_line, &endian);
}

void	ft_regenerate(t_data *data)
{
	perform_raycasting(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	if (data->bonus)
	{
		draw_minimap(data);
		mlx_put_image_to_window(data->mlx, data->win, data->minimap_img,
			data->minimap_x, data->minimap_y);
	}
}
