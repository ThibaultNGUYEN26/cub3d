/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchbouki <rchbouki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 22:40:27 by rchbouki          #+#    #+#             */
/*   Updated: 2024/01/26 16:33:11 by rchbouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_free_data(t_data *data, int i, char *buffer, char *msg)
{
	int	j;

	j = -1;
	printf(RED "[ERROR]" YELLOW " %s\n" EOC, msg);
	free(data->texture->t_north);
	free(data->texture->t_south);
	free(data->texture->t_east);
	free(data->texture->t_west);
	while (++j < i)
		free(data->tab[j]);
	free(data->tab);
	if (buffer)
		free(buffer);
	free(data);
	exit(EXIT_FAILURE);
}

int	empty_line(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!ft_is_wspaces(str[i]) && str[i] != '\n' && str[i] != '\0')
			return (free(str), 0);
		if (str[i] == '\0')
			break ;
	}
	return (free(str), 1);
}

int	ft_last_in_line(char *line)
{
	int	i;
	int	index;

	i = ft_strlen(line) - 1;
	index = 0;
	while (i >= 0)
	{
		if (!ft_is_wspaces(line[i]) && line[i] != '\n')
			break ;
		i--;
		index++;
	}
	free(line);
	return (index);
}

static void	ft_tab_init(t_data *data, char *buffer, int k)
{
	int	i;

	ft_skip_empty(data, buffer, &k);
	i = k;
	ft_count_lines(buffer, &k, data);
	ft_check_surroundings(buffer, &k, &i, data);
	data->tab = malloc(sizeof(int *) * (data->nb_lines + 1));
	if (!data->tab)
		ft_free_data(data, 0, buffer, "Allocation Failure.");
	k = i;
	tab_init_utils(buffer, &k, data);
}

void	ft_create_tab(t_data *data, char *buffer, int k)
{
	int	i;
	int	player;

	ft_tab_init(data, buffer, k);
	free(buffer);
	player = 0;
	ft_check_player(data, &player);
	if (!player)
		ft_free_data(data, data->nb_lines, NULL, "Invalid Map.");
	i = -1;
	while (++i < data->nb_lines)
	{
		if (i == 0)
			check_line(data, i, i + 1);
		else if (i == data->nb_lines - 1)
			check_line(data, i, i - 1);
		else
		{
			check_line(data, i, i + 1);
			check_line(data, i, i - 1);
		}
	}
}
