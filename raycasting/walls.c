/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:49:46 by lmicheli          #+#    #+#             */
/*   Updated: 2024/05/17 18:50:41 by lmicheli         ###   ########.fr       */
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
			reverse_bit(arr[(int)y_o * texture.width + (int)x_o]));
		y_o += factor;
		t_pix++;
	}
}

void	draw_upndown(t_game *game, double t_pix, double b_pix)
{
	double		x_o;
	double		y_o;
	t_img		texture;
	u_int32_t	*arr;
	double		factor;

	texture = game->txts.imgs[4];
	arr = (u_int32_t *)texture.data;
	factor = (double)texture.height / (SCREEN_HEIGHT / 2);
	x_o = get_xo(game, texture);
	y_o = 0;
	while (y_o < SCREEN_HEIGHT / 2)
	{
		better_pixel_put(game, game->ray.i_ray, y_o,
			reverse_bit(arr[(int)y_o * texture.width + (int)x_o]));
		y_o++;
	}
}

void	render_wall(t_game *game, int i_ray)
{
	double	wall_h;
	double	b_pix;
	double	t_pix;

	game->ray.dist *= cos(nor_angle(game->player.angle - game->ray.angle));
	wall_h = (TILE_SIZE / game->ray.dist) * (SCREEN_WIDTH / 2)
		/ tan(game->fov_rd / 2);
	b_pix = (SCREEN_HEIGHT / 2) + (wall_h / 2);
	t_pix = (SCREEN_HEIGHT / 2) - (wall_h / 2);
	if (b_pix > SCREEN_HEIGHT)
		b_pix = SCREEN_HEIGHT;
	if (t_pix < 0)
		t_pix = 0;
	draw_wall(game, wall_h, t_pix, b_pix);
	draw_upndown(game, t_pix, b_pix);
}
