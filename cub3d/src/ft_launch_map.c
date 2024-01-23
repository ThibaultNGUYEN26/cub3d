/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launch_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchbouki <rchbouki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 23:09:28 by thibault          #+#    #+#             */
/*   Updated: 2024/01/22 14:22:40 by rchbouki         ###   ########.fr       */
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
	data = ft_parsing(buffer);
	printf(GREEN "[INFO]" YELLOW " Initialization of the map...\n" EOC);
	if (len == -1)
	{
		perror(RED "[ERROR]" YELLOW " Reading file" EOC);
		close(fd);
		exit(EXIT_FAILURE);
	}
	printf(GREEN "[INFO]" YELLOW " Opening map...\n" EOC);
	close(fd);
	return (data);
}
