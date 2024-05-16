/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:42:14 by lmicheli          #+#    #+#             */
/*   Updated: 2024/05/16 16:26:55 by lmicheli         ###   ########.fr       */
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
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	ft_free_matrix(game->input.map_and_txt);
	ft_free_matrix(game->txts.txts);
	ft_free_matrix(game->map);
	exit(1);
}
