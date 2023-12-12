/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 17:11:06 by thibault          #+#    #+#             */
/*   Updated: 2023/12/12 14:33:09 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define RED		"\033[1;31m"
# define GREEN		"\033[1;32m"
# define YELLOW		"\033[1;33m"
# define BLUE		"\033[1;34m"
# define WHITE		"\033[1;37m"
# define EOC		"\033[0;0m"

# include "../minilibx-linux/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

int		ft_strcmp(char *s1, char *s2);
char	*ft_strdup(char *s);
int		ft_strlen(char *s);
char	*ft_substr(char *s, int start, int len);

void	ft_launch_map(char *map);

#endif