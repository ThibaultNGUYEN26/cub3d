/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 17:11:06 by thibault          #+#    #+#             */
/*   Updated: 2024/01/05 17:31:03 by thibault         ###   ########.fr       */
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

# define WIDTH		1280
# define HEIGHT		720
# define ESC		65307
# define KEY_W		119
# define KEY_A		97
# define KEY_S		115
# define KEY_D		100
# define KEY_LEFT	65361
# define KEY_RIGHT	65363
# define MOVE_SPEED	5

# include "../minilibx-linux/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

typedef struct s_data
{
	int		nb_lines;
	int		longest_line;
	char	**tab;
}	t_data;

typedef struct s_player
{
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	oldDirX;
	double	oldDirY;
	double	rotSpeed;
} t_player;

int			ft_strcmp(char *s1, char *s2);
char		*ft_strdup(char *s);
int			ft_strlen(char *s);
char		*ft_substr(char *s, int start, int len);

t_data		*ft_launch_map(char *map);
t_data		*ft_count_file_lines(ssize_t bytes_read, char *buffer);
int			ft_fill_tab(t_data *data, char *buffer);
void		ft_free_tab(t_data *data);
int			ft_parsing(t_data *data);

void		setup_mlx(t_data *data, t_player *player);
void		ft_draw_minimap(void *mlx, void *window, t_data *data, t_player *player);
t_player	*ft_player_init(void);

#endif