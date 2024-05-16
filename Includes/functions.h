/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:46:39 by lmicheli          #+#    #+#             */
/*   Updated: 2024/05/16 12:13:47 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include <structs.h>

t_game	*init_game(char *map_path);
char	**parse_map(char *map_path, t_game *game);
void	*put_xmp(void *mlx, char *filename, int *width, int *height);

// error_management.c

void	err(char *msg);

// splut.c

void	split_map(t_game *game);
int		parse_line(char *line, t_game *game);

#endif