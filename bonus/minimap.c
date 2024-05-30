/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 11:51:43 by lmicheli          #+#    #+#             */
/*   Updated: 2024/05/30 12:55:24 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>

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
				set_pixel(&img, curs.j, curs.i, 0x000000);
			else if (game->bonus.minimap[curs.i][curs.j] == '0')
				set_pixel(&img, curs.j, curs.i, 0xFFFFFF);
			else if (ft_isinset(game->bonus.minimap[curs.i][curs.j], "PNSWE"))
				set_pixel(&img, curs.j, curs.i, 0xFF0000);
			curs.j++;
		}
		curs.i++;
	}
	fprintf(stderr, "minimap\n");
	mlx_put_image_to_window(game->mlx, game->win, img.img.image, 0, 0);
	mlx_destroy_image(game->mlx, img.img.image);
}
