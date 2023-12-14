/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 17:12:49 by thibault          #+#    #+#             */
/*   Updated: 2023/12/12 21:31:07 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	ft_last_in_line(char *line)
{
	int	i;
	int	index;

	i = 0;
	while (line[i])
		if (line[i] != ' ')
			index = i;
		i++;
	return (index);
}

static int	ft_surroundings(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->nb_lines)
	{
		j = 0;
		if (i == 0 || i = data->nb_lines - 1)
			while (j < data->longest_line)
				if (data->tab[i][j] != '1' || data->tab[i][j] != ' ')
					return (0);
		else
		{
			while (data->tab[i][j] == ' ')
				j++;
			if (data->tab[i][j] != 1 || ft_last_in_line(data->tab[i]) != 1)
				return (0);
		}
		i++;
	}
	return (1);
}

static int	ft_spaces(t_data *data)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (i < data->nb_lines)
	{
		j = 0;
		if (tab[i][j] == ' ')
		{
			if (tab[i][j - 1] != '1')
				return (0);
			while (tab[i][j] == ' ')
				j++;
			if (tab[i][j] != '1')
				return (0);
		}
		else
		{
			k = j;
			if (tab[i - 1][k] == ' ' && (tab[i][k] != -1 || tab[i][k]) 
			while (tab[i - 1][k] == ' ')
			
		}
		j++;
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
					printf(RED "[ERROR]" YELLOW " Too many player\n" EOC);
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

int	ft_parsing(t_data *data)
{
	if (!ft_surroundings(data))
	{
		printf(RED "[ERROR]" YELLOW " Walls are not closed\n" EOC);
		return (0);
	}
	if (!ft_check_player(data))
		return (0);
	return (1);
}
