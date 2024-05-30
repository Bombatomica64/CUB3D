/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 11:51:43 by lmicheli          #+#    #+#             */
/*   Updated: 2024/05/30 15:58:58 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>

void set_pixel_m(t_Myimg *image, int x, int y, int color)
{
	int pixel;
	int i;
	int j;

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

void	minimap(t_game *game)
{
	t_Myimg	img;
	t_curs	curs;

	curs = (t_curs){0, 0, 0, 0};
	img = empty_myimg(game, game->bonus.width, game->bonus.height);
	img.data = (int *)mlx_get_data_addr(img.img.image, &img.img.bpp,
			&img.size_line, &img.endian);
	while (curs.i < game->map_height)
	{
		curs.j = 0;
		while (curs.j < game->map_width)
		{
			if (game->bonus.minimap[curs.i][curs.j] == '1')
				set_pixel_m(&img, curs.j * MINIMAP_SCALE, curs.i * MINIMAP_SCALE, 0x000000);
			else if (game->bonus.minimap[curs.i][curs.j] == '0')
				set_pixel_m(&img, curs.j * MINIMAP_SCALE, curs.i * MINIMAP_SCALE, 0xFFFFFF);
			else if (ft_isinset(game->bonus.minimap[curs.i][curs.j], "PNSWE"))
				set_pixel_m(&img, curs.j * MINIMAP_SCALE, curs.i * MINIMAP_SCALE, 0xFF0000);
			curs.j++;
		}
		curs.i++;
	}
	mlx_put_image_to_window(game->mlx, game->win, img.img.image, 0, 0);
	mlx_destroy_image(game->mlx, img.img.image);
}
