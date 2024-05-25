/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:39:43 by lmicheli          #+#    #+#             */
/*   Updated: 2024/05/25 23:11:00 by marco            ###   ########.fr       */
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

// Q2 Q1
// Q3 Q4

void	cast_rays(t_game *game)
{		
	double FOV_rad = FOV * M_PI / 180; // conversione in radianti
	printf(BLUE"FOV_rad:%f\n"END, FOV_rad);
	double FOV2 = FOV_rad / 2;
	double alpha = FOV2; //angolo iniziale
	//printf(BLUE"alpha:%f\n"END, alpha);

	//double alpha_tot = game->ray.angle + FOV2; non funge game->ray.angle
	double alpha_tot = M_PI_2 + FOV2; //quindi lo hardcodo a 90 (N) + 45
	printf(BLUE"alpha_tot:%f\n"END, alpha_tot);
	double alpha_current = alpha_tot;
	double rotaz = alpha / (SCREEN_WIDTH / 2);
	int signx;
	int signy;
	
	//--calcolo piccolo di delta x--
	double Smallstepx; //distanza da p.y a y riga successiva (n00)
	double Smallstepy; //distanza da p.x a interzezione con riga y (n00)
	double dSmallstep;
	double Wx; //intersezione da controllare con IsWall
	double Wy; //intersezione con riga y (n00) IsWall
	double d; //distanza finale
	int signalpha = -1;
	
	int displayx = 0;
	while (alpha_current > alpha_tot - FOV_rad) //angolo del player - FOV/2 ???
	{
		//NORMALIZZA Angolo
		
		//segno per quadrante
		if (alpha_current >= 0 && alpha_current < M_PI_2)
		{
			signx = 1;
			signy = -1;
		}
		else if (alpha_current >= M_PI_2 && alpha_current < M_PI)
		{
			signx = -1;
			signy = -1;
		}
		else if (alpha_current >= M_PI && alpha_current < 3 * M_PI_2)
		{
			signx = -1;
			signy = 1;
		}
		else
		{
			signx = 1;
			signy = 1;
		}
		
		//printf(GREEN"signx:%d\nsigny:%d\n"END, signx, signy);
		printf(BLUE"alpha:%f\n"END, alpha);
		if ((signx == -1 && signy == -1) || (signx == 1 && signy == 1))
		{
			Smallstepy = fmod(game->player.y, TILE_SIZE); //y % TILE_SIZE in float
			Smallstepx = Smallstepy * tan(alpha);
			dSmallstep = Smallstepx / sin(alpha);
		}
		else
		{
			Smallstepy = fmod(game->player.y, TILE_SIZE); //x % TILE_SIZE in float
			Smallstepx = Smallstepy * tan(alpha);
			dSmallstep = Smallstepx / sin(alpha);
		}
		printf(PURPLE"sstepx:%f\nsstepy:%f\n"END, Smallstepx, Smallstepy);
		
		//printf(RED"dSmallstep:%f\n"END, dSmallstep);
		Wx = game->player.x + Smallstepx * signx;
		Wy = game->player.y + Smallstepy * signy; //per controllare se muro
		//printf(GREEN"Wx:%f\nWy:%f\n"END, Wx, Wy);

		d = dSmallstep;
		if ((signx == 1 && signy == -1) || (signx == -1 && signy == -1))
		{	
			if (is_wall(Wx, Wy - TILE_SIZE, game) == 1)
			{
				alpha_current = alpha_current - rotaz;
				alpha = alpha + rotaz * (signalpha);
				if (alpha <= 0)
				{
					signalpha = 1;
				}
				printf(GREEN"wx:%f\nwy:%f\n"END, Wx, Wy);
				printf(RED"è muro e smalld:%f\n"END, d);
				//exit(0);
				continue;
			}
		}
		else
		{
			if (is_wall(Wx, Wy + TILE_SIZE, game) == 1)
			{
				printf(BLUE"alpha_current:%f\n"END, alpha_current);
				alpha_current = alpha_current - rotaz;
				alpha = alpha + rotaz * (signalpha);
				if (alpha <= 0)
				{
					signalpha = 1;
				}
				printf(GREEN"wx:%f\nwy:%f\n"END, Wx, Wy);

				printf(RED"è muro e smalld:%f\n"END, d);
				//exit(0);
				continue;
			}
		}
		
		//--se non è muro-- step da ripetere x--
		double stepx;
		double stepy;
		double dstep;

		if ((signx == -1 && signy == -1) || (signx == 1 && signy == 1))
		{
			stepy = TILE_SIZE;
			stepx = stepy * tan(alpha);
			dstep = stepx / sin(alpha); 
		}
		else
		{
			stepy = TILE_SIZE;
			stepx = stepy * tan(alpha);
			dstep = stepx / sin(alpha); 
		}
		
		printf(PURPLE"stepx:%f\nstepy:%f\n"END, stepx, stepy);
		//printf(RED"dstep:%f\n"END, dstep);

		if ((signx == 1 && signy == -1) || (signx == -1 && signy == -1))
		{
			while (is_wall(Wx, Wy - TILE_SIZE, game) == 0)
			{
				Wx = Wx + stepx * signx;
				Wy = Wy + stepy * signy;
				d = d + dstep;
				if (d > 1000) //errore non trova il muro
					break;
				//printf(GREEN"Wx:%f\nWy:%f\n"END, Wx, Wy);
			}
		}
		else
		{
			while (is_wall(Wx, Wy + TILE_SIZE, game) == 0)
			{
				Wx = Wx + stepx * signx;
				Wy = Wy + stepy * signy;
				d = d + dstep;
				if (d > 1000) //errore non trova il muro
					break;
				//printf(GREEN"Wx:%f\nWy:%f\n"END, Wx, Wy);
			}
		}

		
		if (d > 1000) //errore non trova il muro. stampa comunque righe nere, boh?
		{
			alpha_current = alpha_current - rotaz;
			alpha = alpha + rotaz * (signalpha);
			for (int y = 0; y <= SCREEN_HEIGHT; y++)
				mlx_pixel_put(game->mlx, game->win, displayx, y, 0xFF0000);
			displayx++;
			if (alpha <= 0)
			{
				signalpha = 1;
			}
			continue;
		}
		printf(GREEN"Wx:%f\nWy:%f\n"END, Wx, Wy);

		printf(RED"è muro e d:%f\n"END, d);
		
		

		//print wall
		int y = 0;
		while (y <= floor(d) / 2)
		{
			mlx_pixel_put(game->mlx, game->win, displayx, y, 0x00FFFF);
			mlx_pixel_put(game->mlx, game->win, displayx, SCREEN_HEIGHT - y, 0x00FFFF);
			y++;
		}
		while( y <= SCREEN_HEIGHT / 2)
		{
			mlx_pixel_put(game->mlx, game->win, displayx, y, 0xFFFF00);
			mlx_pixel_put(game->mlx, game->win, displayx, SCREEN_HEIGHT - y, 0xFFFF00);
			y++;
		}
		displayx++;


		//ciclo while
		alpha_current = alpha_current - rotaz;
		alpha = alpha + rotaz * (signalpha);
		if (alpha <= 0)
		{
			signalpha = 1;
		}
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