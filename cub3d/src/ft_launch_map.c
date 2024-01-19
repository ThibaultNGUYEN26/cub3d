/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launch_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchbouki <rchbouki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 23:09:28 by thibault          #+#    #+#             */
/*   Updated: 2024/01/19 16:04:00 by rchbouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* static void	ft_error(char *error, int fd)
{
	printf(RED "[ERROR] " YELLOW %s "\n" EOC, error);
	close(fd);
	exit(EXIT_FAILURE);
} */

static int	ft_check_extension(char *map)
{
	int		len;
	char	*s;

	len = ft_strlen(map);
	s = ft_substr(map, len - 4, 4);
	if (ft_strcmp(s, ".cub") == 0)
		return (free(s), 1);
	return (free(s), 0);
}

void	ft_print_tab(t_data *data)
{
	printf("FOR FILE :\n");
	printf("longest_line_file : %d\n", data->longest_line_file);
	printf("nb_lines_file : %d\n", data->nb_lines_file);
	for (int i = 0; i < data->nb_lines_file; i++)
	{
		for (int j = 0; j < data->longest_line_file; j++)
			printf("%c", data->tab[i][j]);
		printf("\n");
	}
	printf("FOR TAB :\n");
	printf("mapWidth %d\n", data->longest_line);
	printf("mapHeight %d\n", data->nb_lines);
	for (int i = 0; i < data->nb_lines; i++)
	{
		for (int j = 0; j < data->longest_line; j++)
			printf("%c", data->tab[i][j]);
		printf("\n");
	}
}

t_data	*ft_launch_map(char *map)
{
	int		fd;
	ssize_t	bytes_read;
	char	*buffer = NULL;
	t_data	*data;

	data = NULL;
	if (!ft_check_extension(map))
	{
		printf(RED "[ERROR]" YELLOW " Wrong extension map\n" EOC);
		exit(EXIT_FAILURE);
	}
	fd = open(map, O_RDONLY);
	if (fd == -1) {
		perror(RED "[ERROR]" YELLOW " Opening file" EOC);
		exit(EXIT_FAILURE);
	}
	char	*old_buffer = NULL;
	char	read2[1025];
	int		len = 0;
	while (1)
	{
		bytes_read = read(fd, read2, 1024);
		if (bytes_read > 0)
		{
			if (!buffer)
				old_buffer = ft_strdup("");
			else
				old_buffer = ft_strdup(buffer);
			len += bytes_read;
			read2[bytes_read] = '\0';
			free(buffer);
			buffer = ft_strjoin(old_buffer, read2);
		}
		else
			break;
	}
	buffer[len] = '\0';
	printf(GREEN "[INFO]" YELLOW " Initialization of the map...\n" EOC);
	data = ft_count_file_lines(len, buffer);
	if (!ft_fill_tab(data, buffer))
	{
		printf(RED "[ERROR]" YELLOW " Allocation failure\n" EOC);
		ft_free_tab(data);
		free(data->file);
		free(data);
		close(fd);
		exit(EXIT_FAILURE);
	}
	ft_print_tab(data);
	if (len == -1)
	{
		perror(RED "[ERROR]" YELLOW " Reading file" EOC);
		close(fd);
		exit(EXIT_FAILURE);
	}
	/*
	if (!ft_parsing(data))
	{
		close(fd);
		exit(EXIT_FAILURE);
	} */
	printf(GREEN "[INFO]" YELLOW " Opening map...\n" EOC);
	close(fd);
	return (data);
}
