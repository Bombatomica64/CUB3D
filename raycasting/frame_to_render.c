/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_to_render.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 23:14:57 by marco             #+#    #+#             */
/*   Updated: 2024/06/03 23:30:28 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>

void	player_set(t_game *game, t_Myimg *img)
{
	t_pos	pos;
	t_pos	circle;

	pos.y = game->bonus.player.y * MINIMAP_SCALE;
	pos.x = game->bonus.player.x * MINIMAP_SCALE;
	circle.y = -P_RADIUS;
	while (circle.y < P_RADIUS * 2)
	{
		circle.x = -P_RADIUS;
		while (circle.x < P_RADIUS * 2)
		{
			draw_circle(game, img, pos, circle);
			circle.x++;
		}
		circle.y++;
	}
}

void	set_pixel(t_Myimg *image, int x, int y, int color)
{
	int	pixel;

	pixel = y * (image->size_line / 4) + x;
	image->data[pixel] = color;
}

void	frame_set(t_game *game, t_Myimg *image, int x, int y)
{
	if (BONUS && x < MINIMAP_SCALE * game->map_width && y < MINIMAP_SCALE
		* game->map_height)
		minimap(game, image, x, y);
	else if (game->pixels[y][x] > 0)
		set_pixel(image, x, y, game->pixels[y][x]);
}

void	draw_circle(t_game *game, t_Myimg *img, t_pos pos, t_pos circle)
{
	t_curs	map;

	map.i = (int)floor(pos.y + circle.y) / MINIMAP_SCALE;
	map.j = (int)floor(pos.x + circle.x) / MINIMAP_SCALE;
	if (map.i >= 0 && map.i < game->map_height && map.j >= 0
		&& map.j < game->map_width)
	{
		if ((circle.x - P_RADIUS) * (circle.x - P_RADIUS)
			+ (circle.y - P_RADIUS) * (circle.y - P_RADIUS)
			<= P_RADIUS * P_RADIUS)
		{
			if (!(ft_isinset(game->bonus.minimap[map.i][map.j], "1D")))
				set_pixel(img, pos.x + circle.x, pos.y + circle.y, 0xAA3355);
		}
	}
}
