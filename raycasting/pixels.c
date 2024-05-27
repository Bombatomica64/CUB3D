/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 11:30:33 by gduranti          #+#    #+#             */
/*   Updated: 2024/05/27 18:34:57 by lmicheli         ###   ########.fr       */
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
		return (exit(1));
	i = 0;
	while (i < SCREEN_HEIGHT)
	{
		game->pixels[i] = ft_calloc(SCREEN_WIDTH + 1, sizeof(int));
		if (!game->pixels[i])
			return (ft_free_matrix((char **)game->pixels), exit(1));
		i++;
	}
}

static t_Myimg	get_index(t_game *game)
{
	if (game->ray.side == 0)
	{
		if (game->ray.dir.x < 0)
			return (game->txts.imgs[3]);
		else
			return (game->txts.imgs[2]);
	}
	else
	{
		if (game->ray.dir.y > 0)
			return (game->txts.imgs[1]);
		else
			return (game->txts.imgs[0]);
	}
}

void	pixels_update(t_game *game, int x)
{
	int			y;
	int			color;
	t_Myimg		texture;

	texture = get_index(game);
	game->txts.x = (int)(game->ray.wall_x * game->txts.size);
	if ((game->ray.side == 0 && game->ray.dir.x < 0) || (game->ray.side == 1 && game->ray.dir.y > 0))
		game->txts.x = game->txts.size - game->txts.x - 1;
	game->txts.step = 1.0 * game->txts.size / game->ray.line_len;
	game->txts.pos = (game->ray.drw_start - SCREEN_HEIGHT
			/ 2 + game->ray.line_len / 2) * game->txts.step;
	y = game->ray.drw_start;
	while (y < game->ray.drw_end)
	{
		game->txts.y = (int)game->txts.pos & (game->txts.size - 1);
		game->txts.pos += game->txts.step;
		color = texture.data[TILE_SIZE * game->txts.y + game->txts.x];
		if (!color)
			color += 1;
		game->pixels[y][x] = color;
		y++;
	}
}

		// if (game->txts.index == NORTH || game->txts.index == EAST) // for shadows
		// 	color = (color >> 1) & 8355711;