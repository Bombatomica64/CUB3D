/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by lmicheli          #+#    #+#             */
/*   Updated: 2024/06/03 23:21:38 by marco            ###   ########.fr       */
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

t_Myimg	empty_myimg(t_game *game, int width, int height)
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
