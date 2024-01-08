/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 17:11:06 by thibault          #+#    #+#             */
/*   Updated: 2024/01/08 19:35:51 by thibault         ###   ########.fr       */
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
# define MOVE_SPEED	1
# define FOV_LENGTH	5
# define ROT_SPEED	0.5
# define M_PI		3.1415926536897932384626433832795028841971
# define SCALE		8

# include "../minilibx-linux/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include <string.h>

typedef struct	s_player
{
	double		posX;
	double		posY;
	double		dirX;
	double		dirY;
	double		oldDirX;
	double		oldDirY;
	double		rotSpeed;
}	t_player;

typedef struct	s_data
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	void		*img2;
	char		*addr2;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			key;
	int			nb_lines;
	int			longest_line;
	char		**tab;
	t_player	*player;
}	t_data;

int			ft_strcmp(char *s1, char *s2);
char		*ft_strdup(char *s);
int			ft_strlen(char *s);
char		*ft_substr(char *s, int start, int len);

t_data		*ft_launch_map(char *map);
t_data		*ft_count_file_lines(ssize_t bytes_read, char *buffer);
int			ft_fill_tab(t_data *data, char *buffer);
void		ft_free_tab(t_data *data);
int			ft_parsing(t_data *data);

void		setup_mlx(t_data *data);
void		ft_draw_minimap(t_data *data);
void		ft_minimap(t_data *data);
void		ft_player_init(t_data *data);
void		handle_key_event(int key, t_data *data);
void		ft_rotate_player(int key, t_player *player);
void		ft_mlx_put_pixel(int x, int y, int color, t_data *data);

#endif