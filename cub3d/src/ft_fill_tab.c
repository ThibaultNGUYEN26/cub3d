/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchbouki <rchbouki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 22:40:27 by rchbouki          #+#    #+#             */
/*   Updated: 2024/01/25 01:22:20 by rchbouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	ft_free_data(t_data *data, int i, char *buffer, char *msg)
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

static int	empty_line(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!ft_is_wspaces(str[i]) && str[i] != '\n' && str[i] != '\0')
		{
			free(str);
			return (0);
		}
		if (str[i] == '\0')
			break ;
	}
	free(str);
	return (1);
}

static int	ft_last_in_line(char *line)
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
	int	count;
	int	start;
	int	end;

	// skip the empty lines
	while (1)
	{
		start = k;
		while (buffer[k] != '\n' && buffer[k] != '\0')
			k++;
		if (!empty_line(ft_substr(buffer, start, k - start + 1)))
		{
			k = start;
			break ;
		}
		else
			k++;
	}
	if (buffer[k] == '\0')
		ft_free_data(data, 0, buffer, "Invalid Map.\n");
	// check where la fin of le tableau is
	i = k;
	while (1)
	{
		start = k;
		while (buffer[k] && buffer[k] != '\n')
			k++;
		if (empty_line(ft_substr(buffer, start, k - start + 1)))
			break ;
		else
		{
			count = k - start;
			data->nb_lines++;
			if (data->longest_line < count)
				data->longest_line = count;
			if (buffer[k] == '\0')
				break ;
		}
		k++;
	}
	end = k;
	// check if after the first empty line we encounter after the end of the map, there are ONLY empty lines
	while (buffer[k])
	{
		if (!ft_is_wspaces(buffer[k]) && buffer[k] != '\n' && buffer[k] != '\0')
			ft_free_data(data, 0, buffer, "Invalid Map.\n");
		k++;
	}
	// checking the surroundings
	k = i;
	while (k < end)
	{
		start = k;
		while (buffer[k] && buffer[k] != '\n')
			k++;
		while (ft_is_wspaces(buffer[start]))
			start++;
		if (buffer[start] != '1' || buffer[k - ft_last_in_line(ft_substr(\
buffer, start, k - start)) - 1] != '1')
			ft_free_data(data, 0, buffer, "Invalid Map.\n");
		k++;
	}
	// allocate the tab if all is well
	data->tab = malloc(sizeof(int *) * (data->nb_lines + 1));
	if (!data->tab)
		ft_free_data(data, 0, buffer, "Allocation Failure.");
	k = i;
	i = -1;
	while (++i < data->nb_lines)
	{
		start = k;
		while (buffer[k] && buffer[k] != '\n')
		{
			if (ft_is_wspaces(buffer[k]))
				buffer[k] = '1';
			k++;
		}
		/* printf("start : %d, k : %d, buffer : %s\n", start, k, ft_substr(buffer, start, k - start)); */
		data->tab[i] = ft_substr(buffer, start, k - start);
		if (!(data->tab[i]))
			ft_free_data(data, i, buffer, "Allocation Failure.");
		if (buffer[k])
			k++;
		printf("%s\n", data->tab[i]);
	}
	data->tab[i] = NULL;
}

void	ft_create_tab(t_data *data, char *buffer, int k)
{
	int	i;
	int	j;
	int	player;
	int	len_1;
	int	len_2;

	ft_tab_init(data, buffer, k);
	free(buffer);
	// CHECKING THE FIRST AND LAST LINES + CHEKCING THE PLAYER
	player = 0;
	i = -1;
	while (++i < data->nb_lines)
	{
		if (i == 0 || i == data->nb_lines - 1)
		{
			j = -1;
			while (data->tab[i][++j])
				if (data->tab[i][j] != '1' && data->tab[i][j] != ' ')
					ft_free_data(data, data->nb_lines, NULL, "Invalid Map.");
		}
		j = -1;
		while (data->tab[i][++j])
		{
			if (data->tab[i][j] != 'N' && data->tab[i][j] != 'S'
				&& data->tab[i][j] != 'W' && data->tab[i][j] != 'E'
				&& data->tab[i][j] != '0' && data->tab[i][j] != '1')
			{
				printf("error 4\n");
				ft_free_data(data, data->nb_lines, NULL, "Invalid Map.");
			}
			if (data->tab[i][j] == 'N' || data->tab[i][j] == 'S'
				|| data->tab[i][j] == 'W' || data->tab[i][j] == 'E')
			{
				if (player)
				{
					printf("error 5\n");
					ft_free_data(data, data->nb_lines, NULL, "Invalid Map.");
				}
				player = 1;
			}
		}
	}
	if (!player)
	{
		printf("error 6\n");
		ft_free_data(data, data->nb_lines, NULL, "Invalid Map.");
	}
	i = -1;
	while (++i < data->nb_lines)
	{
		if (i == 0)
		{
			// we only check down
			len_1 = ft_strlen(data->tab[i]);
			len_2 = ft_strlen(data->tab[i + 1]);
			if (len_1 < len_2)
			{
				j = len_1 - 2;
				while (++j < len_2)
					if (data->tab[i + 1][j] != '1')
						ft_free_data(data, data->nb_lines, NULL,
							"Invalid Map.");
			}
		}
		else if (i == data->nb_lines - 1)
		{
			// we only check up
			len_1 = ft_strlen(data->tab[i]);
			len_2 = ft_strlen(data->tab[i - 1]);
			if (len_1 < len_2)
			{
				j = len_1 - 2;
				while (++j < len_2)
					if (data->tab[i - 1][j] != '1')
						ft_free_data(data, data->nb_lines, NULL,
							"Invalid Map.");
			}
		}
		else
		{
			len_1 = ft_strlen(data->tab[i]);
			len_2 = ft_strlen(data->tab[i - 1]);
			if (len_1 < len_2)
			{
				j = len_1 - 2;
				while (++j < len_2)
					if (data->tab[i - 1][j] != '1')
						ft_free_data(data, data->nb_lines, NULL,
							"Invalid Map.");
			}
			len_2 = ft_strlen(data->tab[i + 1]);
			if (len_1 < len_2)
			{
				j = len_1 - 2;
				while (++j < len_2)
					if (data->tab[i + 1][j] != '1')
						ft_free_data(data, data->nb_lines, NULL,
							"Invalid Map.");
			}
		}
	}
}
