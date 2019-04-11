/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coords.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkostrub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 13:06:20 by kkostrub          #+#    #+#             */
/*   Updated: 2018/06/02 18:29:02 by kkostrub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	set_zdvig_to_zero(t_coords *zdvig)
{
	zdvig->zdvig_x = 0;
	zdvig->zdvig_y = 0;
	zdvig->pole_to_resize = 0;
}

int		calc_vidstup(int coord)
{
	if (coord >= 5 && coord <= 8)
		coord -= 5;
	else if (coord >= 10 && coord <= 13)
		coord -= 10;
	else if (coord >= 15 && coord <= 18)
		coord -= 15;
	return (coord);
}

int		calc_pohibku(t_lst *current)
{
	int		i;
	int		elem;
	int		pohibka;
	int		vidstup;

	i = -1;
	pohibka = 0;
	if (current->str_coord[0] >= 5 && current->str_coord[0] <= 8)
		pohibka = 5;
	else if (current->str_coord[0] >= 10 && current->str_coord[0] <= 13)
		pohibka = 10;
	else if (current->str_coord[0] >= 15 && current->str_coord[0] <= 18)
		pohibka = 15;
	i = -1;
	elem = 0;
	vidstup = calc_vidstup(current->str_coord[elem]);
	while (++i < 4)
	{
		if (vidstup > calc_vidstup(current->str_coord[i]))
		{
			elem = i;
			vidstup = calc_vidstup(current->str_coord[elem]);
		}
	}
	return (pohibka + vidstup);
}

t_lst	*help_convert_coord_to_descart(t_lst *current, int i)
{
	if (current->str_coord[i] >= 0 && current->str_coord[i] <= 3)
	{
		current->y[i] = current->str_coord[i];
		current->x[i] = 0;
	}
	if (current->str_coord[i] >= 5 && current->str_coord[i] <= 8)
	{
		current->y[i] = current->str_coord[i] - 5;
		current->x[i] = 1;
	}
	if (current->str_coord[i] >= 10 && current->str_coord[i] <= 13)
	{
		current->y[i] = current->str_coord[i] - 10;
		current->x[i] = 2;
	}
	if (current->str_coord[i] >= 15 && current->str_coord[i] <= 18)
	{
		current->y[i] = current->str_coord[i] - 15;
		current->x[i] = 3;
	}
	return (current);
}

void	convert_coord_to_descart(t_lst **node)
{
	int		i;
	t_lst	*current;

	i = 0;
	current = *node;
	while (i < 4)
	{
		help_convert_coord_to_descart(current, i);
		i++;
	}
}
