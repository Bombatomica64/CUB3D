/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:42:14 by lmicheli          #+#    #+#             */
/*   Updated: 2024/05/21 10:53:34 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>

int	err(char *msg)
{
	ft_putstr_fd(msg, 2);
	return (1);
}

void	err_exit(char *msg, t_game *game)
{
	ft_putstr_fd(msg, 2);
	ft_free_matrix(game->input.map_and_txt);
	mlx_destroy_image(game->mlx, game->txts.imgs[0].image);
	mlx_destroy_image(game->mlx, game->txts.imgs[1].image);
	mlx_destroy_image(game->mlx, game->txts.imgs[2].image);
	mlx_destroy_image(game->mlx, game->txts.imgs[3].image);
	mlx_destroy_image(game->mlx, game->txts.imgs[4].image);
	// mlx_destroy_image(game->mlx, game->txts.imgs[5].image);
	ft_free_matrix(game->txts.txts);
	ft_free_matrix(game->map);
	free(game->txts.txt_nm);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	free(game);
	exit(1);
}
