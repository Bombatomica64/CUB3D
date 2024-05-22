/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:49:46 by lmicheli          #+#    #+#             */
/*   Updated: 2024/05/22 18:47:37 by mruggier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>

double	get_xo(t_game *game, t_img texture, char type)
{
	double		x_o;

	if (type == 'w')
	{
		if (game->ray.flag == 1)
			x_o = (int)fmodf((game->ray.hor_x * \
			(texture.width / TILE_SIZE)), texture.width);
		else
			x_o = (int)fmodf((game->ray.ver_y * \
			(texture.width / TILE_SIZE)), texture.width);
	}
	else
	{
		x_o = (int)fmodf((game->player.x
					* (texture.width / TILE_SIZE)), texture.width);
	}
	return (x_o);
}

void	draw_wall(t_game *game, double wall_h, double t_pix, double b_pix)
{
	double		x_o;
	double		y_o;
	t_img		texture;
	u_int32_t	*arr;
	double		factor;

	texture = get_texture(game);
	arr = (u_int32_t *)game->txts.addr[2];
	factor = (double)texture.height / (wall_h);
	x_o = get_xo(game, texture, 'w');
	y_o = (t_pix - SCREEN_HEIGHT / 2 + wall_h / 2) * factor;
	if (y_o < 0)
		y_o = 0;
	while (t_pix < b_pix)
	{
		better_pixel_put(game, game->ray.i_ray, t_pix,
			reverse_bit(/*0x115221*/arr[(int)y_o * texture.width + (int)x_o]));
		y_o += factor;
		t_pix++;
	}
}

void	draw_down(t_game *game, double wall_h, double b_pix)
{
	double		x_o;
	double		y_o;
	t_img		texture;
	u_int32_t	*arr;
	double		factor;
	int			i;

	texture = game->txts.imgs[5];
	arr = (u_int32_t *)game->txts.addr[5];
	factor = (double)texture.height / (SCREEN_HEIGHT - wall_h);
	x_o = get_xo(game, texture, 'f');
	y_o = b_pix * factor;
	if (y_o < 0)
		y_o = 0;
	while (b_pix < SCREEN_HEIGHT)
	{
		i = (int)y_o * texture.width + (int)x_o;
		if (i >= 0 && i < texture.width * texture.height)
			better_pixel_put(game, game->ray.i_ray, b_pix,
				reverse_bit(0x0F0000/*arr[i]*/));
		y_o += factor;
		b_pix++;
	}
}

void	draw_up(t_game *game, double wall_h, double t_pix)
{
	double		x_o;
	double		y_o;
	t_img		texture;
	u_int32_t	*arr;
	double		factor;
	int			i;

	texture = game->txts.imgs[4];
	arr = (u_int32_t *)game->txts.addr[4];
	factor = (double)texture.height / (SCREEN_HEIGHT - wall_h);
	x_o = get_xo(game, texture, 'c');
	y_o = t_pix * factor;
	if (y_o < 0)
		y_o = 0;
	while (t_pix >= 0)
	{
		i = (int)y_o * texture.width + (int)x_o;
		if (i >= 0 && i < texture.width * texture.height)
			better_pixel_put(game, game->ray.i_ray, t_pix,
				reverse_bit(0x897445/* arr[i] */));
		y_o -= factor;
		t_pix--;
	}
}

void	render_wall(t_game *game)
{
	double	wall_h;
	double	b_pix;
	double	t_pix;
	// double	correction;

	// correction = cos((game->fov_rd / 2) - game->ray.angle);
	// game->ray.dist *= cos(nor_angle(game->ray.angle - game->player.angle));
	wall_h = (SCREEN_HEIGHT / game->ray.dist);/* * game->player.dist_proj * correction;  */
	//printf("wall_h: %f\n", wall_h);
	b_pix = (SCREEN_HEIGHT / 2) + (wall_h / 2);
	t_pix = (SCREEN_HEIGHT / 2) - (wall_h / 2);
	if (b_pix > SCREEN_HEIGHT)
		b_pix = SCREEN_HEIGHT;
	if (t_pix < 0)
		t_pix = 0;
	draw_wall(game, wall_h, t_pix, b_pix);
	draw_up(game, wall_h, t_pix);
	draw_down(game, wall_h, b_pix);
}

// void	draw_up(t_game *game)
// {
// 	double		x_o;
// 	double		y_o;
// 	t_img		texture;
// 	u_int32_t	*arr;
// 	double		factor;

// 	texture = game->txts.imgs[4];
// 	arr = (u_int32_t *)texture.data;
// 	factor = (double)texture.height / (SCREEN_HEIGHT / 2);
// 	x_o = get_xo(game, texture);
// 	y_o = 0;
// 	while (y_o < SCREEN_HEIGHT / 2)
// 	{
// 		better_pixel_put(game, game->ray.i_ray, y_o,
// 			reverse_bit(arr[(int)y_o * texture.width + (int)x_o]));
// 		y_o++;
// 	}
// }

// void	draw_down(t_game *game, double b_pix)
// {
// 	double		x_o;
// 	double		y_o;
// 	t_img		texture;
// 	u_int32_t	*arr;
// 	double		factor;

// 	texture = game->txts.imgs[5];
// 	arr = (u_int32_t *)texture.data;
// 	factor = (double)texture.height / (SCREEN_HEIGHT / 2);
// 	x_o = get_xo(game, texture);
// 	y_o = 0;
// 	while (y_o < SCREEN_HEIGHT / 2)
// 	{
// 		better_pixel_put(game, game->ray.i_ray, b_pix + y_o,
// 			reverse_bit(arr[(int)y_o * texture.width + (int)x_o]));
// 		y_o++;
// 	}
// }
