/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by lmicheli          #+#    #+#             */
/*   Updated: 2024/06/04 18:03:32 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>

void	key_input(t_game *data)
{
	mlx_hook(data->win, KeyPress, KeyPressMask, &on_key_press, data);
	mlx_hook(data->win, KeyRelease, KeyReleaseMask, &on_key_release, data);
	mlx_hook(data->win, DestroyNotify, StructureNotifyMask, &on_destroy, data);
	mlx_loop_hook(data->mlx, &render_images, data);
	mlx_loop(data->mlx);
}

void	basic_checks(int ac, char **av)
{
	if (MOVE_SPEED < 0 || MOVE_SPEED > 1)
	{
		err("Error\nInvalid move speed\n");
		exit(1);
	}
	if (ac != 2)
	{
		perror("Error\nWrong number of arguments\n");
		exit(1);
	}
	if (ft_strncmp(av[1] + ft_strlen(av[1]) - 4, ".cub", 4))
	{
		perror("Error\nWrong file extension\n");
		exit(1);
	}
}

int	main(int ac, char **av)
{
	t_game	*game;

	basic_checks(ac, av);
	game = init_game(av[1]);
	if (!game->mlx)
	{
		perror("Error\nFailed to init mlx\n");
		return (1);
	}
	printf("bonus = %d\n", BONUS);
	mlx_mouse_move(game->mlx, game->win, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	key_input(game);
	return (0);
}

	// mlx_mouse_hide(game->mlx, game->win);