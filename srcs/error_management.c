/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by lmicheli          #+#    #+#             */
/*   Updated: 2024/05/31 11:25:08 by lmicheli         ###   ########.fr       */
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
	if (game->txts.imgs[0].img.image)
		mlx_destroy_image(game->mlx, game->txts.imgs[0].img.image);
	if (game->txts.imgs[1].img.image)
		mlx_destroy_image(game->mlx, game->txts.imgs[1].img.image);
	if (game->txts.imgs[2].img.image)
		mlx_destroy_image(game->mlx, game->txts.imgs[2].img.image);
	if (game->txts.imgs[3].img.image)
		mlx_destroy_image(game->mlx, game->txts.imgs[3].img.image);
	if (game->txts.imgs[4].img.image)
		mlx_destroy_image(game->mlx, game->txts.imgs[4].img.image);
	if (game->txts.imgs[5].img.image)
		mlx_destroy_image(game->mlx, game->txts.imgs[5].img.image);
	ft_free_matrix(game->txts.txts);
	ft_free_matrix(game->map);
	ft_free_matrix((char **)game->pixels);
	if (BONUS)
		ft_free_matrix(game->bonus.minimap);
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
