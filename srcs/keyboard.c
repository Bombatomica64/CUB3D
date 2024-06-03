/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:33:50 by lmicheli          #+#    #+#             */
/*   Updated: 2024/06/03 17:36:40 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>

int	is_inbounds(t_game *game, t_pos new_pos)
{
	int	x;
	int	y;

	x = (int)(game->player.pos.x + new_pos.x);
	y = (int)(game->player.pos.y + new_pos.y);
	return (!(game->map[y][x] == '1' || (game->map[y + 1][x] == '1'
		&& game->player.pos.y + new_pos.y - y > 0.9) || (game->map[y
				- 1][x] == '1' && game->player.pos.y + new_pos.y - y < 0.1)
			|| (game->map[y][x + 1] == '1' && game->player.pos.x + new_pos.x
				- x > 0.9) || (game->map[y][x - 1] == '1' && game->player.pos.x
				+ new_pos.x - x < 0.1) || game->map[y][x] == 'D' || (game->map[y
				+ 1][x] == 'D' && game->player.pos.y + new_pos.y - y > 0.9)
			|| (game->map[y - 1][x] == 'D' && game->player.pos.y + new_pos.y
				- y < 0.1) || (game->map[y][x + 1] == 'D' && game->player.pos.x
				+ new_pos.x - x > 0.9) || (game->map[y][x - 1] == 'D'
				&& game->player.pos.x + new_pos.x - x < 0.1)));
}

int	game_loop(t_game *game)
{
	t_pos	new_pos_x;
	t_pos	new_pos_y;

	new_pos_x.x = game->player.dir.x * MOVE_SPEED * (game->keys.w
			- game->keys.s);
	new_pos_x.y = 0;
	new_pos_y.x = 0;
	new_pos_y.y = game->player.dir.y * MOVE_SPEED * (game->keys.w
			- game->keys.s);
	new_pos_x.x += game->player.dir.y * MOVE_SPEED * (game->keys.a
			- game->keys.d);
	new_pos_y.y -= game->player.dir.x * MOVE_SPEED * (game->keys.a
			- game->keys.d);
	if (is_inbounds(game, new_pos_x))
		game->player.pos = add(game->player.pos, new_pos_x);
	if (is_inbounds(game, new_pos_y))
		game->player.pos = add(game->player.pos, new_pos_y);
	game->player.dir = rot(game->player.dir, ROT_SPEED * game->keys.right);
	game->player.plane = rot(game->player.plane, ROT_SPEED * game->keys.right);
	game->player.dir = rot(game->player.dir, -ROT_SPEED * game->keys.left);
	game->player.plane = rot(game->player.plane, -ROT_SPEED * game->keys.left);
	if (BONUS)
		move_player(game);
	return (0);
}

int	on_destroy(t_game *data)
{
	err_exit("Exiting\n", data);
	return (0);
}

int	on_key_press(int keysym, t_game *game)
{
	if (keysym == XK_Escape)
		err_exit("Exiting\n", game);
	if (BONUS && keysym == XK_space)
		door_opening(game);
	if (keysym == XK_w)
		game->keys.w = 1;
	else if (keysym == XK_a)
		game->keys.a = 1;
	else if (keysym == XK_s)
		game->keys.s = 1;
	else if (keysym == XK_d)
		game->keys.d = 1;
	else if (keysym == XK_Left)
		game->keys.left = 1;
	else if (keysym == XK_Right)
		game->keys.right = 1;
	return (0);
}

int	on_key_release(int keysym, t_game *game)
{
	if (keysym == XK_w)
		game->keys.w = 0;
	else if (keysym == XK_a)
		game->keys.a = 0;
	else if (keysym == XK_s)
		game->keys.s = 0;
	else if (keysym == XK_d)
		game->keys.d = 0;
	else if (keysym == XK_Left)
		game->keys.left = 0;
	else if (keysym == XK_Right)
		game->keys.right = 0;
	return (0);
}
