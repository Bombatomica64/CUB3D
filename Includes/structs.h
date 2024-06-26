/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by lmicheli          #+#    #+#             */
/*   Updated: 2024/06/04 18:02:34 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <colours.h>
# include <stdbool.h>
# include "../minilibx/mlx.h"
# include "../minilibx/mlx_int.h"
# include "../libft/get_next_line_bonus.h"
# include "../libft/ft_printf.h"

# define ESC 53
# define W 13
# define A 0
# define S 1
# define D 2
# define SCREEN_WIDTH 720.0
# define SCREEN_HEIGHT 480.0
# define TILE_SIZE 256
# define BACKGROUND_SIZE 512
# define MOVE_SPEED 0.1
# define ROT_SPEED 0.1
# define MROT_SPEED 0.005
# define MINIMAP_SCALE 10
# ifndef M_PI
#  define M_PI	3.14159265358979323846
# endif
# ifndef M_PI_2
#  define M_PI_2 1.57079632679489661923	/* pi/2 */
# endif
# ifndef M_PI_4
#  define M_PI_4 0.78539816339744830962	/* pi/4 */
# endif
# ifndef INT_MAX
#  define INT_MAX 2147483647
# endif
# ifndef BONUS
#  define BONUS 0
# endif
# define UDIV 1.2
# define VDIV 1.2
# define VMOVE 60
# define FOV 75
# define P_RADIUS 3.5
# if BONUS
#  include <time.h>
#  include <sys/time.h>
# endif

/**
 * @brief 2D space vector
*/
typedef struct s_pos
{
	double	x;
	double	y;
	int		wall_hit; // 0 = NORTH , 1 = EAST, 2 = WEST, 3 = SOUTH
}	t_pos;

typedef struct s_curs
{
	int		i;
	int		j;
	int		k;
	int		status;
}	t_curs;

typedef struct s_norminette
{
	t_curs	curs;
	t_pos	sprite;
	t_pos	transform;
	double	invdet;
	int		sprite_screen_x;
	int		v_move_screen;
	int		sprite_height;
	int		sprite_width;
	int		drw_start_y;
	int		drw_end_y;
	int		drw_start_x;
	int		drw_end_x;
	int		stripe;
	int		texx;
	int		texy;
	int		color;
	int		d;
}	t_norminette;
typedef struct s_player
{
	double		x;
	double		y;
	double		angle;
	char		name;
	t_pos		pos;
	t_pos		dir;
	t_pos		plane;
}	t_player;

typedef struct s_color
{
	char	*r;
	int		r_value;
	char	*g;
	int		g_value;
	char	*b;
	int		b_value;
	char	*color_str;
	char	*path;
	int		color_value;
	char	*color_name;
	int		i;
	int		len;
	int		start;
}	t_color;

typedef struct s_ray
{
	double		camera_x; //x coordinate of the camera plane
	t_pos		dir; //direction of the ray
	t_pos		map; //current map square
	t_pos		step; //lenght of the steps
	t_pos		side_dist; //distance to the next side
	t_pos		delta_dist; //distance between two sides
	double		dist; //distance to wall
	double		wall_x; //x coordinate of the wall
	int			side; // 0 = NORTH , 1 = EAST, 2 = WEST, 3 = SOUTH
	double		line_len; //lenght of the line to draw
	int			drw_start; //start of the line to draw
	int			drw_end; //end of the line to draw
	int			i_ray; //ray number
}	t_ray;

typedef struct s_chadimg
{
	t_img	img;
	int		bpp;
	int		size_line;
	int		endian;
	int		nb_txt;
	int		*data;
}	t_Myimg;

/**
 * 0 = NORTH, 
 * 1 = EAST, 
 * 2 = WEST, 
 * 3 = SOUTH,
 * 4 = FLOOR, 
 * 5 = CEILING,
 * 6 = DOOR,
 * 7 = SPRITE
 * 8 = SPRITE_animation
 * 9 = SPRITE_animation2
 * 10 = open door
*/
typedef struct s_texture
{
	char		**txts;
	char		**txt_nm; //alloced in var_init.c
	u_int8_t	nb_txt;
	t_Myimg		imgs[11];
	int			x;
	int			y;
	double		pos;
	double		step;
}	t_texture;

typedef struct s_input
{
	int		file_len;
	int		fd;
	t_bool	map_str;
	char	**map_and_txt;
}	t_input;

typedef struct s_keys
{
	int		w;
	int		s;
	int		a;
	int		d;
	int		right;
	int		left;
}	t_keys;

typedef struct s_pair
{
	double	first;
	int		second;
}			t_pair;

typedef struct s_sprite
{
	double	zbuffer[(int)SCREEN_WIDTH];
	double	*sprite_dist;
	int		*sprite_order;
	t_pos	*pos;
	int		nb_sprites;
	int		text_nb;
}	t_sprite;

typedef struct s_door
{
	char		wall_hit;
	int			doorx;
	int			doory;
	int			wallx;
	int			wally;
	int			door_open;
	bool		insidedoor;
}	t_door;

typedef struct s_bonus
{
	int			height;
	int			width;
	char		**minimap;
	t_pos		player;
	t_sprite	sprite;
	int			door;
	t_door		doors;
	int			frame;
	long		time;
	long		frame_time;
	char		*frames;
}	t_bonus;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	char		**map;
	int			**pixels;
	int			map_width;
	int			map_height;
	double		sin_table[360];
	double		cos_table[360];
	t_ray		ray;
	t_input		input;
	t_player	player;
	t_texture	txts;
	double		fov_rd;
	t_keys		keys;
	t_pos		mouse;
	t_bonus		bonus;
}	t_game;

#endif
