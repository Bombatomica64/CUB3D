/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:13:53 by lmicheli          #+#    #+#             */
/*   Updated: 2024/05/13 17:58:31 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>

t_game	init_game(char *map_path)
{
	t_game	game;

	game.mlx = mlx_init();
	if (!game.mlx)
		return (game);
	game.win = mlx_new_window(game.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D");
	game.map = parse_map(map_path, &game);
	return (game);
}
