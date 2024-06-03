/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by lmicheli          #+#    #+#             */
/*   Updated: 2024/06/03 18:05:49 by mruggier         ###   ########.fr       */
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
	if (BONUS && x < MINIMAP_SCALE * game->map_width && y < MINIMAP_SCALE
		* game->map_height)
		minimap(game, image, x, y);
	else if (game->pixels[y][x] > 0)
		set_pixel(image, x, y, game->pixels[y][x]);
}

t_Myimg	empty_myimg(t_game *game, int width, int height)
{
	t_Myimg	image;

	image.img.image = mlx_new_image(game->mlx, width, height);
	image.data = (int *)mlx_get_data_addr(image.img.image, &image.img.bpp,
			&image.size_line, &image.endian);
	return (image);
}

static void	draw_circle(t_game *game, t_Myimg *img, t_pos pos, t_pos circle)
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

static void	player_set(t_game *game, t_Myimg *img)
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
	time_t			current_time;

	mouse(game);
	pixels_init(game);
	cast_rays(game);
	render_frame(game);
	if (BONUS)
	{
		game->bonus.frame++;
		current_time = get_time();
		free(game->bonus.frames);
		game->bonus.frames = NULL;
		game->bonus.frames = ft_itoa(game->bonus.frame);
		mlx_string_put(game->mlx, game->win, SCREEN_WIDTH - 10, 10, 0x000000,
			game->bonus.frames);
		if (current_time >= game->bonus.frame_time + 1000)
		{
			game->bonus.frame = 0;
			game->bonus.frame_time = current_time;
		}
	}
	game_loop(game);
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
