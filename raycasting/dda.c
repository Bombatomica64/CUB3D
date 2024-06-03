/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 23:02:28 by marco             #+#    #+#             */
/*   Updated: 2024/06/03 23:27:10 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>

void	dda_init(t_game *game)
{
	if (game->ray.dir.x < 0)
	{
		game->ray.step.x = -1;
		game->ray.side_dist.x = (game->player.pos.x - game->ray.map.x)
			* game->ray.delta_dist.x;
	}
	else
	{
		game->ray.step.x = 1;
		game->ray.side_dist.x = (game->ray.map.x + 1.0 - game->player.pos.x)
			* game->ray.delta_dist.x;
	}
	if (game->ray.dir.y < 0)
	{
		game->ray.step.y = -1;
		game->ray.side_dist.y = (game->player.pos.y - game->ray.map.y)
			* game->ray.delta_dist.y;
	}
	else
	{
		game->ray.step.y = 1;
		game->ray.side_dist.y = (game->ray.map.y + 1.0 - game->player.pos.y)
			* game->ray.delta_dist.y;
	}
}

t_bool	ray_hit(t_game *game)
{
	char	map_value;

	map_value = game->map[(int)game->ray.map.y][(int)game->ray.map.x];
	if (map_value == '1' || map_value == 'D')
	{
		game->bonus.doors.wall_hit = map_value;
		if (BONUS && map_value == '1' && game->bonus.doors.door_open == 1)
		{
			game->bonus.doors.wallx = (int)game->ray.map.x;
			game->bonus.doors.wally = (int)game->ray.map.y;
		}
		if (BONUS && game->map[(int)game->player.pos.y][(int)game->player.pos.x]
			== 'L')
			game->bonus.doors.insidedoor = true;
		return (true);
	}
	if (map_value == 'L')
	{
		game->bonus.doors.door_open = 1;
		game->bonus.doors.doorx = (int)game->ray.map.x;
		game->bonus.doors.doory = (int)game->ray.map.y;
	}
	return (false);
}

void	dda_exec(t_game *game)
{
	bool	hit;

	hit = false;
	if (BONUS)
		game->bonus.doors = (t_door){0, 0, 0, 0, 0, 0, false};
	while (hit == false)
	{
		if (game->ray.side_dist.x < game->ray.side_dist.y)
		{
			game->ray.side_dist.x += game->ray.delta_dist.x;
			game->ray.map.x += game->ray.step.x;
			game->ray.side = 0;
		}
		else
		{
			game->ray.side_dist.y += game->ray.delta_dist.y;
			game->ray.map.y += game->ray.step.y;
			game->ray.side = 1;
		}
		if (game->ray.map.y < 0.25 || game->ray.map.x < 0.25
			|| game->ray.map.y > game->map_height - 0.25
			|| game->ray.map.x > game->map_width - 1.25)
			break ;
		hit = ray_hit(game);
	}
}
