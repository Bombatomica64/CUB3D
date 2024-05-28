/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fast_trig.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by lmicheli          #+#    #+#             */
/*   Updated: 2024/05/27 10:11:46 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>

void	init_trig(t_game *game)
{
	int	i;

	i = 0;
	while (i < 360)
	{
		game->sin_table[i] = sin(i * M_PI / 180);
		game->cos_table[i] = cos(i * M_PI / 180);
		i++;
	}
	game->sin_table[0] = 0;
	game->cos_table[0] = 1;
	game->sin_table[90] = 1;
	game->cos_table[90] = 0;
	game->sin_table[180] = 0;
	game->cos_table[180] = -1;
	game->sin_table[270] = -1;
	game->cos_table[270] = 0;
}

double	fast_sin(double angle, t_game *game)
{
	return (game->sin_table[(int)angle % 360]);
}

double	fast_cos(double angle, t_game *game)
{
	return (game->cos_table[(int)angle % 360]);
}

double	fast_tan(double angle, t_game *game)
{
	return (fast_sin(angle, game) / fast_cos(angle, game));
}
