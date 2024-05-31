/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by lmicheli          #+#    #+#             */
/*   Updated: 2024/05/31 15:05:01 by mruggier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>

void	pixels_init(t_game *game)
{
	int	i;

	if (game->pixels)
		ft_free_matrix((char **)game->pixels);
	game->pixels = ft_calloc(SCREEN_HEIGHT + 1, sizeof(int *));
	if (!game->pixels)
		return (err_exit("Failed to allocate pixels", game));
	i = 0;
	while (i < SCREEN_HEIGHT)
	{
		game->pixels[i] = ft_calloc(SCREEN_WIDTH + 1, sizeof(int));
		if (!game->pixels[i])
			return (ft_free_matrix((char **)game->pixels), exit(1));
		i++;
	}
}

static int	get_index(t_game *game)
{
	if (BONUS && game->bonus.wall_hit == 'D')
	{
		game->bonus.wall_hit = '1';
		if (game->ray.side == 0)
		{
			if (game->ray.dir.x < 0)
				return (6);
			else
				return (6);
		}
		else
		{
			if (game->ray.dir.y > 0)
				return (6);
			else
				return (6);
		}
	}
	else
	{
		if (BONUS)
			game->bonus.wall_hit = '1';
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
		color = game->txts.imgs[4].data[(int)fmod((int)(fmod(curs.x, BACKGROUND_SIZE)
				+ (int)fmod(curs.y, BACKGROUND_SIZE) * BACKGROUND_SIZE), BACKGROUND_SIZE )];
		game->pixels[i][x] = color;
		i++;
	}
}

void pixel_floor(t_game *game, int x, int y)
{
	int		i;
	t_pos	curs;
	double	step;
	int		color;

	curs = (t_pos){0, 0, 0};
	i = y;
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
		color = game->txts.imgs[5].data[(int)fmod((int)(fmod(curs.x, BACKGROUND_SIZE)
				+ (int)fmod(curs.y, BACKGROUND_SIZE) * BACKGROUND_SIZE), BACKGROUND_SIZE )];
		game->pixels[i][x] = color;
		i++;
	}
}

void	pixels_update(t_game *game, int x)
{
	int			y;
	int			color;
	int			i;

	i = get_index(game);
	game->txts.x = (int)(game->ray.wall_x * (int)TILE_SIZE);
	if ((game->ray.side == 0 && game->ray.dir.x < 0)
		|| (game->ray.side == 1 && game->ray.dir.y > 0))
		game->txts.x = (int)TILE_SIZE - game->txts.x - 1;
	game->txts.step = 1.0 * (int)TILE_SIZE / game->ray.line_len;
	game->txts.pos = (game->ray.drw_start - SCREEN_HEIGHT
			/ 2 + game->ray.line_len / 2) * game->txts.step;
	y = game->ray.drw_start;
	pixel_sky(game, x, y);
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
