/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchbouki <rchbouki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 18:16:27 by rchbouki          #+#    #+#             */
/*   Updated: 2024/01/26 16:33:21 by rchbouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	ft_init_parsing(t_data **data, t_var **var, int *i, int *k)
{
	*i = -1;
	*k = 0;
	*var = malloc(sizeof(t_var) * 1);
	(*var)->var_tab = malloc(sizeof(int) * 6);
	if (!(*var)->var_tab)
		return (free(*var), 0);
	(*var)->var_char = malloc(sizeof(char *) * 7);
	if (!(*var)->var_char)
	{
		free((*var)->var_tab);
		return (free(*var), 0);
	}
	if (!ft_init_data(data))
	{
		free((*var)->var_tab);
		free((*var)->var_char);
		return (free(*var), 0);
	}
	return (ft_init_var(var));
}

void	element_affect(t_data *data, char *cmp, char *value, int test)
{
	if (!test)
	{
		if (!ft_strcmp(cmp, "NO"))
			data->texture->t_north = value;
		else if (!ft_strcmp(cmp, "SO"))
			data->texture->t_south = value;
		else if (!ft_strcmp(cmp, "EA"))
			data->texture->t_east = value;
		else if (!ft_strcmp(cmp, "WE"))
			data->texture->t_west = value;
	}
	else
	{
		if (!ft_strcmp(cmp, "F"))
			data->floor_color = ft_atoi(value);
		else if (!ft_strcmp(cmp, "C"))
			data->ceiling_color = ft_atoi(value);
		free(value);
	}
}

int	check_color(t_data *data, char *buf, char *cmp, int *k)
{
	t_color	c;
	int		j;
	int		i;

	j = -1;
	while (++j <= 2)
	{
		ft_skip(buf, k, &i);
		if (buf[*k] == ',')
		{
			if (j > 1 || (!j && !affect(buf, k, i, &(c.r)))
				|| (j == 1 && !affect(buf, k, i, &(c.g))))
				return (-1);
			*k += 1;
		}
		else if (buf[*k] == '\n' || ft_is_wspaces(buf[*k]))
		{
			if ((j == 2 && !affect(buf, k, i, &(c.b))) || !color_utils(buf, k))
				return (-1);
		}
		else
			return (-1);
	}
	ft_affect_color(data, cmp, c);
	return (1);
}

int	ft_check_element(char *buffer, int *k, t_data *data, char *cmp)
{
	char	*str;
	int		len;
	int		result;

	len = ft_strlen(cmp);
	str = ft_substr(buffer, *k, len);
	result = ft_strcmp(str, cmp);
	free(str);
	if (!result && ft_is_wspaces(buffer[*k + len]))
	{
		*k += len;
		while (ft_is_wspaces(buffer[*k]))
			*k += 1;
		if (buffer[*k] == '\0' || buffer[*k] == '\n')
			return (-1);
		if (check_element_utils(buffer, k, data, cmp) == -1)
			return (-1);
	}
	else if (result)
		return (0);
	else
		return (-1);
	return (1);
}

t_data	*ft_parsing(char *buffer)
{
	t_data	*data;
	t_var	*var;
	int		k;
	int		i;
	int		start;

	if (!ft_init_parsing(&data, &var, &i, &k))
		return (NULL);
	while (i != 6)
	{
		if (!buffer_switch(buffer, &k, &start))
			error_msg(data, var, buffer);
		else if (buffer[k] == '\n')
			k++;
		else
			i = element_loop(data, var, buffer, &k);
	}
	if (!end_parsing(&k, start, var))
		error_msg(data, var, buffer);
	ft_create_tab(data, buffer, k);
	return (data);
}
