/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:39:43 by lmicheli          #+#    #+#             */
/*   Updated: 2024/05/20 11:13:02 by lmicheli         ###   ########.fr       */
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
		if (h_inter < v_inter)
			game->ray.dist = h_inter;
		else
			game->ray.dist = v_inter;
		render_wall(game);
		game->ray.angle += game->fov_rd / SCREEN_WIDTH;
		game->ray.i_ray++;
	}
	return ;
}
