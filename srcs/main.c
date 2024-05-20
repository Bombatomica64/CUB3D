/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 12:03:28 by lmicheli          #+#    #+#             */
/*   Updated: 2024/05/20 12:44:36 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>

int	on_esc(int keysym)
{
	if (keysym == XK_Escape)
		exit(1);
	return (0);
}

int	on_destroy(t_game *data)
{
	(void)data;
	exit(1);
	return (0);
}

void	key_input(t_game *data)
{
	mlx_hook(data->win, KeyPress, KeyPressMask,
		&on_esc, NULL);
	// mlx_hook(data->data.win, ButtonPress, ButtonPressMask,
	// 	&on_mouseclick, &data->data);
	// mlx_hook(data->data.win, ButtonRelease, ButtonReleaseMask,
	// 	&on_mouserelease, &data->data);
	mlx_hook(data->win, DestroyNotify, StructureNotifyMask,
		&on_destroy, data);
	mlx_loop(data->mlx);
}

int	main(int ac, char **av)
{
	t_game	*game;

	if (ac != 2)
	{
		printf("Error\nWrong number of arguments\n");
		return (1);
	}
	game = init_game(av[1]);
	if (!game->mlx)
	{
		printf("Error\nFailed to init mlx\n");
		return (1);
	}
	printf("game.mlx[%p]\n", game->mlx);
	mlx_put_image_to_window(game->mlx, game->win, game->txts.imgs[0].image, 0, 0);
	exit(0);

	cast_rays(game);
	key_input(game);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	return (0);
}
