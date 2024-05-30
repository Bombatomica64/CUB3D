/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 10:09:07 by lmicheli          #+#    #+#             */
/*   Updated: 2024/05/30 11:41:57 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>

void	mouse(t_game *game)
{
	int	x;
	int	y;

	mlx_mouse_get_pos(game->mlx, game->win, &x, &y);
	game->player.dir = rot(game->player.dir,
			(x - SCREEN_WIDTH / 2) * MROT_SPEED);
	game->player.plane = rot(game->player.plane,
			(x - SCREEN_WIDTH / 2) * MROT_SPEED);
	mlx_mouse_move(game->mlx, game->win, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
}
