/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:46:39 by lmicheli          #+#    #+#             */
/*   Updated: 2024/05/16 18:21:43 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include <structs.h>

t_game	*init_game(char *map_path);
char	**parse_map(char *map_path, t_game *game);

// srcs/put_image.c
void	*put_xmp(void *mlx, char *filename, int *width, int *height);
t_img	get_img(char *path, t_game *game);

// error_management.c

int		err(char *msg);
void	err_exit(char *msg, t_game *game);

// splut.c

void	split_map(t_game *game);
int		parse_line(char *line, t_game *game);

// color.c

char	*create_color_file(t_color color, t_game *game, int nm);

#endif