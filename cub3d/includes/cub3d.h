/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 17:11:06 by thibault          #+#    #+#             */
/*   Updated: 2024/01/24 19:02:37 by thibault         ###   ########.fr       */
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
# define MOVE_SPEED	0.1
# define ROT_SPEED	0.05
# define M_PI		3.1415926536897932384626433832795028841971693993751058209749
# define NUM_KEYS	256
# define MAP_SIZE	150

# include "../minilibx-linux/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include <string.h>
# include <limits.h>

typedef struct	s_player
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		olddir_x;
	double		olddir_y;
	double		planeX;
	double		planeY;
}	t_player;

typedef struct	s_texture
{
	char		*t_north;
	char		*t_south;
	char		*t_west;
	char		*t_east;
	void		*img_ptr;
	int			*data;
	int			width;
	int			height;
	int			size_line;
	int			bpp;
	int			endian;
}	t_texture;

typedef struct	s_data
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	void		*minimap_img;
	char		*minimap_addr;
	int			minimap_x;
	int			minimap_y;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			key;
	int			nb_lines;
	int			longest_line;
	char		**tab;
	int			key_status[NUM_KEYS];
	int			floor_color;
	int			ceiling_color;
	int			prev_mouse_x;
	// t_texture	*texture;
	t_texture	texture[4];
	t_player	*player;
}	t_data;

enum TextureIndex {
    TEXTURE_NORTH,
    TEXTURE_SOUTH,
    TEXTURE_WEST,
    TEXTURE_EAST
};

int				ft_strcmp(char *s1, char *s2);
char			*ft_strdup(char *s);
char			*ft_strdup2(int len, char *s);
char			*ft_strjoin(char *s1, char *s2);
int				ft_strlen(char *s);
char			*ft_substr(char *s, int start, int len);
int				ft_atoi(char *str);
char			*ft_itoa(int n);
size_t			ft_strlcpy(char *dst, char *src, size_t dstsize);

int				ft_is_wspaces(char c);
void			error_msg(t_data *data, int *var, char **var_char, char *buffer);
int				check_color_utils(char *buffer, int *k);
int				affect_color(char *str, int *value);
unsigned int	ft_convert_color(int r, int g, int b);

int				check_element_utils(char *buffer, int *k, t_data *data, char *cmp);

t_data			*ft_launch_map(char *map);
t_data			*ft_parsing(char *buffer);
int				check_color(t_data *data, char *buffer, char *cmp, int *k);
void			element_affect(t_data *data, char *cmp, char *value, int test);
void			ft_create_tab(t_data *data, char *buffer, int k);

void			ft_mlx_init(t_data *data);
void			ft_player_init(t_data *data);
void			perform_raycasting(t_data *data);
void			update_player_position(int keycode, t_data *data);
void			draw_minimap(t_data *data);
void			raycast_minimap(t_data *data);

#endif