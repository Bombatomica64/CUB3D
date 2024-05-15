/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 12:03:28 by lmicheli          #+#    #+#             */
/*   Updated: 2024/05/15 16:39:52 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
	{
		printf("Error\nWrong number of arguments\n");
		return (1);
	}
	game = init_game(av[1]);
	if (!game.mlx)
	{
		printf("Error\nFailed to init mlx\n");
		return (1);
	}
	// mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	// mlx_hook(game.win, 3, 1L << 1, key_release, &game);
	// mlx_hook(game.win, 17, 1L << 17, close_game, &game);
	// mlx_loop_hook(game.mlx, update, &game);
	// mlx_loop(game.mlx);
	return (0);
}