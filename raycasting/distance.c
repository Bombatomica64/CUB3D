/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:39:43 by lmicheli          #+#    #+#             */
/*   Updated: 2024/05/24 19:45:41 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>

double	get_wall_dist(t_game *game)
{
	t_pos		steps;

	steps.x = TILE_SIZE / tan(game->ray.angle);
	if (game->ray.angle > M_PI || (game->ray.angle > 0
			&& game->ray.angle < M_PI))
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

void	cast_rays(t_game *game)
{
	//double	increment;
	int y;

	game->ray.i_ray = 0;
	//increment = game->fov_rd / SCREEN_WIDTH;
	game->ray.angle = game->player.angle - (game->fov_rd / 2);
	while (game->ray.i_ray <= SCREEN_WIDTH)
	{
		y = (SCREEN_HEIGHT);
		while (y >= 0)
		{
			if (y > 500)
				mlx_pixel_put(game->mlx, game->win, game->ray.i_ray, y, 0xFF0000);
			else
				mlx_pixel_put(game->mlx, game->win, game->ray.i_ray, y, 0x00FF00);
			y--;
		
		}
		game->ray.i_ray++;


		{
			double FOV_rad = FOV * M_PI / 180; // conversione in radianti
			double FOV2 = FOV_rad / 2;
			double alpha = FOV2; //angolo iniziale
			double alpha_ray = game->ray.angle + FOV2;
			double rotaz = alpha / (SCREEN_WIDTH / 2);
			(void)alpha_ray;
			//while (alpha != 0) //solo prima metà, cioè a nord per POV/2
			//{
			//	
			//	alpha = alpha - rotaz;
			//}
			
			//--calcolo piccolo di delta x--
			double Smallstepx; //distanza da p.y a y riga successiva (n00)
			double Smallstepy; //distanza da p.x a interzezione con riga y (n00)
			double dSmallstep;
			double Wx; //intersezione da controllare con IsWall
			double Wy; //intersezione con riga y (n00) IsWall
			double d; //distanza finale

			Smallstepy = fmod(game->player.y, TILE_SIZE); //y % TILE_SIZE in float
			Smallstepx = Smallstepy / tan(alpha);
			printf(PURPLE"sstepx:%f\nsstepy:%f\n"END, Smallstepx, Smallstepy);
			dSmallstep = Smallstepy / sin(alpha);
			printf(RED"dSmallstep:%f\n"END, dSmallstep);
			Wx = game->player.x - Smallstepx;
			Wy = game->player.y - Smallstepy; //per controllare se muro
			printf(GREEN"Wx:%f\nWy:%f\n"END, Wx, Wy);

			d = dSmallstep;
			if (is_wall(Wx - TILE_SIZE, Wy - TILE_SIZE, game) == 1)
			{
				printf(RED"è muro e d:%f\n"END, d);
				exit(0);
			}
			
			//--se non è muro-- step da ripetere x--
			double stepx;
			double stepy;
			double dstep;

			stepy = TILE_SIZE;
			stepx = stepy * tan(alpha);
			dstep = stepy / cos(alpha);
			printf(PURPLE"stepx:%f\nstepy:%f\n"END, stepx, stepy);
			printf(RED"dstep:%f\n"END, dstep);

			while (is_wall(Wx - TILE_SIZE, Wy - TILE_SIZE, game) == 0)
			{
				Wx = Wx - stepx;
				Wy = Wy - stepy;
				d = d + dstep;
				printf(GREEN"Wx:%f\nWy:%f\n"END, Wx, Wy);
			}
			printf(RED"è muro e d:%f\n"END, d);
			
			

			

			
			








			
		}
		exit(0);
		//game->ray.flag = 0;
		//game->ray.angle = nor_angle(game->ray.angle);*/
		//game->ray.dist = get_wall_dist(game);
		//printf("ray %d: dist = %f\n", game->ray.i_ray, game->ray.dist);
		//render_wall(game);
		//game->ray.angle += increment;
		
	}
	return ;
}

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