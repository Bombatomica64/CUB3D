/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by lmicheli          #+#    #+#             */
/*   Updated: 2024/05/29 16:57:41 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include <structs.h>

//var_init.c

t_game	*init_game(char *map_path);
char	**parse_map(char *map_path, t_game *game);

// srcs/put_image.c
void	*put_xmp(void *mlx, char *filename, int *width, int *height);
t_img	get_img(char *path, t_game *game);

// error_management.c

int		err(char *msg);
void	err_exit(char *msg, t_game *game);

// splut.c

void	split_map(t_game *game);
int		parse_line(char *line, t_game *game);

// color.c

char	*itoa_base_hex(int n);
char	*create_color_file(t_color color, t_game *game, int nm);

// map_check.c

char	**parse_map(char *map_path, t_game *game);
void	check_map(t_game *game);
void	check_closed_space(t_game *game, t_curs curs);

//rays.c

double	nor_angle(double angle);
int		is_wall(double x, double y, t_game *game);
t_img	get_texture(t_game *game);
int		unit_circle(double angle, char c);

//inter_h.c

double	horizontal_inter(t_game *game);
int		check_inter(double angle, double *y, double *y_step, int flag);

//inter_v.c

double	vertical_inter(t_game *game);

//pixel_putting.c

void	better_pixel_put(t_game *game, int x, int y, int color);
int		reverse_bit(int c);

//walls.c

void	render_wall(t_game *game);

//distance.c

int		cast_rays(t_game *game);

//textures.c

void	get_texture_int(t_game *game);
char	**texture_names( void );
t_img	get_floor(char *path, t_game *game, int nm);
void	get_textures(t_game *game);
void	get_texture_adresses(t_game *game);
int		get_texture_id(t_game *game);

//player.c

void	init_player(t_game *game, int x, int y);

//fast_trig.c

void	init_trig(t_game *game);
double	fast_cos(double angle, t_game *game);
double	fast_sin(double angle, t_game *game);
double	fast_tan(double angle, t_game *game);

//smallsteps.c

t_pos	get_wal(t_game *game, t_pos first_step, t_pos steps);
t_pos	smallstep_q1(t_game *game);
t_pos	smallstep_q2(t_game *game);
t_pos	smallstep_q3(t_game *game);
t_pos	smallstep_q4(t_game *game);
t_pos	calculate_first_step_and_steps(t_game *game, double ray_angle);

//pixels.c

void	pixels_init(t_game *game);
void	pixels_update(t_game *game, int x);

//render.c

int		render_images(t_game *game);

//vectors.c

t_pos	add(t_pos a, t_pos b);
t_pos	sub(t_pos a, t_pos b);
t_pos	mult(t_pos a, double b);
t_pos	scale(t_pos a, double b);

#endif
