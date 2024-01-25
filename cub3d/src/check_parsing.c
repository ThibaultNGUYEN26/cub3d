/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchbouki <rchbouki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 20:39:24 by rchbouki          #+#    #+#             */
/*   Updated: 2024/01/25 01:15:29 by rchbouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_init_data(t_data **data)
{
	*data = malloc(sizeof(t_data) * 1);
	if (!data)
		return (0);
	(*data)->tab = NULL;
	(*data)->nb_lines = 0;
	(*data)->longest_line = 0;
	(*data)->texture->t_north = NULL;
	(*data)->texture->t_south = NULL;
	(*data)->texture->t_west = NULL;
	(*data)->texture->t_east = NULL;
	return (1);
}

int	ft_init_var(t_var **var)
{
	int	j;
	
	j = 0;
	while (j < 6)
		(*var)->var_tab[j++] = 0;
	(*var)->var_char[0] = "NO";
	(*var)->var_char[1] = "SO";
	(*var)->var_char[2] = "WE";
	(*var)->var_char[3] = "EA";
	(*var)->var_char[4] = "C";
	(*var)->var_char[5] = "F";
	(*var)->var_char[6] = NULL;
	return (1);
}

int	check_element_utils(char *buffer, int *k, t_data *data, char *cmp)
{
	int	end;

	// if we are not checking colors : we are checking textures
	if (ft_strcmp(cmp, "F") && ft_strcmp(cmp, "C"))
	{
		end = *k;
		if (buffer[*k] != '.' || buffer[*k + 1] != '/')
			return (-1);
		while (!ft_is_wspaces(buffer[end]) && buffer[end] != '\n')
			end++;
		if (buffer[*k] == '\0')
			return (-1);
		element_affect(data, cmp, ft_substr(buffer, *k, end - *k), 0);
		*k = end;
	}
	else
	{
		if (check_color(data, buffer, cmp, k) == -1)
			return (-1);
	}
	return (1);
}

void	ft_skip(char *buffer, int *k, int *start)
{
	*start = *k;
	while (!ft_is_wspaces(buffer[*k]) && buffer[*k] != ','
		&& (buffer[*k] >= '0' && buffer[*k] <= '9'))
		*k += 1;
}

int	element_loop(t_data *data, t_var *var, char *buffer, int *k)
{
	int	i;
	int	temp;

	i = -1;
	while (++i < 6)
	{
		temp = ft_check_element(buffer, k, data, var->var_char[i]);
		if (temp == -1)
			return (0);
		if (temp)
		{
			var->var_tab[i] += 1;
			if (var->var_tab[i] > 1)
				error_msg(data, var, buffer);
			break ;
		}
	}
	return (i);
}
