/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by lmicheli          #+#    #+#             */
/*   Updated: 2024/06/04 15:31:24 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include <structs.h>

// var_init.c

t_game	*init_game(char *map_path);
char	**parse_map(char *map_path, t_game *game);

// srcs/put_image.c
void	*put_xmp(void *mlx, char *filename, int *width, int *height);
t_img	get_img(char *path, t_game *game);

// error_management.c

int		err(char *msg);
void	err_exit(char *msg, t_game *game);
void	free_color(t_color *color);

// splut.c

void	split_map(t_game *game);
int		parse_line(char *line, t_game *game, t_curs curs);

// color.c

char	*itoa_base_hex(int n);
char	*create_color_file(t_color color, t_game *game, int nm);

void	color_fill(int fd);

// map_check.c

char	**parse_map(char *map_path, t_game *game);
void	check_map(t_game *game);
void	check_closed_space(t_game *game, t_curs curs);

// rays.c

double	nor_angle(double angle);
int		is_wall(double x, double y, t_game *game);
t_img	get_texture(t_game *game);
int		unit_circle(double angle, char c);

// inter_h.c

double	horizontal_inter(t_game *game);
int		check_inter(double angle, double *y, double *y_step, int flag);

// inter_v.c

double	vertical_inter(t_game *game);

// pixel_putting.c

void	better_pixel_put(t_game *game, int x, int y, int color);
int		reverse_bit(int c);

// walls.c

void	render_wall(t_game *game);

// distance.c

int		cast_rays(t_game *game);
void	sprite_animation(t_game *game);

// textures.c

void	get_texture_int(t_game *game);
char	**texture_names(void);
t_img	get_floor(char *path, t_game *game, int nm);
void	get_textures(t_game *game);
void	get_texture_adresses(t_game *game);
int		get_texture_id(t_game *game);

// player.c

void	init_player(t_game *game, int x, int y);

// fast_trig.c

void	init_trig(t_game *game);
double	fast_cos(double angle, t_game *game);
double	fast_sin(double angle, t_game *game);
double	fast_tan(double angle, t_game *game);

// smallsteps.c

t_pos	get_wal(t_game *game, t_pos first_step, t_pos steps);
t_pos	smallstep_q1(t_game *game);
t_pos	smallstep_q2(t_game *game);
t_pos	smallstep_q3(t_game *game);
t_pos	smallstep_q4(t_game *game);
t_pos	calculate_first_step_and_steps(t_game *game, double ray_angle);

// pixels.c

void	pixels_init(t_game *game);
void	pixels_update(t_game *game, int x);

// dda.c

void	dda_init(t_game *game);
t_bool	ray_hit(t_game *game);
void	dda_exec(t_game *game);

// frame_to_render.c

void	player_set(t_game *game, t_Myimg *img);
void	set_pixel(t_Myimg *image, int x, int y, int color);
void	frame_set(t_game *game, t_Myimg *image, int x, int y);
void	draw_circle(t_game *game, t_Myimg *img, t_pos pos, t_pos circle);

// render.c

int		render_images(t_game *game);
int		game_loop(t_game *game);
t_Myimg	empty_myimg(t_game *game, int width, int height);
void	set_pixel(t_Myimg *image, int x, int y, int color);

// vectors.c

t_pos	add(t_pos a, t_pos b);
t_pos	sub(t_pos a, t_pos b);
t_pos	mult(t_pos a, double b);
t_pos	scale(t_pos a, double b);
t_pos	rot(t_pos pos, double angle);

// mouse.c

void	mouse(t_game *game);

// rot.c

t_pos	rot(t_pos a, double angle);

// minimap.c

void	minimap(t_game *game, t_Myimg *img, int x, int y);
void	move_player(t_game *game);
void	set_pixel_m(t_Myimg *image, int x, int y, int color);

// bonus_init.c

void	bonus_init(t_game *game);

// sprites.c

void	sprite_calc(t_game *game);
void	sortsprites(int *order, double *dist, int amount);

// animations.c

long	get_time(void);

// doors.c

void	door_opening(t_game *game);

// keyboard.c

int		is_inbounds(t_game *game, t_pos new_pos);
int		game_loop(t_game *game);
int		on_destroy(t_game *data);
int		on_key_press(int keysym, t_game *game);
int		on_key_release(int keysym, t_game *game);

// char_checks.c

void	check_closed_space(t_game *game, t_curs curs);
void	checksmh(t_game *game);
void	check_chars_bonus(t_game *game, t_curs curs);
void	check_chars(t_game *game, t_curs curs);
void	check_and_init_player(t_game *game);

// floor_ceiling.c

char	*color_rgb(char *path, t_game *game, int nm);

// get_textures.c

void	process_texture(t_game *game, t_curs *curs);
void	process_texture2(t_game *game, t_curs *curs);

// sprite_init.c

void	sprite_init(t_game *game);
void	rand_init(t_game *game);

// sprite_calcs.c

void	sort_order(t_norminette *spr, t_game *game);
void	calculate_sprite_transform(t_norminette *spr, t_game *game);
void	calculate_draw_parameters(t_norminette *spr);
void	get_draws(t_norminette *spr, t_game *game);
void	assign_color(t_norminette *spr, t_game *game);

#endif
