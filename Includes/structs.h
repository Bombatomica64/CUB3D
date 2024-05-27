/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:07:39 by lmicheli          #+#    #+#             */
/*   Updated: 2024/05/27 10:17:23 by lmicheli         ###   ########.fr       */
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
# include "../minilibx/mlx.h"
# include "../minilibx/mlx_int.h"
# include "../libft/get_next_line_bonus.h"
# include "../libft/ft_printf.h"

# define ESC 53
# define W 13
# define A 0
# define S 1
# define D 2
# define SCREEN_WIDTH 1900
# define SCREEN_HEIGHT 1000
# define TILE_SIZE 100
# ifndef M_PI
#  define M_PI	3.14159265358979323846
# endif
# ifndef M_PI_2
#  define M_PI_2 1.57079632679489661923	/* pi/2 */
# endif
# ifndef INT_MAX
#  define INT_MAX 2147483647
# endif
# define FOV 120

/**
 * @brief 2D space vector
*/
typedef struct s_pos
{
	double	x;
	double	y;
}	t_pos;

typedef struct s_player
{
	double		x;
	double		y;
	double		angle;
	t_pos		pos; // 0, 50, 0
	t_pos		dir; // 0, 50, 2
	double		dist_proj; // distance from player to projection plane
}	t_player;

typedef struct s_color
{
	char	*r;
	char	*g;
	char	*b;
}	t_color;

typedef struct s_ray
{
	double		angle; //angle of ray
	double		dist; //distance to wall
	t_pos		next; //next intersection point
	int			i_ray; //ray number
	int			flag; //1 = vertical, 0 = horizontal
}	t_ray;

typedef struct s_texture
{
	char	**txts;
	char	**txt_nm; //alloced in var_init.c
	t_img	imgs[6]; // 0 = NO, 1 = SO, 2 = WE, 3 = EA, 4 = C, 5 = F
	size_t	addr[6]; // 0 = NO, 1 = SO, 2 = WE, 3 = EA, 4 = C, 5 = F
	int		endians[6];
}	t_texture;

typedef struct s_input
{
	int		file_len;
	int		fd;
	t_bool	map_str;
	char	**map_and_txt;
}	t_input;

typedef struct s_curs
{
	int		i;
	int		j;
	int		k;
	int		status;
}	t_curs;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	char		**map;
	int			map_width;
	int			map_height;
	double		sin_table[360];
	double		cos_table[360];
	t_ray		ray;
	t_input		input;
	t_player	player;
	t_texture	txts;
	double		fov_rd;
}	t_game;

#endif