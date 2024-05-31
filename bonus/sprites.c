/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 11:17:25 by lmicheli          #+#    #+#             */
/*   Updated: 2024/05/31 17:37:10 by lmicheli         ###   ########.fr       */
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

void	sprite_calc(t_game *game)
{
	t_curs	curs;
	t_pos	sprite;
	t_pos	transform;
	double	invdet;
	int		sprite_screen_x;
	int		v_move_screen;
	int		sprite_height;
	int		sprite_width;
	int		drw_start_y;
	int		drw_end_y;
	int		drw_start_x;
	int		drw_end_x;
	int		stripe;
	int		texx;
	int		texy;
	int		color;
	int		d;

	curs = (t_curs){0, 0, 0, 0};
	while (curs.i < game->bonus.sprite.nb_sprites)
	{
		game->bonus.sprite.sprite_order[curs.i] = curs.i;
		game->bonus.sprite.sprite_dist[curs.i] = ((game->player.pos.x
					- game->bonus.sprite.pos[curs.i].x) * (game->player.pos.x
					- game->bonus.sprite.pos[curs.i].x) + (game->player.pos.y
					- game->bonus.sprite.pos[curs.i].y) * (game->player.pos.y
					- game->bonus.sprite.pos[curs.i].y));
		curs.i++;
	}
	sortsprites(game->bonus.sprite.sprite_order, game->bonus.sprite.sprite_dist,
		game->bonus.sprite.nb_sprites);
	while (curs.j < game->bonus.sprite.nb_sprites)
	{
		sprite.x = game->bonus.sprite.pos
		[game->bonus.sprite.sprite_order[curs.j]].x
			- game->player.pos.x;
		sprite.y = game->bonus.sprite.pos
		[game->bonus.sprite.sprite_order[curs.j]].y
			- game->player.pos.y;
		invdet = 1.0 / (game->player.plane.x * game->player.dir.y
				- game->player.dir.x * game->player.plane.y);
		transform.x = invdet * (game->player.dir.y * sprite.x
				- game->player.dir.x * sprite.y);
		transform.y = invdet * (-game->player.plane.y * sprite.x
				+ game->player.plane.x * sprite.y);
		sprite_screen_x = (int)((SCREEN_WIDTH / 2) * (1 + transform.x
					/ transform.y));
		v_move_screen = (int)(VMOVE / transform.y);
		sprite_height = (int)fabs(SCREEN_HEIGHT / transform.y) / VDIV;
		drw_start_y = -sprite_height / 2 + SCREEN_HEIGHT / 2 + v_move_screen;
		if (drw_start_y < 0)
			drw_start_y = 0;
		drw_end_y = sprite_height / 2 + SCREEN_HEIGHT / 2 + v_move_screen;
		if (drw_end_y >= SCREEN_HEIGHT)
			drw_end_y = SCREEN_HEIGHT - 1;
		sprite_width = (int)fabs(SCREEN_HEIGHT / transform.y) / UDIV;
		drw_start_x = -sprite_width / 2 + sprite_screen_x;
		if (drw_start_x < 0)
			drw_start_x = 0;
		drw_end_x = sprite_width / 2 + sprite_screen_x;
		if (drw_end_x >= SCREEN_WIDTH)
			drw_end_x = SCREEN_WIDTH - 1;
		stripe = drw_start_x;
		while (stripe < drw_end_x)
		{
			texx = (int)(256 * (stripe - (-sprite_width / 2 + sprite_screen_x))
					* TILE_SIZE / sprite_width) / 256;
			if (transform.y > 0 && stripe > 0 && stripe < SCREEN_WIDTH
				&& transform.y < game->bonus.sprite.zbuffer[stripe])
			{
				curs.k = drw_start_y;
				while (curs.k < drw_end_y)
				{
					d = (curs.k - v_move_screen) * 256 - SCREEN_HEIGHT * 128
						+ sprite_height * 128;
					texy = ((d * TILE_SIZE) / sprite_height) / 256;
					color = game->txts.imgs[7].data[TILE_SIZE
						* texy + texx];
					game->pixels[curs.k][stripe] = color;
					curs.k++;
				}
			}
			stripe++;
		}
	}
	printf("sprite.x = %f\n", sprite.x);
	printf("sprite.y = %f\n", sprite.y);
	printf("drw_start_y = %d\n", drw_start_y);
	printf("drw_end_y = %d\n", drw_end_y);
	printf("drw_start_x = %d\n", drw_start_x);
	printf("drw_end_x = %d\n", drw_end_x);
	printf("sprite_screen_x = %d\n", sprite_screen_x);
	printf("sprite_height = %d\n", sprite_height);
	printf("sprite_width = %d\n", sprite_width);
	printf("transform.x = %f\n", transform.x);
	printf("transform.y = %f\n", transform.y);
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
