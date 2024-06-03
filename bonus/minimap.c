/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 11:51:43 by lmicheli          #+#    #+#             */
/*   Updated: 2024/06/03 17:17:35 by mruggier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>

void	set_pixel_m(t_Myimg *image, int x, int y, int color)
{
	int	pixel;
	int	i;
	int	j;

	i = 0;
	while (i < MINIMAP_SCALE)
	{
		j = 0;
		while (j < MINIMAP_SCALE)
		{
			pixel = (y + i) * (image->size_line / 4) + (x + j);
			image->data[pixel] = color;
			j++;
		}
		i++;
	}
}

void	minimap(t_game *game, t_Myimg *img, int x, int y)
{
	if (game->bonus.minimap[y / MINIMAP_SCALE][x / MINIMAP_SCALE] == '1')
		set_pixel_m(img, x, y, 0x503C2D);
	else if (game->bonus.minimap[y / MINIMAP_SCALE][x / MINIMAP_SCALE] == '0')
		set_pixel_m(img, x, y, 0x333333);
	else if (game->bonus.minimap[y / MINIMAP_SCALE][x / MINIMAP_SCALE] == 'D')
		set_pixel_m(img, x, y, 0x2560CC);
	else if (game->bonus.minimap[y / MINIMAP_SCALE][x / MINIMAP_SCALE] == 'L')
		set_pixel_m(img, x, y, 0x00BB00);
	else if (game->bonus.minimap[y / MINIMAP_SCALE][x / MINIMAP_SCALE] == 'X')
		set_pixel_m(img, x, y, 0x544564);
	else
		set_pixel_m(img, x, y, 0x503C2D);
}

void	move_player(t_game *game)
{
	/*game->bonus.minimap[(int)game->bonus.player.y]
	[(int)game->bonus.player.x] = '0';
	game->bonus.minimap[(int)game->player.pos.y][(int)game->player.pos.x] = 'P';*/
	
	game->bonus.player.x = game->player.pos.x - 0.3;
	game->bonus.player.y = game->player.pos.y - 0.3;
}
