/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:39:43 by lmicheli          #+#    #+#             */
/*   Updated: 2024/05/21 15:31:31 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>

void	cast_rays(t_game *game)
{
	double		h_inter;
	double		v_inter;

	game->ray.i_ray = 0;
	game->ray.angle = game->player.angle - (game->fov_rd / 2);
	while (game->ray.i_ray < SCREEN_WIDTH)
	{
		game->ray.flag = 0;
		game->ray.angle = nor_angle(game->ray.angle);
		h_inter = horizontal_inter(game);
		v_inter = vertical_inter(game);
		if (v_inter <= h_inter)
			game->ray.dist = v_inter;
		else
		{
			game->ray.dist = h_inter;
			game->ray.flag = 1;
		}
		// game->ray.dist *= cos(game->ray.angle - game->player.angle);
		render_wall(game);
		game->ray.angle += game->fov_rd / SCREEN_WIDTH;
		game->ray.i_ray++;
	}
	return ;
}
