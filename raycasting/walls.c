/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:49:46 by lmicheli          #+#    #+#             */
/*   Updated: 2024/05/22 12:00:59 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>

double	get_xo(t_game *game, t_img texture)
{
	double		x_o;

	if (game->ray.flag == 1)
		x_o = (int)fmodf((game->ray.hor_x * \
		(texture.width / TILE_SIZE)), texture.width);
	else
		x_o = (int)fmodf((game->ray.ver_y * \
		(texture.width / TILE_SIZE)), texture.width);
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
	arr = (u_int32_t *)texture.data;
	factor = (double)texture.height / (wall_h);
	x_o = get_xo(game, texture);
	y_o = (t_pix - SCREEN_HEIGHT / 2 + wall_h / 2) * factor;
	if (y_o < 0)
		y_o = 0;
	while (t_pix < b_pix)
	{
		better_pixel_put(game, game->ray.i_ray, t_pix,
			reverse_bit(0x115221/* arr[(int)y_o * texture.width + (int)x_o] */));
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

	texture = game->txts.imgs[5];
	arr = (u_int32_t *)texture.data;
	factor = (double)texture.height / (SCREEN_HEIGHT - wall_h);
	x_o = get_xo(game, texture);
	y_o = (b_pix - SCREEN_HEIGHT / 2 + wall_h / 2) * factor;
	if (y_o < 0)
		y_o = 0;
	while (b_pix < SCREEN_HEIGHT)
	{
		better_pixel_put(game, game->ray.i_ray, b_pix,
			reverse_bit(0x0F0000/* arr[(int)y_o * texture.width + (int)x_o] */));
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

	texture = game->txts.imgs[4];
	arr = (u_int32_t *)texture.data;
	factor = (double)texture.height / (SCREEN_HEIGHT - wall_h);
	x_o = get_xo(game, texture);
	y_o = (t_pix - SCREEN_HEIGHT / 2 + wall_h / 2) * factor;
	if (y_o < 0)
		y_o = 0;
	while (t_pix >= 0)
	{
		better_pixel_put(game, game->ray.i_ray, t_pix,
			reverse_bit(0xF00F00/* arr[(int)y_o * texture.width + (int)x_o] */));
		y_o -= factor;
		t_pix--;
	}
}

void	render_wall(t_game *game)
{
	double	wall_h;
	double	b_pix;
	double	t_pix;

	game->ray.dist *= fast_cos(nor_angle(game->ray.angle - game->player.angle),
			game);
	wall_h = (TILE_SIZE / game->ray.dist) * game->player.dist_proj;
	// printf("wall_h: %f\n", wall_h);
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
