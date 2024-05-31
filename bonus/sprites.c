/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 11:17:25 by lmicheli          #+#    #+#             */
/*   Updated: 2024/05/31 12:13:20 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>

static int	compare(const void *first, const void *second)
{
	if (*(int *)first > *(int *)second)
		return (1);
	else if (*(int *)first < *(int *)second)
		return (-1);
	else
		return (0);
}

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

// void	merge(t_pair *orders, int left, int mid, int right)
// {
// 	int		n1;
// 	int		n2;
// 	t_pair	l[n1];
// 	t_pair	r[n2];
// 	int		i = 0, j = 0, k;

// 	i = 0, j = 0, k = left;
// 	while (i < n1 && j < n2)
// 	{
// 		if (l[i].first <= r[j].first)
// 		{
// 			orders[k] = l[i];
// 			i++;
// 		}
// 		else
// 		{
// 			orders[k] = r[j];
// 			j++;
// 		}
// 		k++;
// 	}
// 	while (i < n1)
// 	{
// 		orders[k] = l[i];
// 		i++;
// 		k++;
// 	}
// 	while (j < n2)
// 	{
// 		orders[k] = r[j];
// 		j++;
// 		k++;
// 	}
// }

// void	merge_sort(t_pair *orders, int left, int right)
// {
// 	int	mid;

// 	if (left < right)
// 	{
// 		mid = left + (right - left) / 2;
// 		merge_sort(orders, left, mid);
// 		merge_sort(orders, mid + 1, right);
// 		merge(orders, left, mid, right);
// 	}
// }
// void	sort_order(t_pair *orders, int amount)
// {
// 	merge_sort(orders, 0, amount - 1);
// }

