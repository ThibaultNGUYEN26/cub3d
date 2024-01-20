/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 17:12:49 by thibault          #+#    #+#             */
/*   Updated: 2024/01/20 17:53:58 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	ft_last_in_line(char *line)
{
	int	i;
	int	index;

	i = 0;
	index = -1;
	while (line[i])
	{
		if (line[i] != ' ')
			index = i;
		i++;	
	}
	return (index);
}

/* CAS D'ERREUR :
		- si la 1ere ou derniere ligne a autre chose que des 1 ou des espaces
		- si le premier element dans une ligne est autre qu'un 1
		- si le dernier element dans une ligne est autre qu'un 1
*/
static int	ft_surroundings(t_data *data)
{	
	int	i;
	int	j;
	int	index;

	i = 0;
	while (i < data->nb_lines)
	{
		// soit la premiere ligne ou la derniere
		if (i == 0 || i == data->nb_lines - 1)
		{
			j = 0;
			while (j < data->longest_line)
			{
				if (data->tab[i][j] != '1' && data->tab[i][j] != ' ')
					return (0);
				j++;
			}
		}
		j = 0;
		// j = le premier element de la ligne
		while (j != (data->longest_line - 1) && data->tab[i][j] == ' ')
			j++;
		// index le dernier element de la ligne
		index = ft_last_in_line(data->tab[i]);
		// si j n'est pas un 1 ou index n'est pas un 1
		if (data->tab[i][j] != '1' || data->tab[i][index] != '1')
			return (0);
		i++;
	}
	return (1);
}

static int	ft_check_player(t_data *data)
{
	int	i;
	int	j;
	int	player;
	
	player = 0;
	i = -1;
	while (++i < data->nb_lines)
	{
		j = -1;
		while (++j < data->longest_line)
		{
			if (data->tab[i][j] != 'N' && data->tab[i][j] != 'S'
				&& data->tab[i][j] != 'W' && data->tab[i][j] != 'E'
				&& data->tab[i][j] != '0' && data->tab[i][j] != '1')
			{
				printf(RED "[ERROR]" YELLOW " Wrong map format\n" EOC);
				return (0);
			}
			if (data->tab[i][j] == 'N' || data->tab[i][j] == 'S'
				|| data->tab[i][j] == 'W' || data->tab[i][j] == 'E')
			{
				if (player)
				{
					printf(RED "[ERROR]" YELLOW " Too many players\n" EOC);
					return (0);
				}
				player = 1;
			}
		}
	}
	if (!player)
	{
		printf(RED "[ERROR]" YELLOW " No player\n" EOC);
		return (0);
	}
	return (1);
}

/* TEXTURES PARSING */
static int	ft_check_textures(t_data *data, int i, int j, char *s2)
{
	int	end;
	
	end = j;
	if (data->file[i][j] != '.' || data->file[i][j + 1] != '/')
	{
		printf(RED "[ERROR]" YELLOW " Texures are not well formated\n" EOC);	
		return (0);
	}
	while (data->file[i][end] != '\0' && (data->file[i][end] !='\f' && data->file[i][end] != '\t' && data->file[i][end] != '\r' && data->file[i][end] != '\v' && data->file[i][end] != ' '))
		end++;
	if (!ft_strcmp(s2, "NO"))
		data->texture->t_north = ft_substr(data->file[i], j, end - j);
	else if (!ft_strcmp(s2, "SO"))
		data->texture->t_south = ft_substr(data->file[i], j, end - j);
	else if (!ft_strcmp(s2, "EA"))
		data->texture->t_east = ft_substr(data->file[i], j, end - j);
	else if (!ft_strcmp(s2, "WE"))
		data->texture->t_west = ft_substr(data->file[i], j, end - j);
	return (1);
}

static int	ft_which_tex(t_data *data, int i, char *s2, int *count)
{
	int	j = 0;
	while (data->file[i][j] != '\0' && (data->file[i][j] == '\f' || data->file[i][j] == '\t' || data->file[i][j] == '\r' || data->file[i][j] == '\v' || data->file[i][j] == ' '))
		j++;
	if (ft_strcmp(ft_substr(data->file[i], j, 2), s2) != 0)
		return (0);
	*count += 1;
	if (*count > 1)
	{
		printf(RED "[ERROR]" YELLOW " Too many of the same textures found\n" EOC);
		return (0);
	}
	j += 2;
	while (data->file[i][j] != '\0' && (data->file[i][j] == '\f' || data->file[i][j] == '\t' || data->file[i][j] == '\r' || data->file[i][j] == '\v' || data->file[i][j] == ' '))
		j++;
	if (!ft_check_textures(data, i, j, s2))
		return (0);
	return (1);
}

static int	ft_textures(t_data *data)
{
	int	i;
	int	no;
	int	so;
	int	ea;
	int	we;
	
	no = 0;
	so = 0;
	ea = 0;
	we = 0;
	i = 0;
	while (data->file[i])
	{
		// Getting rid of empty lines
		while (data->file[i] && ft_white_spaces(data->file[i]))
			i++;
		if (data->file[i])
		{
			if (ft_which_tex(data, i, "NO", &no) ||
				ft_which_tex(data, i, "SO", &so) ||
				ft_which_tex(data, i, "WE", &we) ||
				ft_which_tex(data, i, "EA", &ea))
				i++;
			else
				i++;
		}
	}
	if (no == 0 || so == 0 || ea == 0 || we == 0)
	{
		printf(RED "[ERROR]" YELLOW " Not all of the textures have been found\n" EOC);
		return (0);
	}
	printf("NO : %s\n", data->texture->t_north);
	printf("SO : %s\n", data->texture->t_south);
	printf("WE : %s\n", data->texture->t_west);
	printf("EA : %s\n", data->texture->t_east);
	return (1);
}

/* Convert RGB to hexadecimal */
static unsigned int	ft_convert_color(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

/* FLOOR AND CEILING COLORS */
static int	ft_check_rgb(t_data *data, char *s1, int j, char *s2)
{
	int		r;
	int		g;
	int		b;
	int		count;
	int		number;
	int		index;
	char	*str;

	count = 0;
	r = 0;
	g = 0;
	b = 0;
	while (count < 3 && s1[j])
	{
		if (s1[j] == ',')
		{
			count++;
			j++;
		}
		else if (s1[j] >= '0' && s1[j] <= '9')
		{
			index = j;
			while (s1[index] >= '0' && s1[index] <= '9')
				index++;
			str = ft_substr(s1, j, index - j + 1);
			number = ft_atoi(str);
			if (number < 0 || number > 255)
				return (0);
			free(str);
			j = index;
			if (count == 0)
				r = number;
			else if (count == 1)
				g = number;
			else if (count == 2)
				b = number;
		}
		else
			return (0);
	}
	if (count > 2)
		return (0);
	if (!ft_strcmp(s2, "F"))
		data->floor_color = ft_convert_color(r, g, b);
	else if (!ft_strcmp(s2, "C"))
		data->ceiling_color = ft_convert_color(r, g, b);
	return (1);
}

static int	ft_which_element(t_data *data, int i, char *s2, int *count)
{
	int	j;

	j = 0;
	while (data->file[i][j] != '\0' && (data->file[i][j] == '\f' || data->file[i][j] == '\t' || data->file[i][j] == '\r' || data->file[i][j] == '\v' || data->file[i][j] == ' '))
		j++;
	/* printf("str : %s, substr : %s\n", data->file[i], ft_substr(data->file[i], j, 1));*/
	if (ft_strcmp(ft_substr(data->file[i], j, 1), s2) != 0)
		return (0);
	*count += 1;
	if (*count > 1)
	{
		printf(RED "[ERROR]" YELLOW " Too many of the same elements found\n" EOC);
		return (0);
	}
	j += 1;
	while (data->file[i][j] != '\0' && (data->file[i][j] == '\f' || data->file[i][j] == '\t' || data->file[i][j] == '\r' || data->file[i][j] == '\v' || data->file[i][j] == ' '))
		j++;
	if (!ft_check_rgb(data, data->file[i], j, s2))
		return (0);
	return (1);
}

static int	ft_floor_ceiling(t_data *data, int line_textures)
{
	(void)line_textures;
	int	i;
	int	f;
	int	c;
	
	f = 0;
	c = 0;
	i = 0;
	while (data->file[i])
	{	
		// Getting rid of empty lines
		while (data->file[i] && ft_white_spaces(data->file[i]))
			i++;
		if (data->file[i])
		{
			if (ft_which_element(data, i, "F", &f) || ft_which_element(data, i, "C", &c))
				i++;
			else
				i++;
		}
	}
	if (f == 0 || c == 0)
	{
		printf(RED "[ERROR]" YELLOW " Not all of the elements have been found\n" EOC);
		return (0);
	}
	printf("F : %d\n", data->floor_color);
	printf("C : %d\n", data->ceiling_color);
	return (1);
}

int	ft_parsing(t_data *data)
{
	int line_textures = 0;
	if (!ft_surroundings(data))
	{
		printf(RED "[ERROR]" YELLOW " Walls are not closed\n" EOC);
		return (0);
	}
	if (!ft_textures(data))
	{
		printf(RED "[ERROR]" YELLOW " Texture Failure\n" EOC);
		return (0);
	}
	if (!ft_floor_ceiling(data, line_textures))
	{
		printf(RED "[ERROR]" YELLOW " Floor/Ceiling colors are not well formated\n" EOC);
		return (0);
	}
	if (!ft_check_player(data))
		return (0);
	return (1);
}
