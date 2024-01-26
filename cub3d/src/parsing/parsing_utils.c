/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchbouki <rchbouki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 21:00:49 by rchbouki          #+#    #+#             */
/*   Updated: 2024/01/26 16:33:26 by rchbouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	ft_is_wspaces(char c)
{
	if (c == '\0' || c == '\n' || (c != '\f' && c != '\t' && c != '\r'
			&& c != '\v' && c != ' '))
		return (0);
	return (1);
}

void	error_msg(t_data *data, t_var *var, char *buffer)
{
	if (data->texture->t_north)
		free(data->texture->t_north);
	if (data->texture->t_south)
		free(data->texture->t_south);
	if (data->texture->t_east)
		free(data->texture->t_east);
	if (data->texture->t_west)
		free(data->texture->t_west);
	free(data);
	free(var->var_tab);
	free(var->var_char);
	free(var);
	free(buffer);
	printf(RED "[ERROR]" YELLOW " Invalid Map.\n" EOC);
	exit(EXIT_FAILURE);
}

/* can't have anything after r,g,b besides spaces 
and if we've reached the end of the file => no map => error */
int	color_utils(char *buffer, int *k)
{
	while (buffer[*k] != '\n')
	{
		if ((buffer[*k] != '\f' && buffer[*k] != '\t' && buffer[*k] != '\r'
				&& buffer[*k] != '\v' && buffer[*k] != ' ')
			|| buffer[*k] == '\0')
			return (0);
		*k += 1;
	}
	return (1);
}

int	affect(char *buffer, int *k, int i, int *value)
{
	char	*str;

	str = ft_substr(buffer, i, *k - i);
	*value = ft_atoi(str);
	free(str);
	if (*value < 0 || *value > 255)
		return (0);
	return (1);
}

unsigned int	ft_convert_color(t_color color)
{
	return ((color.r << 16) | (color.g << 8) | color.b);
}
