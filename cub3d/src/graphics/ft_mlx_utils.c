/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchbouki <rchbouki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 16:35:26 by rchbouki          #+#    #+#             */
/*   Updated: 2024/01/26 16:41:06 by rchbouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	ft_close_window(t_data *data)
{
	(void)data;
	printf(GREEN "[INFO] " YELLOW "Closing program...\n" EOC);
	exit(0);
	return (0);
}

void	ft_free_utils(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_lines)
		free(data->tab[i]);
	free(data->tab);
	free(data->player);
	free(data);
}

void	free_textures(t_data *data)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (data->texture[i].img_ptr != NULL)
		{
			mlx_destroy_image(data->mlx, data->texture[i].img_ptr);
			data->texture[i].img_ptr = NULL;
			data->texture[i].data = NULL;
		}
	}
	free(data->texture->t_north);
	free(data->texture->t_south);
	free(data->texture->t_east);
	free(data->texture->t_west);
}

int	ft_key_hook(int key, t_data *data)
{
	if (key == ESC)
	{
		mlx_destroy_image(data->mlx, data->minimap_img);
		mlx_destroy_image(data->mlx, data->img);
		free_textures(data);
		ft_free_utils(data);
		printf(GREEN "[INFO] " YELLOW "Closing program...\n" EOC);
		exit(0);
	}
	if (key == KEY_W)
		data->forward = 1;
	if (key == KEY_S)
		data->backward = 1;
	if (key == KEY_A)
		data->left = 1;
	if (key == KEY_D)
		data->right = 1;
	if (key == KEY_LEFT)
		data->turn_left = 1;
	if (key == KEY_RIGHT)
		data->turn_right = 1;
	return (0);
}

int	ft_key_release_hook(int key, t_data *data)
{
	if (key == KEY_W)
		data->forward = 0;
	if (key == KEY_S)
		data->backward = 0;
	if (key == KEY_A)
		data->left = 0;
	if (key == KEY_D)
		data->right = 0;
	if (key == KEY_LEFT)
		data->turn_left = 0;
	if (key == KEY_RIGHT)
		data->turn_right = 0;
	return (0);
}
