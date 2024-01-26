/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibnguy <thibnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 17:11:06 by thibault          #+#    #+#             */
/*   Updated: 2024/01/26 21:37:44 by thibnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "define.h"
# include "struct.h"

/* --- GRAPHICS --- */

/* FT_DISPLAY */
void			ft_regenerate(t_data *data);
void			load_texture(t_data *data, int textureIndex, char *filePath);
/* FT_DRAW_MINIMAP */
void			draw_minimap(t_data *data);
/* FT_MINI_RAYCAST */
void			raycast_minimap(t_data *data, int longest);
/* FT_MLX_INIT */
void			ft_mlx_init(t_data *data);
/* FT_MLX_UTILS */
int				ft_close_window(t_data *data);
void			ft_free_utils(t_data *data);
void			free_textures(t_data *data);
int				ft_key_hook(int key, t_data *data);
int				ft_key_release_hook(int key, t_data *data);
/* FT_PLAYER_UTILS */
void			update_player_position(int keycode, t_data *data);
/* FT_PLAYER */
void			ft_player_init(t_data *data);
/* FT_RAYCAST_UTILS */
void			init_utils(t_dda *dda, int a, double b, int test);
void			dda_loop_utils(t_dda *dda, int test);
void			tex_index_init(t_dda *dda, t_tex_dda *tex, int test);
void			draw_vertical_line(t_data *data, int x, int draw_start, \
				int color);
/* FT_RAYCASTING */
void			perform_raycasting(t_data *data);

/* --- LIBFT --- */
int				ft_atoi(char *str);
char			*ft_itoa(int n);
int				ft_strcmp(char *s1, char *s2);
char			*ft_strdup(char *s);
char			*ft_strdup2(int len, char *s);
char			*ft_strjoin(char *s1, char *s2);
size_t			ft_strlcpy(char *dst, char *src, size_t dstsize);
int				ft_strlen(char *s);
char			*ft_substr(char *s, int start, int len);

/* --- PARSING --- */

/* CHECK_PARSING_2 */
int				end_parsing(int *k, int start, t_var *var);
int				buffer_switch(char *buffer, int *k, int *start);
void			ft_affect_color(t_data *data, char *cmp, t_color color);
void			ft_skip_empty(t_data *data, char *buffer, int *k);
void			ft_count_lines(char *buffer, int *k, t_data *data);
/* CHECK_PARSING */
int				ft_init_data(t_data **data);
int				ft_init_var(t_var **var);
int				check_element_utils(char *buffer, int *k, t_data *data, \
				char *cmp);
void			ft_skip(char *buffer, int *k, int *start);
int				element_loop(t_data *data, t_var *var, char *buffer, int *k);
/* FILL_TAB_UTILS */
void			ft_check_surroundings(char *buf, int *k, int *i, t_data *data);
void			tab_init_utils(char *buffer, int *k, t_data *data);
void			ft_check_player(t_data *data, int *player);
void			check_line(t_data *data, int line_1, int line_2);
/* FT_FILL_TAB */
void			ft_free_data(t_data *data, int i, char *buffer, char *msg);
int				empty_line(char *str);
int				ft_last_in_line(char *line);
void			ft_create_tab(t_data *data, char *buffer, int k);
/* FT_LAUNCH_MAP */
t_data			*ft_launch_map(char *map);
/* FT_PARSING */
void			element_affect(t_data *data, char *cmp, char *value, int test);
int				check_color(t_data *data, char *buffer, char *cmp, int *k);
int				ft_check_element(char *buffer, int *k, t_data *data, char *cmp);
t_data			*ft_parsing(char *buffer);
/* PARSING_UTILS */
int				ft_is_wspaces(char c);
void			error_msg(t_data *data, t_var *var, char *buffer);
int				color_utils(char *buffer, int *k);
int				affect(char *buffer, int *k, int i, int *value);
unsigned int	ft_convert_color(t_color color);

#endif