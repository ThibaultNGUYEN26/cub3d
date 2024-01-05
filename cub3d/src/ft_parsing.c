/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchbouki <rchbouki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 17:12:49 by thibault          #+#    #+#             */
/*   Updated: 2024/01/05 23:33:05 by rchbouki         ###   ########.fr       */
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
