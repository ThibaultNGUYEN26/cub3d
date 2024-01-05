/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchbouki <rchbouki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:06:22 by thibault          #+#    #+#             */
/*   Updated: 2024/01/05 23:31:38 by rchbouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_data	*ft_count_file_lines(ssize_t bytes_read, char *buffer)
{
	t_data *data;
	int	i;
	int line;
	int	temp;

	data = malloc(sizeof(t_data) * 1);
	if (!data)
		return (NULL);
	i = -1;
	data->longest_line = 0;
	line = 0;
	temp = 0;
	data->nb_lines = 1;
	while (++i <= bytes_read)
	{
		if (buffer[i] == '\n')
		{
			line = i - temp - 1;
			temp = i;
			data->nb_lines++;
			if (line > data->longest_line)
				data->longest_line = line;
		}
	}
	return (data);
}

void	ft_free_tab(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_lines)
		free(data->tab[i]);
	free(data->tab);
}

int	ft_fill_tab(t_data *data, char *buffer)
{
	int	i;
	int	j;
	int	k;

	data->tab = malloc(sizeof(char **) * (data->nb_lines + 1));
	if (!data->tab)
		return (0);
	i = -1;
	j = -1;
	k = 0;
	while (++i < data->nb_lines)
	{
		data->tab[i] = malloc(sizeof(char *) * data->longest_line);
		if (!data->tab[i])
			return (0);
		j = -1;
		while (++j <= data->longest_line)
		{
			if (buffer[k] != '\n' && buffer[k] != '\0')
			{
				if (buffer[k] == ' ')
					data->tab[i][j] = '1';
				else
					data->tab[i][j] = buffer[k];
			}
			else
			{
				k++;
				while (j < data->longest_line)
					data->tab[i][j++] = '1';
				data->tab[i][j] = '\0';
				break ;
			}
			k++;
		}
	}
	data->tab[i] = NULL;
	return (1);
}