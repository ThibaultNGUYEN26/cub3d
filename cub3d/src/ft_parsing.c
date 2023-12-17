/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchbouki <rchbouki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 17:12:49 by thibault          #+#    #+#             */
/*   Updated: 2023/12/14 14:58:15 by rchbouki         ###   ########.fr       */
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

static int	ft_surroundings(t_data *data)
{
	int	i;
	int	j;
	int	index;

	i = 0;
	while (i < data->nb_lines)
	{
		j = 0;
		if (i == 0 || i == data->nb_lines - 1)
		{
			while (j < data->longest_line)
			{
				if (data->tab[i][j] != '1' && data->tab[i][j] != ' ')
					return (0);
				j++;
			}
		}
		else
		{
			while (j != (data->longest_line - 1) && data->tab[i][j] == ' ')
				j++;
			index = ft_last_in_line(data->tab[i]);
			if (j != (data->longest_line - 1) && (data->tab[i][j] != '1' || data->tab[i][index] != '1'))
				return (0);
		}
		i++;
	}
	return (1);
}

static int	ft_compare_spaces(char *s1, char *s2)
{
	int	res;
	
	res = ft_strcmp(s1, s2);
	free(s1);
	free(s2);
	return (res);
}

static int	ft_spaces(t_data *data)
{
	int		i;
	int		j;
	int		start;
	int 	end;

	i = 0;
	j = 0;
	while (i < data->nb_lines)
	{
		while (j < data->longest_line)
		{
			// first space
			if (data->tab[i][j] == ' ')
			{
				start = j - 1;
				while (data->tab[i][j] == ' ')
					j++;
				end = j;
				// if before and after the spaces we don't have 1s, wrong map
				if (((start != -1) && (data->tab[i][start] != '1')) || (end != data->longest_line && data->tab[i][end] != '1'))
					return (0);
				// if we DONT have the same spaces in the previous line
				if ((i - 1) >= 0 && ft_compare_spaces(ft_substr(data->tab[i - 1], start + 1, end - start), ft_substr(data->tab[i], start + 1, end - start)))
				{
					// we check if we have ones surrounding upwards
					while (start <= end)
					{
						if (start >= 0 && data->tab[i - 1][start] != '1')
							return (0);
						start++;
					}
				}
				// if we DONT have the same spaces in the next line
				if ((i + 1) < data->nb_lines && ft_compare_spaces(ft_substr(data->tab[i + 1], start + 1, end - start), ft_substr(data->tab[i], start + 1, end - start)))
				{
					// we check if we have ones surrounding upwards
					if (start == -1)
						start = 0;
					while (start <= end && start < data->longest_line)
					{
						if (data->tab[i + 1][start] != '1' && data->tab[i + 1][start] != ' ')
							return (0);
						start++;
					}
				}
			}
			else
				j++;
		}
		i++;
	}
	return (1);
}

/* 
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
} */

int	ft_parsing(t_data *data)
{
	if (!ft_surroundings(data))
	{
		printf(RED "[ERROR]" YELLOW " Walls are not closed\n" EOC);
		return (0);
	}
	/* if (!ft_check_player(data))
		return (0); */
	if (!ft_spaces(data))
	{
		printf(RED "[ERROR]" YELLOW " Spaces are not closed\n" EOC);
		return (0);
	}
	return (1);
}
