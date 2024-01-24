/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchbouki <rchbouki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 18:16:27 by rchbouki          #+#    #+#             */
/*   Updated: 2024/01/24 20:49:17 by rchbouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	ft_init_parsing(t_data **data, int **var, char ***var_char)
{
	int	i;

	i = 0;
	*data = malloc(sizeof(t_data) * 1);
	*var = malloc(sizeof(int) * 6);
	(*var_char) = malloc(sizeof(char *) * 7);
	if (!(*data) || !(*var) || !(*var_char))
		return (0);
	(*data)->tab = NULL;
	(*data)->nb_lines = 0;
	(*data)->longest_line = 0;
	(*data)->texture->t_north = NULL;
	(*data)->texture->t_south = NULL;
	(*data)->texture->t_west = NULL;
	(*data)->texture->t_east = NULL;
	while (i < 6)
		(*var)[i++] = 0;
	(*var_char)[0] = "NO";
	(*var_char)[1] = "SO";
	(*var_char)[2] = "WE";
	(*var_char)[3] = "EA";
	(*var_char)[4] = "C";
	(*var_char)[5] = "F";
	(*var_char)[6] = NULL;
	return (1);
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

int	check_color(t_data *data, char *buffer, char *cmp, int *k)
{
	int	r;
	int	g;
	int	b;
	int	count;
	int	start;

	count = 0;
	while (1)
	{
		start = *k;
		while (!ft_is_wspaces(buffer[*k]) && buffer[*k] != ','
			&& (buffer[*k] >= '0' && buffer[*k] <= '9'))
			*k += 1;
		if (buffer[*k] == ',')
		{
			if (count == 0 && !affect_color(ft_substr(buffer, start, *k
						- start), &r))
				return (-1);
			else if (count == 1 && !affect_color(ft_substr(buffer, start, *k
						- start), &g))
				return (-1);
			else if (count > 1)
				return (-1);
			*k += 1;
			count++;
		}
		else if (buffer[*k] == '\n' || ft_is_wspaces(buffer[*k]))
		{
			if (count == 2 && !affect_color(ft_substr(buffer, start, *k
						- start), &b))
				return (-1);
			else if (count != 2 || check_color_utils(buffer, k) == -1)
				return (-1);
			break ;
		}
		else
			return (-1);
	}
	element_affect(data, cmp, ft_itoa(ft_convert_color(r, g, b)), 1);
	return (1);
}

static int	ft_check_element(char *buffer, int *k, t_data *data, char *cmp)
{
	char	*str;
	int		len;
	int		result;

	len = ft_strlen(cmp);
	str = ft_substr(buffer, *k, len);
	result = ft_strcmp(str, cmp);
	free(str);
	// checking for example that its ONLY NO and not NONONONO => using the is_spaces
	if (!result && ft_is_wspaces(buffer[*k + len]))
	{
		*k += len;
		while (ft_is_wspaces(buffer[*k]))
			*k += 1;
		if (buffer[*k] == '\0' || buffer[*k] == '\n')
			return (-1);
		// if we are not checking colors : we are checking textures
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
	int		*var;
	char	**var_char;
	int		k;
	int		temp;
	int		i;
	int		start;

	i = -1;
	k = 0;
	data = NULL;
	var = NULL;
	var_char = NULL;
	if (!ft_init_parsing(&data, &var, &var_char))
	{
		free(buffer);
		printf(RED "[ERROR]" YELLOW " Allocation failure.\n" EOC);
		exit(EXIT_FAILURE);
	}
	/* let's first scan every line for the textures and the colors and fill the data elements */
	while (i != 6)
	{
		start = k;
		// skipping the white spaces (empty lines or just spaces)
		while (ft_is_wspaces(buffer[k]))
			k++;
		if (buffer[k] == '\0')
			error_msg(data, var, var_char, buffer);
		else if (buffer[k] == '\n')
			k++;
		else
		{
			i = -1;
			while (++i < 6)
			{
				temp = ft_check_element(buffer, &k, data, var_char[i]);
				if (temp == -1)
					error_msg(data, var, var_char, buffer);
				if (temp)
				{
					var[i] += 1;
					if (var[i] > 1)
						error_msg(data, var, var_char, buffer);
					break ;
				}
			}
		}
		// la boucle s'arrête quand on trouve une ligne qui ne match avec rien d'ou le i == 6 
	}
	k = start;
	i = -1;
	while (++i < 6)
		if (var[i] == 0)
			error_msg(data, var, var_char, buffer);
	free(var);
	free(var_char);
	ft_create_tab(data, buffer, k);
	return (data);
}
