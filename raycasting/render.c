/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by lmicheli          #+#    #+#             */
/*   Updated: 2024/06/02 16:03:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>

void	set_pixel(t_Myimg *image, int x, int y, int color)
{
	int	pixel;

	pixel = y * (image->size_line / 4) + x;
	image->data[pixel] = color;
}

static void	frame_set(t_game *game, t_Myimg *image, int x, int y)
{
	if (BONUS && x < MINIMAP_SCALE * game->map_width
		&& y < MINIMAP_SCALE * game->map_height)
		minimap(game, image, x, y);
	else if (game->pixels[y][x] > 0)
		set_pixel(image, x, y, game->pixels[y][x]);
	else if (y < SCREEN_HEIGHT / 2)
		set_pixel(image, x, y, 0x87CEEB);
	else if (y < SCREEN_HEIGHT -1)
		set_pixel(image, x, y, 0x2F4F4F);
}

t_Myimg	empty_myimg(t_game *game, int width, int height)
{
	t_Myimg	image;

	image.img.image = mlx_new_image(game->mlx, width, height);
	image.data = (int *)mlx_get_data_addr(image.img.image, &image.img.bpp,
			&image.size_line, &image.endian);
	return (image);
}

static void player_set(t_game *game, t_Myimg *img)
{
	double x;
	double y;
	double i;
	double j;

	y = game->bonus.player.y * MINIMAP_SCALE;
	x = game->bonus.player.x * MINIMAP_SCALE;
	i = -P_RADIUS;
	while (i < P_RADIUS * 2)
	{
		j = -P_RADIUS;
		while (j < P_RADIUS * 2)
		{
			int mapY = (int)floor(y + i) / MINIMAP_SCALE;
			int mapX = (int)floor(x + j) / MINIMAP_SCALE;
			// Check if the pixel is inside the minimap
			if (mapY >= 0 && mapY < game->map_height && mapX >= 0 && mapX < game->map_width)
			{
				// Check if the pixel is inside the circle
				if ((j - P_RADIUS) * (j - P_RADIUS) + (i - P_RADIUS) * (i - P_RADIUS) <= P_RADIUS * P_RADIUS)
				{
					// Check if the pixel is not inside a wall
					if (!(game->bonus.minimap[mapY][mapX] == '1'))
					{
						set_pixel(img, x + j, y + i, 0xAA3355);
					}
				}
			}
			j++;
		}
		i++;
	}
}

static void	render_frame(t_game *game)
{
	t_Myimg	image;
	int		x;
	int		y;

	image = empty_myimg(game, SCREEN_WIDTH, SCREEN_HEIGHT);
	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			frame_set(game, &image, x, y);
			x++;
		}
		y++;
	}
	if (BONUS)
		player_set(game, &image);
	mlx_put_image_to_window(game->mlx, game->win, image.img.image, 0, 0);
	mlx_destroy_image(game->mlx, image.img.image);
}

int	render_images(t_game *game)
{
	static int	frame = 0;

	mouse(game);
	pixels_init(game);
	cast_rays(game);
	render_frame(game);
	frame++;
	//printf("frame = %d\n", frame);
	game_loop(game);
	// if (BONUS)
	// 	minimap(game);
	return (0);
}

	// if (BONUS)
	// 	render_minimap(game);
// int	render(t_game *game)
// {
// 	game->player.has_moved += ft_movement(game);
// 	if (game->player.has_moved == 0)
// 		return (0);
// 	render_images(game);
// 	return (0);
// }
