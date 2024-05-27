/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smallsteps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 10:32:56 by lmicheli          #+#    #+#             */
/*   Updated: 2024/05/27 12:57:53 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>

t_pos	get_wal(t_game *game, t_pos first_step, t_pos steps)
{
	while (is_wall(first_step.x, first_step.y, game) == 0)
	{
		first_step.x += steps.x;
		first_step.y += steps.y;
	}
	first_step.wall_hit = get_texture_id(game);
	return (first_step);
}

t_pos	smallstep_q1(t_game *game)
{
	t_pos	first_step;
	t_pos	steps;

	if (game->ray.angle > M_PI_4)
	{
		first_step.x = TILE_SIZE - fmod(game->player.x, TILE_SIZE);
		first_step.y = first_step.x * tan(game->ray.angle);
		first_step.x = game->player.x + first_step.x;
		first_step.y = game->player.y + first_step.y;
		steps.y = TILE_SIZE;
		steps.x = TILE_SIZE * tan(game->ray.angle);
	}
	else
	{
		first_step.y = TILE_SIZE - fmod(game->player.y, TILE_SIZE);
		first_step.x = first_step.y / tan(game->ray.angle);
		first_step.x = game->player.x + first_step.x;
		first_step.y = game->player.y + first_step.y;
		steps.x = TILE_SIZE;
		steps.y = TILE_SIZE * tan(game->ray.angle);
	}
	if (is_wall(first_step.x, first_step.y, game) == 1)
		return (first_step);
	first_step = get_wal(game, first_step, steps);
	return (first_step);
}

t_pos	smallstep_q2(t_game *game)
{
	t_pos	first_step;
	t_pos	steps;

	if (game->ray.angle > 3 * M_PI_4)
	{
		first_step.x = fmod(game->player.x, TILE_SIZE);
		first_step.y = first_step.x * tan(game->ray.angle);
		first_step.x = game->player.x - first_step.x;
		first_step.y = game->player.y - first_step.y;
		steps.x = TILE_SIZE;
		steps.y = TILE_SIZE * tan(game->ray.angle);
	}
	else
	{
		first_step.y = fmod(game->player.y, TILE_SIZE);
		first_step.x = first_step.y * tan(game->ray.angle);
		first_step.x = game->player.x - first_step.x;
		first_step.y = game->player.y - first_step.y;
		steps.x = TILE_SIZE;
		steps.y = TILE_SIZE * tan(game->ray.angle);
	}
	if (is_wall(first_step.x, first_step.y, game) == 1)
		return (first_step);
	first_step = get_wal(game, first_step, steps);
	return (first_step);
}

t_pos	smallstep_q3(t_game *game)
{
	t_pos	first_step;
	t_pos	steps;

	if (game->ray.angle > 5 * M_PI_4)
	{
		first_step.y = TILE_SIZE - fmod(game->player.y, TILE_SIZE);
		first_step.x = first_step.y * tan(game->ray.angle);
		first_step.x = game->player.x - first_step.x;
		first_step.y = game->player.y + first_step.y;
		steps.y = TILE_SIZE;
		steps.x = TILE_SIZE * tan(game->ray.angle);
	}
	else
	{
		first_step.x = fmod(game->player.x, TILE_SIZE);
		first_step.y = first_step.y * tan(game->ray.angle);
		first_step.x = game->player.x - first_step.x;
		first_step.y = game->player.y + first_step.y;
		steps.x = TILE_SIZE;
		steps.y = TILE_SIZE * tan(game->ray.angle);
	}
	if (is_wall(first_step.x, first_step.y, game) == 1)
		return (first_step);
	first_step = get_wal(game, first_step, steps);
	return (first_step);
}

t_pos	smallstep_q4(t_game *game)
{
	t_pos	first_step;
	t_pos	steps;

	if (game->ray.angle > 7 * M_PI_4)
	{
		first_step.x = TILE_SIZE - fmod(game->player.x, TILE_SIZE);
		first_step.y = first_step.x * tan(game->ray.angle);
		first_step.x = game->player.x + first_step.x;
		first_step.y = game->player.y - first_step.y;
		steps.x = TILE_SIZE;
		steps.y = TILE_SIZE * tan(game->ray.angle);
	}
	else
	{
		first_step.y = TILE_SIZE - fmod(game->player.y, TILE_SIZE);
		first_step.x = first_step.y * tan(game->ray.angle);
		first_step.x = game->player.x + first_step.x;
		first_step.y = game->player.y + first_step.y;
		steps.y = TILE_SIZE;
		steps.x = TILE_SIZE * tan(game->ray.angle);
	}
	if (is_wall(first_step.x, first_step.y, game) == 1)
		return (first_step);
	first_step = get_wal(game, first_step, steps);
	return (first_step);
}
