/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_calcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 15:29:16 by lmicheli          #+#    #+#             */
/*   Updated: 2024/06/04 15:33:44 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>

void	sort_order(t_norminette *spr, t_game *game)
{
	t_curs	curs;

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
}

void	calculate_sprite_transform(t_norminette *spr, t_game *game)
{
	spr->sprite.x = game->bonus.sprite.pos
	[game->bonus.sprite.sprite_order[spr->curs.j]].x
		- game->player.pos.x;
	spr->sprite.y = game->bonus.sprite.pos
	[game->bonus.sprite.sprite_order[spr->curs.j]].y
		- game->player.pos.y;
	spr->invdet = 1.0 / (game->player.plane.x * game->player.dir.y
			- game->player.dir.x * game->player.plane.y);
	spr->transform.x = spr->invdet * (game->player.dir.y * spr->sprite.x
			- game->player.dir.x * spr->sprite.y);
	spr->transform.y = spr->invdet * (-game->player.plane.y * spr->sprite.x
			+ game->player.plane.x * spr->sprite.y);
	spr->sprite_screen_x = (int)((SCREEN_WIDTH / 2) * (1 + spr->transform.x
				/ spr->transform.y));
	spr->v_move_screen = (int)(VMOVE / spr->transform.y);
}

void	calculate_draw_parameters(t_norminette *spr)
{
	spr->sprite_height = (int)fabs(SCREEN_HEIGHT / spr->transform.y) / VDIV;
	spr->drw_start_y = -spr->sprite_height / 2 + SCREEN_HEIGHT / 2
		+ spr->v_move_screen;
	if (spr->drw_start_y < 0)
		spr->drw_start_y = 0;
	spr->drw_end_y = spr->sprite_height / 2 + SCREEN_HEIGHT / 2
		+ spr->v_move_screen;
	if (spr->drw_end_y >= SCREEN_HEIGHT)
		spr->drw_end_y = SCREEN_HEIGHT - 1;
	spr->sprite_width = (int)fabs(SCREEN_HEIGHT / spr->transform.y) / UDIV;
	spr->drw_start_x = ((spr->sprite_width / 2) * -1) + spr->sprite_screen_x;
	if (spr->drw_start_x < 0)
		spr->drw_start_x = 0;
	spr->drw_end_x = spr->sprite_width / 2 + spr->sprite_screen_x;
	if (spr->drw_end_x >= SCREEN_WIDTH)
		spr->drw_end_x = SCREEN_WIDTH - 1;
	spr->stripe = spr->drw_start_x;
}

void	get_draws(t_norminette *spr, t_game *game)
{
	calculate_sprite_transform(spr, game);
	calculate_draw_parameters(spr);
}

void	assign_color(t_norminette *spr, t_game *game)
{
	spr->texx = (int)(256 * (spr->stripe - (-spr->sprite_width / 2
					+ spr->sprite_screen_x)) * TILE_SIZE / spr->sprite_width)
		/ 256;
	if (spr->transform.y > 0 && spr->stripe > 0 && spr->stripe < SCREEN_WIDTH
		&& spr->transform.y < game->bonus.sprite.zbuffer[spr->stripe])
	{
		spr->curs.k = spr->drw_start_y;
		while (spr->curs.k < spr->drw_end_y)
		{
			spr->d = (spr->curs.k - spr->v_move_screen) * 256 - SCREEN_HEIGHT
				* 128 + spr->sprite_height * 128;
			spr->texy = ((spr->d * TILE_SIZE) / spr->sprite_height) / 256;
			spr->color = game->txts.imgs
			[game->bonus.sprite.text_nb].data[TILE_SIZE
				* spr->texy + spr->texx];
			if ((spr->color & 0x00FFFFFF) != 0)
				game->pixels[spr->curs.k][spr->stripe] = spr->color;
			spr->curs.k++;
		}
	}
	spr->stripe++;
}
