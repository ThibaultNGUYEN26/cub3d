/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launch_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 23:09:28 by thibault          #+#    #+#             */
/*   Updated: 2023/12/12 15:04:27 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

static int	ft_check_walls()
{
	
}

void	ft_launch_map(char *map)
{
	int		fd;
	ssize_t	bytes_read;
	char	buffer[1024];

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
	while ((bytes_read = read(fd, buffer, 1023)) > 0)
	{
		buffer[bytes_read] = '\0';
		printf(GREEN "[INFO]" YELLOW " Initialization of the map...\n" EOC);
	}
	if (bytes_read == -1) {
		perror(RED "[ERROR]" YELLOW " Reading file" EOC);
		close(fd);
		exit(EXIT_FAILURE);
	}
	printf(GREEN "[INFO]" YELLOW " Opening map...\n" EOC);
	close(fd);
}
