/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchbouki <rchbouki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 20:39:24 by rchbouki          #+#    #+#             */
/*   Updated: 2024/01/23 20:50:38 by rchbouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
