/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by lmicheli          #+#    #+#             */
/*   Updated: 2024/05/28 11:08:58 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>

static void	frame_set(t_game *game, t_myImg *image, int x, int y)
{
	if (game->pixels[y][x] > 0)
		set_pixel(image, x, y, game->pixels[y][x]);
	else if (y < SCREEN_HEIGHT / 2)
		set_pixel(image, x, y, game->textures.col_ceiling.value);
	else if (y < SCREEN_HEIGHT -1)
		set_pixel(image, x, y, game->textures.col_floor.value);
}

static void	render_frame(t_game *game)
{
	t_myImg	image;
	int		x;
	int		y;

	image.img = NULL;
	image = empty_myImg(game, game->win_w, SCREEN_HEIGHT);
	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < game->win_w)
		{
			frame_set(game, &image, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(game->mlx, game->window, image.img, 0, 0);
	mlx_destroy_image(game->mlx, image.img);
}

void	render_images(t_game *game)
{
	pixels_init(game);
	raycasting(game);
	render_frame(game);
	// if (BONUS)
	// 	render_minimap(game);
}

int	render(t_game *game)
{
	game->player.has_moved += ft_movement(game);
	if (game->player.has_moved == 0)
		return (0);
	render_images(game);
	return (0);
}
