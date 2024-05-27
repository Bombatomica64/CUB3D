/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:39:43 by lmicheli          #+#    #+#             */
/*   Updated: 2024/05/27 13:00:21 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>

double	get_wall_dist(t_game *game)
{
	t_pos	steps;

	steps.x = TILE_SIZE / tan(game->ray.angle);
	if (game->ray.angle > M_PI
		|| (game->ray.angle > 0 && game->ray.angle < M_PI))
		steps.x = -steps.x;
	steps.y = TILE_SIZE * tan(game->ray.angle);
	if (game->ray.angle > M_PI / 2 && game->ray.angle < 3 * M_PI / 2)
		steps.y = -steps.y;
	printf("step x: %f, step y: %f\n", steps.x, steps.y);
	game->ray.next.x = floor(game->player.x) + steps.x;
	game->ray.next.y = floor(game->player.y) + steps.y;
	while (is_wall(game->ray.next.x, game->ray.next.y, game) == 0
		&& game->ray.next.x >= 0 && game->ray.next.x < game->map_width - 1
		&& game->ray.next.y >= 0 && game->ray.next.y < game->map_height - 1)
	{
		game->ray.next.x += steps.x;
		game->ray.next.y += steps.y;
	}
	return (sqrt(pow(game->player.x - game->ray.next.x, 2)
			+ pow(game->player.y - game->ray.next.y, 2)));
}

// Q2 Q1
// Q3 Q4

void	cast_rays(t_game *game)
{
	// double	game->fov_rd = FOV * M_PI / 180;  conversione in radianti ??? c'e' gia
	printf(BLUE "game->fov_rd:%f\n" END, game->fov_rd);
	double	FOV2 = game->fov_rd / 2;
	double	alpha = FOV2; // angolo iniziale
	// double alpha_tot = game->ray.angle + FOV2; non funge game->ray.angle
	double alpha_tot = M_PI_2 + FOV2; // quindi lo hardcodo a 90 (N) + 45
	printf(BLUE "alpha_tot:%f\n" END, alpha_tot);
	double alpha_current = alpha_tot;
	double rotaz = alpha / (SCREEN_WIDTH / 2);
	int	signx;
	int	signy;
	//--calcolo piccolo di delta x--
	int		signalpha = -1;
	int		displayx = 0;
	double	d;
	t_pos	w_pos;

	while (alpha_current > alpha_tot - game->fov_rd) // angolo del player - FOV/2 ???
	{
		if (alpha_current >= 0 && alpha_current < M_PI_2)
			w_pos = smallstep_q1(game);
		else if (alpha_current >= M_PI_2 && alpha_current < M_PI)
			w_pos = smallstep_q2(game);
		else if (alpha_current >= M_PI && alpha_current < 3 * M_PI_2)
			w_pos = smallstep_q3(game);
		else
			w_pos = smallstep_q4(game);
		d = sqrt(pow(game->player.x - w_pos.x, 2) + pow(game->player.y - w_pos.y, 2));
		
		alpha_current = alpha_current - rotaz;
		alpha = alpha + rotaz * (signalpha);
		if (alpha <= 0)
		{
			signalpha = 1;
		}
	}

	return ;
}
/*
void	ray_casting(t_cub3d *data, float ray_angle,
	int id_ray, mlx_image_t *img)
{
	double	height_wall;
	int		xstart;
	int		ystart;
	int		xend;
	int		yend;

	data->dist = data->dist * cos(to_rad(ray_angle) - to_rad(data->angle));
	height_wall = ((data->size_shape) * HEIGHT_WIN) / data->dist;
	xstart = id_ray;
	xend = id_ray;
	ystart = (HEIGHT_WIN / 2) - (height_wall / 2);
	yend = (HEIGHT_WIN / 2) + (height_wall / 2);
	if (yend > HEIGHT_WIN)
		yend = HEIGHT_WIN;
	data->texture_offset_x = data->present_texture * img->width;
	data->wall_start = ystart;
	while (ystart < yend)
	{
		data->texture_offset_y = (((float)ystart - (float)data->wall_start)
				/ (float)height_wall) * img->height;
		if (ystart >= 0 && ystart < HEIGHT_WIN)
			mlx_put_pixel(data->img, xstart, (int)ystart,
				get_texel(img, data->texture_offset_x, data->texture_offset_y));
		ystart += 1;
	}
}

void	check_ray_draw_down(t_cub3d *data, float ray_angle)
{
	data->hores_inters_y = floor((data->py / data->size_shape) + 1)
		* data->size_shape;
	data->hores_inters_x = data->px + (data->hores_inters_y - data->py)
		/ tan(to_rad(ray_angle));
	data->next_hor_inters_y = data->hores_inters_y + data->size_shape;
	data->next_hor_inters_x = data->hores_inters_x + ((data->next_hor_inters_y
				- data->hores_inters_y) / tan(to_rad(ray_angle)));
	data->step_hor_y = data->size_shape;
	data->step_hor_x = data->next_hor_inters_x - data->hores_inters_x;
	while (((int)(data->hores_inters_x / data->size_shape)) < data->width_map
		&& ((int)(data->hores_inters_y / data->size_shape)) < data->height_map
		&& data->hores_inters_x >= 0 && data->hores_inters_y >= 0
		&& data->map[(int)(data->hores_inters_y
			/ data->size_shape)][(int)(data->hores_inters_x
			/ data->size_shape)] != '1')
	{
		data->hores_inters_y += data->step_hor_y;
		data->hores_inters_x += data->step_hor_x;
	}
}

void	check_ray_draw_up(t_cub3d *data, float ray_angle)
{
	data->hores_inters_y = floor((data->py / data->size_shape))
		* data->size_shape;
	data->hores_inters_x = data->px - ((data->py - data->hores_inters_y)
			/ tan(to_rad(ray_angle)));
	data->next_hor_inters_y = data->hores_inters_y - data->size_shape;
	data->next_hor_inters_x = data->hores_inters_x - ((data->hores_inters_y
				- data->next_hor_inters_y) / tan(to_rad(ray_angle)));
	data->step_hor_y = data->size_shape;
	data->step_hor_x = data->next_hor_inters_x - data->hores_inters_x;
	while (((int)(data->hores_inters_x / data->size_shape)) < data->width_map
		&& ((int)((data->hores_inters_y - 1)
				/ data->size_shape)) < data->height_map
		&& data->hores_inters_x >= 0 && data->hores_inters_y >= 0
		&& data->map[(int)((data->hores_inters_y - 1)
			/ data->size_shape)][(int)(data->hores_inters_x
			/ data->size_shape)] != '1')
	{
		data->hores_inters_y -= data->step_hor_y;
		data->hores_inters_x += data->step_hor_x;
	}
}

void	check_ray_draw_right(t_cub3d *data, float ray_angle)
{
	data->vertcl_inters_x = floor((data->px / data->size_shape) + 1)
		* data->size_shape;
	data->vertcl_inters_y = data->py - ((data->px - data->vertcl_inters_x)
			* tan(to_rad(ray_angle)));
	data->next_ver_inters_x = data->vertcl_inters_x + data->size_shape;
	data->next_ver_inters_y = data->vertcl_inters_y - ((data->vertcl_inters_x
				- data->next_ver_inters_x) * tan(to_rad(ray_angle)));
	data->step_ver_x = data->size_shape;
	data->step_ver_y = data->next_ver_inters_y - data->vertcl_inters_y;
	while (((int)(data->vertcl_inters_x / data->size_shape)) < data->width_map
		&& ((int)(data->vertcl_inters_y / data->size_shape)) < data->height_map
		&& data->vertcl_inters_x >= 0 && data->vertcl_inters_y >= 0
		&& data->map[(int)(data->vertcl_inters_y
			/ data->size_shape)][(int)(data->vertcl_inters_x
			/ data->size_shape)] != '1')
	{
		data->vertcl_inters_y += data->step_ver_y;
		data->vertcl_inters_x += data->step_ver_x;
	}
}

void	check_ray_draw_left(t_cub3d *data, float ray_angle)
{
	data->vertcl_inters_x = floor((data->px / data->size_shape))
		* data->size_shape;
	data->vertcl_inters_y = data->py - ((data->px - data->vertcl_inters_x)
			* tan(to_rad(ray_angle)));
	data->next_ver_inters_x = data->vertcl_inters_x - data->size_shape;
	data->next_ver_inters_y = data->vertcl_inters_y - ((data->vertcl_inters_x
				- data->next_ver_inters_x) * tan(to_rad(ray_angle)));
	data->step_ver_x = data->size_shape;
	data->step_ver_y = data->next_ver_inters_y - data->vertcl_inters_y;
	while (((int)((data->vertcl_inters_x - 1)
			/ data->size_shape)) < data->width_map
		&& ((int)(data->vertcl_inters_y / data->size_shape)) < data->height_map
		&& data->vertcl_inters_x >= 0 && data->vertcl_inters_y >= 0
		&& data->map[(int)(data->vertcl_inters_y
			/ data->size_shape)][(int)((data->vertcl_inters_x - 1)
			/ data->size_shape)] != '1')
	{
		data->vertcl_inters_y += data->step_ver_y;
		data->vertcl_inters_x -= data->step_ver_x;
	}
}*/

// double	get_wall_dist(t_game *game)
// {
// 	double	x_step;
// 	double	y_step;
// 	double	next_x;
// 	double	next_y;
// 	int		hit_side;

// 	if (game->ray.angle > 0 && game->ray.angle < M_PI)
// 	{
// 		y_step = TILE_SIZE;
// 		next_y = floor(game->player.y / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
// 		hit_side = 0;
// 	}
// 	else
// 	{
// 		y_step = -TILE_SIZE;
// 		next_y = floor(game->player.y / TILE_SIZE) * TILE_SIZE - 1;
// 		hit_side = 1;
// 	}
// 	x_step = TILE_SIZE / tan(game->ray.angle);
// 	if ((game->ray.angle > M_PI_2 && game->ray.angle < 3 * M_PI_2)
// 		&& x_step > 0)
// 		x_step = -x_step;
// 	else if ((game->ray.angle <= M_PI_2 || game->ray.angle >= 3 * M_PI_2)
// 		&& x_step < 0)
// 		x_step = -x_step;
// 	next_x = game->player.x + (game->player.y - next_y)
// 		/ tan(game->ray.angle);
// 	while (is_wall(next_x, next_y, game))
// 	{
// 		next_x += x_step;
// 		next_y += y_step;
// 		if (next_x < 0 || next_x >= game->map_width * TILE_SIZE
// 			|| next_y < 0 || next_y >= game->map_height * TILE_SIZE)
// 			return (INFINITY);
// 		if (hit_side == 0 && (game->ray.angle > 0 && game->ray.angle < M_PI))
// 		{
// 			if (check_inter(game->ray.angle, &next_y, &y_step, 1))
// 			{
// 				hit_side = 1;
// 				x_step = TILE_SIZE / tan(game->ray.angle);
// 				if (game->ray.angle > M_PI_2 && game->ray.angle < 3 * M_PI_2)
// 					x_step = -x_step;
// 				next_x = game->player.x
// 					+ (game->player.y - next_y) / tan(game->ray.angle);
// 			}
// 		}
// 		else if (hit_side == 0
// 			&& (game->ray.angle < 0 || game->ray.angle > M_PI))
// 		{
// 			if (check_inter(game->ray.angle, &next_y, &y_step, 0))
// 			{
// 				hit_side = 1;
// 				x_step = TILE_SIZE / tan(game->ray.angle);
// 				if (game->ray.angle <= M_PI_2 || game->ray.angle >= 3 * M_PI_2)
// 					x_step = -x_step;
// 				next_x = game->player.x + (game->player.y - next_y)
// 					/ tan(game->ray.angle);
// 			}
// 		}
// 		if (hit_side == 1
// 			&& (game->ray.angle < M_PI_2 || game->ray.angle > 3 * M_PI_2))
// 		{
// 			if (check_inter(game->ray.angle, &next_x, &x_step, 0))
// 			{
// 				hit_side = 0;
// 				y_step = TILE_SIZE * tan(game->ray.angle);
// 				if (game->ray.angle > M_PI && game->ray.angle < 2 * M_PI)
// 					y_step = -y_step;
// 				next_y = game->player.y + (next_x - game->player.x)
// 					* tan(game->ray.angle);
// 			}
// 		}
// 		else if (hit_side == 1
// 			&& (game->ray.angle > M_PI_2 && game->ray.angle < 3 * M_PI_2))
// 		{
// 			if (check_inter(game->ray.angle, &next_x, &x_step, 1))
// 			{
// 				hit_side = 0;
// 				y_step = TILE_SIZE * tan(game->ray.angle);
// 				if (game->ray.angle < M_PI && game->ray.angle > 0)
// 					y_step = -y_step;
// 				next_y = game->player.y + (next_x - game->player.x)
// 					* tan(game->ray.angle);
// 			}
// 		}
// 	}
// 	return (sqrt(pow(game->player.x - next_x, 2)
// 			+ pow(game->player.y - next_y, 2)));
// }