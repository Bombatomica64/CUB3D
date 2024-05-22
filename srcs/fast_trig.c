/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fast_trig.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:35:14 by lmicheli          #+#    #+#             */
/*   Updated: 2024/05/22 10:38:59 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>

void	init_trig_tables(t_game *game)
{
	int	i;

	i = 0;
	while (i < 360)
	{
		game->sin_table[i] = sin(i * M_PI / 180);
		game->cos_table[i] = cos(i * M_PI / 180);
		i++;
	}
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
