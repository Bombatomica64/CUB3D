/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by lmicheli          #+#    #+#             */
/*   Updated: 2024/05/29 12:26:03 by lmicheli         ###   ########.fr       */
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
	if (game->pixels[y][x] > 0)
		set_pixel(image, x, y, game->pixels[y][x]);
	else if (y < SCREEN_HEIGHT / 2)
		set_pixel(image, x, y, 0x87CEEB);
	else if (y < SCREEN_HEIGHT -1)
		set_pixel(image, x, y, 0x2F4F4F);
}

static t_Myimg	empty_myimg(t_game *game, int width, int height)
{
	t_Myimg	image;

	image.img.image = mlx_new_image(game->mlx, width, height);
	image.data = (int *)mlx_get_data_addr(image.img.image, &image.img.bpp,
			&image.size_line, &image.endian);
	return (image);
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
	mlx_put_image_to_window(game->mlx, game->win, image.img.image, 0, 0);
	mlx_destroy_image(game->mlx, image.img.image);
}

int	render_images(t_game *game)
{
	static int	frame = 0;

	pixels_init(game);
	cast_rays(game);
	render_frame(game);
	frame++;
	printf("frame = %d\n", frame);
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
