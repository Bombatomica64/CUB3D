/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 11:17:25 by lmicheli          #+#    #+#             */
/*   Updated: 2024/06/04 15:29:57 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>

// static int	compare(const void *first, const void *second)
// {
// 	if (*(int *)first > *(int *)second)
// 		return (1);
// 	else if (*(int *)first < *(int *)second)
// 		return (-1);
// 	else
// 		return (0);
// }

void	sort_order(t_pair *orders, int amount)
{
	t_pair	tmp;
	t_curs	curs;

	curs = (t_curs){0, 0, 0, 0};
	while (curs.i < amount)
	{
		curs.j = 0;
		while (curs.j < amount - 1)
		{
			if (orders[curs.j].first > orders[curs.j + 1].first)
			{
				tmp.first = orders[curs.j].first;
				tmp.second = orders[curs.j].second;
				orders[curs.j].first = orders[curs.j + 1].first;
				orders[curs.j].second = orders[curs.j + 1].second;
				orders[curs.j + 1].first = tmp.first;
				orders[curs.j + 1].second = tmp.second;
			}
			curs.j++;
		}
		curs.i++;
	}
}

void	sortsprites(int *order, double *dist, int amount)
{
	t_pair	*sprites;
	t_curs	curs;

	curs = (t_curs){0, 0, 0, 0};
	sprites = (t_pair *)malloc(sizeof(t_pair) * amount);
	while (curs.i < amount)
	{
		sprites[curs.i].first = dist[curs.i];
		sprites[curs.i].second = order[curs.i];
		curs.i++;
	}
	sort_order(sprites, amount);
	while (curs.j < amount)
	{
		dist[curs.j] = sprites[amount - curs.j - 1].first;
		order[curs.j] = sprites[amount - curs.j - 1].second;
		curs.j++;
	}
	free(sprites);
}

void	swap(int *a, int *b)
{
	int	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	sprite_calc(t_game *game)
{
	t_norminette	spr;

	sort_order(&spr, game);
	spr.curs.j = 0;
	while (spr.curs.j < game->bonus.sprite.nb_sprites)
	{
		get_draws(&spr, game);
		while (spr.stripe < spr.drw_end_x)
		{
			assign_color(&spr, game);
		}
		spr.curs.j++;
	}
}
