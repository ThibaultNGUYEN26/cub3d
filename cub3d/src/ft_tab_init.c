/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchbouki <rchbouki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:06:22 by thibault          #+#    #+#             */
/*   Updated: 2024/01/19 15:28:22 by rchbouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_white_spaces(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		if (s[i] != '\f' && s[i] != '\t' && s[i] != '\n' && s[i] != '\r' && s[i] != '\v' && s[i] != ' ')
			return (0);
	return (1);
}

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
	data->longest_line_file = 0;
	line = 0;
	temp = 0;
	data->nb_lines_file = 1;
	while (++i <= bytes_read)
	{
		if (buffer[i] == '\n')
		{
			line = i - temp - 1;
			temp = i;
			data->nb_lines_file++;
			if (line > data->longest_line_file)
				data->longest_line_file = line;
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
	i = -1;
	while (++i < data->nb_lines_file)
		free(data->file[i]);
	free(data->file);
}

static int	ft_fill_map(t_data *data, char **temp, int start)
{
	int	i;
	int	j;
	int	k;
	
	data->tab = malloc(sizeof(char **) * (data->nb_lines + 1));
	if (!temp)
		return (0);
	i = -1;
	while (++i < data->nb_lines)
	{
		data->tab[i] = malloc(sizeof(char *) * data->longest_line);
		if (!data->tab[i])
			return (0);
		j = -1;
		k = 0;
		while (++j <= data->longest_line)
		{
			if (temp[start][k] == '\0')
			{
				while (j < data->longest_line)
					data->tab[i][j++] = '1';
				data->tab[i][j] = '\0';
				break;
			}
			else
			{
				if (temp[start][k] == ' ')
					data->tab[i][j] = '1';
				else
					data->tab[i][j]	= temp[start][k];
			}
			k++;
		}
		start++;
	}
	data->tab[i] = NULL;
	return (1);
}

int	ft_fill_tab(t_data *data, char *buffer)
{
	char	**temp;
	int		start;
	int		end;
	int		i;
	int		j;
	int		k;

	temp = malloc(sizeof(char **) * (data->nb_lines_file + 1));
	if (!temp)
		return (0);
	i = -1;
	k = 0;
	while (++i < data->nb_lines_file)
	{
		temp[i] = malloc(sizeof(char *) * data->longest_line_file);
		if (!temp[i])
			return (0);
		j = 0;
		while (1)
		{
			if (buffer[k] != '\n')
				temp[i][j] = buffer[k];
			else
			{
				temp[i][j] = '\0';
				break;
			}
			k++;
			j++;
		}
	}
	temp[i] = NULL;
	end = data->nb_lines_file - 1;
	while (end >= 0 && ft_white_spaces(temp[end]))
		end--;
	if (end < 0)
		return (0);
	end++;
	start = end;
	while (start >= 0 && !ft_white_spaces(temp[start]))
		start--;
	if (start < 0)
		return (0);
	start++;
	data->nb_lines = end - start;
	if (!ft_fill_map(data, temp, start))
		return (0);
	data->file = malloc(sizeof(char **) * (start));
	if (!data->file)
		return (0);
	i = -1;
	while (++i < start)
	{
		data->file[i] = ft_strdup(temp[i]);
		if (data->file[i] == NULL)
			return (0);
	}
	data->file[i] = NULL;
	i = -1;
	while (++i < data->nb_lines)
		free(temp[i]);
	free(temp);
	data->nb_lines_file = start;
	return (1);
}