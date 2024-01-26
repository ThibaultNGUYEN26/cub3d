/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launch_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchbouki <rchbouki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 23:09:28 by thibault          #+#    #+#             */
/*   Updated: 2024/01/26 16:33:15 by rchbouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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

static int	ft_init_launch(char *map)
{
	int	fd;

	if (!ft_check_extension(map))
	{
		printf(RED "[ERROR]" YELLOW " Wrong extension of map\n" EOC);
		exit(EXIT_FAILURE);
	}
	fd = open(map, O_RDONLY);
	if (fd == -1)
	{
		perror(RED "[ERROR]" YELLOW " Opening file" EOC);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

static void	read_utils(char **buffer, char *read2, int *len, ssize_t bytes_read)
{
	char	*old_buffer;

	if (!(*buffer))
		old_buffer = ft_strdup("");
	else
		old_buffer = ft_strdup(*buffer);
	*len += bytes_read;
	read2[bytes_read] = '\0';
	free(*buffer);
	*buffer = ft_strjoin(old_buffer, read2);
}

static char	*read_buffer(int fd)
{
	int		len;
	ssize_t	bytes_read;
	char	*buffer;
	char	read2[1025];

	buffer = NULL;
	len = 0;
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, read2, 1024);
		if (bytes_read > 0)
			read_utils(&buffer, read2, &len, bytes_read);
	}
	if (len == -1)
		return (NULL);
	buffer[len] = '\0';
	return (buffer);
}

t_data	*ft_launch_map(char *map)
{
	int		fd;
	char	*buffer;
	t_data	*data;

	data = NULL;
	fd = ft_init_launch(map);
	buffer = read_buffer(fd);
	if (!buffer)
	{
		perror(RED "[ERROR]" YELLOW " Reading file" EOC);
		close(fd);
		exit(EXIT_FAILURE);
	}
	data = ft_parsing(buffer);
	if (!data)
	{
		printf(RED "[ERROR]" YELLOW " Allocation failure.\n" EOC);
		exit(EXIT_FAILURE);
	}
	printf(GREEN "[INFO]" YELLOW " Initialization of the map...\n" EOC);
	printf(GREEN "[INFO]" YELLOW " Opening map...\n" EOC);
	close(fd);
	return (data);
}
