/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by lmicheli          #+#    #+#             */
/*   Updated: 2024/05/29 17:22:18 by mruggier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>

t_pos	rotate(t_pos pos, double angle)
{
	t_pos	new_pos;

	new_pos.x = pos.x * cos(angle) - pos.y * sin(angle);
	new_pos.y = pos.x * sin(angle) + pos.y * cos(angle);
	return (new_pos);
}

int	game_loop(t_game *game)
{

	printf("game->keys.w[%d]\n", game->keys.w);
	printf("game->keys.a[%d]\n", game->keys.a);
	printf("game->keys.s[%d]\n", game->keys.s);
	printf("game->keys.d[%d]\n", game->keys.d);
	printf("game->keys.left[%d]\n", game->keys.left);
	printf("game->keys.right[%d]\n", game->keys.right);
	
	/*if (keysym == XK_Escape)
		err_exit("Exiting\n", game);*/
	if (game->keys.s && !game->keys.w)//(keysym == XK_s)
	{
		game->player.pos.y -= game->player.dir.y * MOVE_SPEED;
		game->player.pos.x -= game->player.dir.x * MOVE_SPEED;
	}
	else if (game->keys.w && !game->keys.s)//(keysym == XK_w)
	{
		game->player.pos.x += game->player.dir.x * MOVE_SPEED;
		game->player.pos.y += game->player.dir.y * MOVE_SPEED;
	}
	else if (game->keys.d && !game->keys.a)//(keysym == XK_d)
	{
		game->player.pos.x -= game->player.dir.y * MOVE_SPEED;
		game->player.pos.y += game->player.dir.x * MOVE_SPEED;
	}
	else if (game->keys.a && !game->keys.d)//(keysym == XK_a)
	{
		game->player.pos.x += game->player.dir.y * MOVE_SPEED;
		game->player.pos.y -= game->player.dir.x * MOVE_SPEED;
	}
	else if (game->keys.right && !game->keys.left)//(keysym == XK_Right)
	{
		game->player.dir = rotate(game->player.dir, ROT_SPEED);
		game->player.plane = rotate(game->player.plane, ROT_SPEED);
	}
	else if (game->keys.left && !game->keys.right)//(keysym == XK_Left)
	{
		game->player.dir = rotate(game->player.dir, -ROT_SPEED);
		game->player.plane = rotate(game->player.plane, -ROT_SPEED);
	}
	return (0);
}

int	on_destroy(t_game *data)
{
	err_exit("Exiting\n", data);
	return (0);
}

int	on_key_press(int keysym, t_game *game)
{
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
	mlx_hook(data->win, KeyPress, KeyPressMask,
		&on_key_press, data);
	mlx_hook(data->win, KeyRelease, KeyReleaseMask,
	 	&on_key_release, data);
	mlx_hook(data->win, DestroyNotify, StructureNotifyMask,
		&on_destroy, data);
	mlx_loop_hook(data->mlx, &render_images, data);
	//mlx_loop_hook(data->win, &game_loop, data);
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
	printf("game.mlx[%p]\n", game->mlx);
	mlx_put_image_to_window(game->mlx, game->win, game->txts.imgs[0].img.image, 0, 0);
	mlx_put_image_to_window(game->mlx, game->win, game->txts.imgs[1].img.image, 100, 0);
	mlx_put_image_to_window(game->mlx, game->win, game->txts.imgs[2].img.image, 200, 0);
	mlx_put_image_to_window(game->mlx, game->win, game->txts.imgs[3].img.image, 300, 0);
	mlx_put_image_to_window(game->mlx, game->win, game->txts.imgs[4].img.image, 400, 0);
	mlx_put_image_to_window(game->mlx, game->win, game->txts.imgs[5].img.image, 500, 0);
	key_input(game);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	return (0);
}
