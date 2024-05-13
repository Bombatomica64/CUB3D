/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:07:39 by lmicheli          #+#    #+#             */
/*   Updated: 2024/05/13 18:14:24 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <functions.h>

# define ESC 53
# define W 13
# define A 0
# define S 1
# define D 2
# define CAMERA_HEIGHT 1.0
# define FOV 90
# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1080

typedef struct s_pos
{
	double	x;
	double	y;
	double	z;
}	t_pos;

typedef struct s_img
{
	void	*img;
	int		height;
	int		width;
}	t_img;

typedef struct s_player
{
	t_pos		pos; // 0, 50, 0
	t_pos		dir; // 0, 50, 2
	t_pos		plane; // 0, 1, 0
}	t_player;

typedef struct s_texture
{
	t_img	no;
	t_img	su;
	t_img	we;
	t_img	es;
}	t_texture;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	char		**map;
	int			map_width;
	int			map_height;
	t_player	player;
	t_texture	texture;
}	t_game;

#endif