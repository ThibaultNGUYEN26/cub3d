/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchbouki <rchbouki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 17:11:06 by thibault          #+#    #+#             */
/*   Updated: 2024/01/26 15:03:53 by rchbouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "define.h"
# include "struct.h"

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
void			error_msg(t_data *data, t_var *var, char *buffer);
int				color_utils(char *buffer, int *k);
int				affect(char *buffer, int *k, int i, int *value);
unsigned int	ft_convert_color(t_color color);

int				ft_init_data(t_data **data);
int				ft_init_var(t_var **var);
int				check_element_utils(char *buffer, int *k, t_data *data, char *cmp);
void			ft_skip(char *buffer, int *k, int *start);
int				element_loop(t_data *data, t_var *var, char *buffer, int *k);

int				end_parsing(int *k, int start, t_var *var);
int				buffer_switch(char *buffer, int *k, int *start);
void			ft_affect_color(t_data *data, char *cmp, t_color color);
void			ft_skip_empty(t_data *data, char *buffer, int *k);
void			ft_count_lines(char *buffer, int *k, t_data *data);

t_data			*ft_launch_map(char *map);

t_data			*ft_parsing(char *buffer);
int				ft_check_element(char *buffer, int *k, t_data *data, char *cmp);
int				check_color(t_data *data, char *buffer, char *cmp, int *k);
void			element_affect(t_data *data, char *cmp, char *value, int test);

void			ft_check_surroundings(char *buf, int *k, int *i, t_data *data);
void			tab_init_utils(char *buffer, int *k, t_data *data);
void			ft_check_player(t_data *data, int *player);
void			check_line(t_data *data, int line_1, int line_2);

void			ft_free_data(t_data *data, int i, char *buffer, char *msg);
int				empty_line(char *str);
int				ft_last_in_line(char *line);
void			ft_create_tab(t_data *data, char *buffer, int k);

void			ft_mlx_init(t_data *data);
void			ft_player_init(t_data *data);
void			perform_raycasting(t_data *data);
void			update_player_position(int keycode, t_data *data);

int				ft_longest_line(t_data *data);
void			draw_minimap(t_data *data);
void			raycast_minimap(t_data *data, int longest);

#endif