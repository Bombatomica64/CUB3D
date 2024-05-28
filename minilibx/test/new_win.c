/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_win.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by lmicheli          #+#    #+#             */
/*   Updated: 2024/05/28 11:09:36 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "mlx.h"


void *mlx;
void *win1;
void *win2;



int gere_mouse(int x,int y,int button,void*toto)
{
  printf("Mouse event - new win\n");
  mlx_destroy_window(mlx,win1);
  win1 = mlx_new_window(mlx,random()%500,random()%500,"new win");
  mlx_mouse_hook(win1,gere_mouse,0);
}


int main()
{
  srandom(time(0));
  mlx = mlx_init();
  win1 = mlx_new_window(mlx,300,300,"win1");
  win2 = mlx_new_window(mlx,600,600,"win2");
  mlx_mouse_hook(win1,gere_mouse,0);
  mlx_mouse_hook(win2,gere_mouse,0);
  mlx_loop(mlx);
}
