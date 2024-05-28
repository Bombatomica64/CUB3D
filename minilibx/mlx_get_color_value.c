/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_get_color_value.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by lmicheli          #+#    #+#             */
/*   Updated: 2024/05/13 10:58:43 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** mlx_get_color_value.c for MiniLibX in 
** 
** Made by Charlie Root
** Login   <ol@epitech.net>
** 
** Started on  Mon Jul 31 19:01:33 2000 Charlie Root
** Last update Thu Oct  4 15:04:13 2001 Charlie Root
*/


#include	"mlx_int.h"


int             mlx_get_color_value(t_xvar *xvar,int color)
{
  return(mlx_int_get_good_color(xvar,color));
}

int		mlx_int_get_good_color(t_xvar *xvar,int color)
{
  XColor	xc;

  if (xvar->depth>=24)
    return (color);
  xc.red = (color>>8)&0xFF00;
  xc.green = color&0xFF00;
  xc.blue = (color<<8)&0xFF00;
  xc.pixel = ((xc.red>>(16-xvar->decrgb[1]))<<xvar->decrgb[0])+
    ((xc.green>>(16-xvar->decrgb[3]))<<xvar->decrgb[2])+
    ((xc.blue>>(16-xvar->decrgb[5]))<<xvar->decrgb[4]);
  return (xc.pixel);
}
