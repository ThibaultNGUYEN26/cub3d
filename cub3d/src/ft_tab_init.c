/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:06:22 by thibault          #+#    #+#             */
/*   Updated: 2024/01/20 18:08:20 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_white_spaces(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] != '\f' && s[i] != '\t' && s[i] != '\n' && s[i] != '\r' && s[i] != '\v' && s[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

t_data	*ft_count_file_lines(ssize_t bytes_read, char *buffer)
{
	t_data *data;
	int		i;

	data = malloc(sizeof(t_data) * 1);
	if (!data)
		return (NULL);
	i = -1;
	data->nb_lines_file = 1;
	while (++i <= bytes_read)
		if (buffer[i] == '\n')
			data->nb_lines_file++;
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
	data->longest_line = 0;
	i = -1;
	j = start;
	while (++i < data->nb_lines)
	{
		k = 0;
		while (temp[start][k])
			k++;
		if (k > data->longest_line)
			data->longest_line = k;
		start++;
	}
	start = j;
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
		j = k;
		while (1)
		{
			if (buffer[k] != '\n' && buffer[k] != '\0')
				k++;
			else
			{
				temp[i] = ft_substr(buffer, j, k - j);
				if (!temp[i])
				{
					j = 0;
					while (j < i)
						free(temp[j]);
					free(temp);
					return (0);
				}
				k++;
				break;
			}
		}
		/* printf("%s\n", temp[i]); */
	}
	temp[i] = NULL;
	end = data->nb_lines_file - 1;
	printf("end avant sa boucle : %d\n", end);
	while (end >= 0 && ft_white_spaces(temp[end]))
		end--;
	if (end < 0)
	{
		printf("ligne 159 failure\n");
		return (0);
	}
	start = end;
	while (start >= 0 && !ft_white_spaces(temp[start]))
		start--;
	/* if (ft_white_spaces(temp[start]))
	{
		while ()
	} */
	if (start < 0)
	{
		printf("start : %d, end : %d, temp[end] : %s\n", start, end, temp[end]);
		printf("ligne 171 failure\n");
		return (0);
	}
	start++;
	data->nb_lines = end - start + 1;
	printf("data->nb_lines : %d\n", data->nb_lines);
	printf("data->nb_lines_file : %d\n", data->nb_lines_file);
	if (!ft_fill_map(data, temp, start))
		return (0);
	data->file = malloc(sizeof(char **) * (start + 1));
	if (!data->file)
		return (0);
	i = -1;
	while (++i < start)
	{
		data->file[i] = ft_strdup(temp[i]);
		if (data->file[i] == NULL)
			return (0);
		/* printf("%s\n", data->file[i]); */
	}
	data->file[i] = NULL;
	i = -1;
	while (++i < data->nb_lines)
		free(temp[i]);
	free(temp);
	data->nb_lines_file = start;
	return (1);
}