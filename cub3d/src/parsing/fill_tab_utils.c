/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tab_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchbouki <rchbouki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 21:11:26 by rchbouki          #+#    #+#             */
/*   Updated: 2024/01/25 22:19:26 by rchbouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_check_surroundings(char *buf, int *k, int *i, t_data *data)
{
	int		start;
	char	*str;
	int		end;

	end = *k;
	while (buf[*k])
	{
		if (!ft_is_wspaces(buf[*k]) && buf[*k] != '\n'
			&& buf[*k] != '\0')
			ft_free_data(data, 0, buf, "Invalid Map.\n");
		*k += 1;
	}
	*k = *i;
	while (*k < end)
	{
		start = *k;
		while (buf[*k] && buf[*k] != '\n')
			*k += 1;
		while (ft_is_wspaces(buf[start]))
			start++;
		str = ft_substr(buf, start, *k - start);
		if (buf[start] != '1' || buf[*k - ft_last_in_line(str) - 1] != '1')
			ft_free_data(data, 0, buf, "Invalid Map.\n");
		*k += 1;
	}
}

void	tab_init_utils(char *buffer, int *k, t_data *data)
{
	int	start;
	int	i;

	i = -1;
	while (++i < data->nb_lines)
	{
		start = *k;
		while (buffer[*k] && buffer[*k] != '\n')
		{
			if (ft_is_wspaces(buffer[*k]))
				buffer[*k] = '1';
			*k += 1;
		}
		data->tab[i] = ft_substr(buffer, start, *k - start);
		if (!(data->tab[i]))
			ft_free_data(data, i, buffer, "Allocation Failure.");
		if (buffer[*k])
			*k += 1;
		printf("%s\n", data->tab[i]);
	}
	data->tab[i] = NULL;
}

static void	first_last_line(t_data *data, int i)
{
	int	j;

	j = -1;
	while (data->tab[i][++j])
		if (data->tab[i][j] != '1' && data->tab[i][j] != ' ')
			ft_free_data(data, data->nb_lines, NULL, "Invalid Map.");
}

void	ft_check_player(t_data *data, int *player)
{
	int	i;
	int	j;

	i = -1;
	while (++i < data->nb_lines)
	{
		if (i == 0 || i == data->nb_lines - 1)
			first_last_line(data, i);
		j = -1;
		while (data->tab[i][++j])
		{
			if (data->tab[i][j] != 'N' && data->tab[i][j] != 'S'
				&& data->tab[i][j] != 'W' && data->tab[i][j] != 'E'
				&& data->tab[i][j] != '0' && data->tab[i][j] != '1')
				ft_free_data(data, data->nb_lines, NULL, "Invalid Map.");
			if (data->tab[i][j] == 'N' || data->tab[i][j] == 'S'
				|| data->tab[i][j] == 'W' || data->tab[i][j] == 'E')
			{
				if (*player)
					ft_free_data(data, data->nb_lines, NULL, "Invalid Map.");
				*player = 1;
			}
		}
	}
}

void	check_line(t_data *data, int line_1, int line_2)
{
	int	j;
	int	len_1;
	int	len_2;

	len_1 = ft_strlen(data->tab[line_1]);
	len_2 = ft_strlen(data->tab[line_2]);
	if (len_1 < len_2)
	{
		j = len_1 - 2;
		while (++j < len_2)
			if (data->tab[line_2][j] != '1')
				ft_free_data(data, data->nb_lines, NULL,
					"Invalid Map.");
	}
}
