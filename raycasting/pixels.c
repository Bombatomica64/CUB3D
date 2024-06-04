/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by lmicheli          #+#    #+#             */
/*   Updated: 2024/06/03 23:11:03 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>

int	get_index_bonus(t_game *game)
{
	if (BONUS && game->bonus.doors.wall_hit == 'D')
		return (6);
	else if (BONUS && game->bonus.doors.wall_hit == '1'
		&& game->bonus.doors.door_open == 1)
	{
		if ((game->bonus.doors.wallx == game->bonus.doors.doorx + 1
				&& game->bonus.doors.wally == game->bonus.doors.doory)
			|| (game->bonus.doors.wallx == game->bonus.doors.doorx - 1
				&& game->bonus.doors.wally == game->bonus.doors.doory)
			|| (game->bonus.doors.wallx == game->bonus.doors.doorx
				&& game->bonus.doors.wally == game->bonus.doors.doory + 1)
			|| (game->bonus.doors.wallx == game->bonus.doors.doorx
				&& game->bonus.doors.wally == game->bonus.doors.doory - 1))
			return (6);
	}
	if (BONUS && game->bonus.doors.insidedoor == true)
	{
		if (((int)game->ray.map.x == (int)game->player.pos.x
				&& abs((int)game->ray.map.y - (int)game->player.pos.y) == 1)
			|| ((int)game->ray.map.y == (int)game->player.pos.y
				&& abs((int)game->ray.map.x - (int)game->player.pos.x) == 1))
			return (6);
	}
	return (0);
}

static int	get_index(t_game *game)
{
	int	index;

	if (BONUS)
	{
		index = get_index_bonus(game);
		if (index != 0)
			return (index);
	}
	if (game->ray.side == 0)
	{
		if (game->ray.dir.x < 0)
			return (3);
		else
			return (2);
	}
	else
	{
		if (game->ray.dir.y > 0)
			return (1);
		else
			return (0);
	}
	return (0);
}

void	pixel_sky(t_game *game, int x, int y_end)
{
	int		i;
	t_pos	curs;
	double	step;
	int		color;

	curs = (t_pos){0, 0, 0};
	i = 0;
	step = 1.0 * BACKGROUND_SIZE / game->ray.line_len;
	while (i < y_end)
	{
		color = 0;
		curs.x = (x * BACKGROUND_SIZE / SCREEN_WIDTH);
		curs.y = (i * step);
		if (curs.x < 0)
			curs.x += BACKGROUND_SIZE;
		if (curs.y < 0)
			curs.y += BACKGROUND_SIZE;
		color = game->txts.imgs[4].data[(int)fmod((int)(fmod(curs.x,
						BACKGROUND_SIZE) + (int)fmod(curs.y, BACKGROUND_SIZE)
					* BACKGROUND_SIZE), BACKGROUND_SIZE)];
		game->pixels[i][x] = color;
		i++;
	}
}

void	pixel_floor(t_game *game, int x, int y)
{
	int		i;
	t_pos	curs;
	double	step;
	int		color;

	curs = (t_pos){0, 0, 0};
	i = y;
	pixel_sky(game, x, game->ray.drw_start);
	step = 1.0 * BACKGROUND_SIZE / game->ray.line_len;
	while (i < SCREEN_HEIGHT)
	{
		color = 0;
		curs.x = (x * BACKGROUND_SIZE / SCREEN_WIDTH);
		curs.y = (i * step);
		if (curs.x < 0)
			curs.x += BACKGROUND_SIZE;
		if (curs.y < 0)
			curs.y += BACKGROUND_SIZE;
		color = game->txts.imgs[5].data[(int)fmod((int)(fmod(curs.x,
						BACKGROUND_SIZE) + (int)fmod(curs.y, BACKGROUND_SIZE)
					* BACKGROUND_SIZE), BACKGROUND_SIZE)];
		game->pixels[i][x] = color;
		i++;
	}
}

void	pixels_update(t_game *game, int x)
{
	int	y;
	int	color;
	int	i;

	i = get_index(game);
	game->txts.x = (int)(game->ray.wall_x * (int)TILE_SIZE);
	if ((game->ray.side == 0 && game->ray.dir.x < 0) || (game->ray.side == 1
			&& game->ray.dir.y > 0))
		game->txts.x = (int)TILE_SIZE - game->txts.x - 1;
	game->txts.step = 1.0 * (int)TILE_SIZE / game->ray.line_len;
	game->txts.pos = (game->ray.drw_start - SCREEN_HEIGHT / 2
			+ game->ray.line_len / 2) * game->txts.step;
	y = game->ray.drw_start;
	while (y < game->ray.drw_end + 1 && y < SCREEN_HEIGHT)
	{
		game->txts.y = (int)game->txts.pos & ((int)TILE_SIZE - 1);
		game->txts.pos += game->txts.step;
		color = game->txts.imgs[i].data[(int)TILE_SIZE * game->txts.y
			+ game->txts.x];
		if (!color)
			color += 1;
		game->pixels[y][x] = color;
		y++;
	}
	pixel_floor(game, x, y);
}
// if (game->txts.index == NORTH || game->txts.index == EAST) // for shadows
// 	color = (color >> 1) & 8355711;
