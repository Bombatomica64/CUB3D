/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by lmicheli          #+#    #+#             */
/*   Updated: 2024/06/02 14:51:12 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>

t_pos	rot(t_pos pos, double angle)
{
	t_pos	new_pos;

	new_pos.x = pos.x * cos(angle) - pos.y * sin(angle);
	new_pos.y = pos.x * sin(angle) + pos.y * cos(angle);
	return (new_pos);
}

int	is_inbounds(t_game *game, t_pos new_pos)
{
	int	x;
	int	y;

	x = (int)(game->player.pos.x + new_pos.x);
	y = (int)(game->player.pos.y + new_pos.y);
	return (!(game->map[y][x] == '1' || (game->map[y + 1][x] == '1' && game->player.pos.y + new_pos.y - y > 0.9) 
		|| (game->map[y - 1][x] == '1' && game->player.pos.y + new_pos.y - y < 0.1)
		|| (game->map[y][x + 1] == '1' && game->player.pos.x + new_pos.x - x > 0.9) 
		|| (game->map[y][x - 1] == '1' && game->player.pos.x + new_pos.x - x < 0.1)
		|| game->map[y][x] == 'D' || (game->map[y + 1][x] == 'D' && game->player.pos.y + new_pos.y - y > 0.9) 
		|| (game->map[y - 1][x] == 'D' && game->player.pos.y + new_pos.y - y < 0.1)
		|| (game->map[y][x + 1] == 'D' && game->player.pos.x + new_pos.x - x > 0.9) 
		|| (game->map[y][x - 1] == 'D' && game->player.pos.x + new_pos.x - x < 0.1)));
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

void door_opening(t_game *game)
{
	int	x;
	int	y;

	x = (int)(game->player.pos.x + game->player.dir.x);
	y = (int)(game->player.pos.y + game->player.dir.y);
	if (game->map[y][x] == 'D')
		game->map[y][x] = 'L';
	else if (game->map[y][x] == 'L')
		game->map[y][x] = 'D';
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

void	key_input(t_game *data)
{
	mlx_hook(data->win, KeyPress, KeyPressMask, &on_key_press, data);
	mlx_hook(data->win, KeyRelease, KeyReleaseMask, &on_key_release, data);
	mlx_hook(data->win, DestroyNotify, StructureNotifyMask, &on_destroy, data);
	mlx_loop_hook(data->mlx, &render_images, data);
	mlx_loop(data->mlx);
}

int	main(int ac, char **av)
{
	t_game	*game;

	if (ac != 2)
	{
		printf("Error\nWrong number of arguments\n");
		return (1);
	}
	if (ft_strncmp(av[1] + ft_strlen(av[1]) - 4, ".cub", 4))
	{
		printf("Error\nWrong file extension\n");
		return (1);
	}
	game = init_game(av[1]);
	if (!game->mlx)
	{
		printf("Error\nFailed to init mlx\n");
		return (1);
	}
	printf("bonus = %d\n", BONUS);
	printf("game.mlx[%p]\n", game->mlx);
	mlx_mouse_move(game->mlx, game->win, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	mlx_mouse_hide(game->mlx, game->win);
	key_input(game);
	return (0);
}
