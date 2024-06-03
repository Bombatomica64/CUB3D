/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:31:30 by lmicheli          #+#    #+#             */
/*   Updated: 2024/06/03 17:33:33 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>

void	door_opening(t_game *game)
{
	int	x;
	int	y;

	x = (int)(game->player.pos.x + game->player.dir.x);
	y = (int)(game->player.pos.y + game->player.dir.y);
	if (game->map[y][x] == 'D')
	{
		game->map[y][x] = 'L';
		game->bonus.minimap[y][x] = 'L';
	}
	else if (game->map[y][x] == 'L')
	{
		game->map[y][x] = 'D';
		game->bonus.minimap[y][x] = 'D';
	}
}
