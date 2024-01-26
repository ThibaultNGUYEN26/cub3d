/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 23:26:07 by rchbouki          #+#    #+#             */
/*   Updated: 2024/01/26 21:33:07 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_player
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		olddir_x;
	double		plane_x;
	double		plane_y;
	double		old_plane_x;
	double		strafe_step_x;
	double		strafe_step_y;
	double		move_step_x;
	double		move_step_y;
}	t_player;

typedef struct s_texture
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

typedef struct s_data
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
	int			forward;
	int			backward;
	int			left;
	int			right;
	int			turn_left;
	int			turn_right;
	t_texture	texture[4];
	t_player	*player;
	int			delta_accumulator;
	int			frame_count;
	int			bonus;
}	t_data;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_var
{
	int		*var_tab;
	char	**var_char;
}	t_var;

typedef struct s_minimap
{
	int		width;
	int		height;
	double	aspect_ratio;
	int		player_x;
	int		player_y;
	int		*img;
	int		x;
	int		y;
	int		index_x;
	int		index_y;
	int		index;
}	t_minimap;

typedef struct s_coord
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	raydir_x;
	double	raydir_y;
}	t_coord;

typedef struct s_dda
{
	int				hit;
	int				map_x;
	int				map_y;
	double			camera_x;
	double			raydir_x;
	double			raydir_y;
	int				step_x;
	int				step_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			side_dist_x;
	double			side_dist_y;
	double			wall_x;
	double			wall_dist;
	int				line_height;
	int				side;
	int				draw_start;
	int				draw_end;
}	t_dda;

typedef struct s_tex_dda
{
	unsigned int	d;
	int				tex_width;
	int				tex_x;
	unsigned int	tex_y;
	int				tex_height;
	int				tex_index;
}	t_tex_dda;

typedef struct s_collision
{
	int				map_x;
	int				map_y;
	int				adj_x;
	int				adj_y;
	double			frac_x;
	double			frac_y;
}	t_collision;

#endif
