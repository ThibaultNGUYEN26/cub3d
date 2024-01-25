/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsing_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchbouki <rchbouki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 00:41:17 by rchbouki          #+#    #+#             */
/*   Updated: 2024/01/25 20:22:30 by rchbouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	end_parsing(int *k, int start, t_var *var)
{
	int	i;
	
	*k = start;
	i = -1;
	while (++i < 6)
		if (var->var_tab[i] == 0)
			return (0);
	free(var->var_tab);
	free(var->var_char);
	free(var);
	return (1);
}

int	buffer_switch(char *buffer, int *k, int *start)
{
	*start = *k;
	while (ft_is_wspaces(buffer[*k]))
		*k += 1;
	if (buffer[*k] == '\0')
		return (0);
	return (1);
}

void	ft_affect_color(t_data *data, char *cmp, t_color color)
{
	unsigned int	color_hexa;
	char			*str;
	
	color_hexa = ft_convert_color(color);
	str = ft_itoa(color_hexa);
	element_affect(data, cmp, str, 1);
}
