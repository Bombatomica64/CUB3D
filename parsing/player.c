/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:05:29 by lmicheli          #+#    #+#             */
/*   Updated: 2024/05/21 12:30:27 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>

double	get_angle(int x, int y, t_game *game)
{
	double	angle;

	if (game->map[x][y] == 'N')
		angle = 3 * M_PI / 2;
	else if (game->map[x][y] == 'S')
		angle = M_PI / 2;
	else if (game->map[x][y] == 'W')
		angle = M_PI;
	else if (game->map[x][y] == 'E')
		angle = 0;
	else
	{
		fprintf(stderr, "Error\nInvalid player position\n");
		exit(1);
	}
	return (angle);
}

void	init_player(t_game *game, int x, int y)
{
	game->player.x = x;
	game->player.y = y;
	printf("Player position: %d, %d\n", game->player.x, game->player.y);
	game->player.angle = get_angle(x, y, game);
}
