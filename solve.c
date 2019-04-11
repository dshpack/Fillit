/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkostrub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 17:35:49 by kkostrub          #+#    #+#             */
/*   Updated: 2018/06/02 18:20:16 by kkostrub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		is_twins(t_lst *current)
{
	int		i;
	int		flag;
	t_lst	*prev;

	i = 0;
	flag = 0;
	if (!(prev = current->prev))
		return (0);
	while (i < 4)
	{
		if (current->x[i] == prev->x[i] && current->y[i] == prev->y[i])
			flag++;
		i++;
	}
	if (flag == 4)
		return (1);
	return (0);
}

void	move_zdvig(char *square, t_lst *current, int *zdvig_x, int *zdvig_y)
{
	(*zdvig_y)++;
	if (*zdvig_x >= calc_pole(square))
	{
		*zdvig_x = 0;
		*zdvig_y = 0;
	}
	else if (*zdvig_y >= calc_pole(square))
	{
		(*zdvig_x)++;
		*zdvig_y = 0;
	}
	rewrite_tmp_x_y(&current, *zdvig_x, *zdvig_y);
}

void	skip_repack(t_lst *head, t_lst **current, char **square,
t_coords *zdvig)
{
	*square = delete_sqr(square);
	(zdvig->pole_to_resize)++;
	if (!(*square = make_smallest_square(calc_smallest_square(head,
						zdvig->pole_to_resize))))
	{
		delete_listfrom_tail(current);
		ft_error();
	}
	*current = head;
	zdvig->zdvig_x = 0;
	zdvig->zdvig_y = 0;
}

void	do_repack(t_lst *head, t_lst **current, char **square, t_coords *zdvig)
{
	if (!(*current = (*current)->prev))
	{
		*square = delete_sqr(square);
		(zdvig->pole_to_resize)++;
		if (!(*square = make_smallest_square(calc_smallest_square(head,
							zdvig->pole_to_resize))))
		{
			delete_listfrom_tail(current);
			ft_error();
		}
		*current = head;
		zdvig->zdvig_x = 0;
		zdvig->zdvig_y = 0;
		rewrite_tmp_x_y(current, zdvig->zdvig_x, zdvig->zdvig_y);
	}
	else
	{
		rewrite_square(square, (*current)->letter);
		zdvig->zdvig_x = (*current)->tmp_x[1] - (*current)->x[1];
		zdvig->zdvig_y = (*current)->tmp_y[1] - (*current)->y[1];
		if (zdvig->zdvig_y >= calc_pole(*square))
			rewrite_tmp_x_y(current, ++(zdvig->zdvig_x), zdvig->zdvig_y = 0);
		else if (zdvig->zdvig_y < calc_pole(*square))
			rewrite_tmp_x_y(current, zdvig->zdvig_x, ++(zdvig->zdvig_y));
	}
}

void	place_my_tetrimino(t_lst **head, char **square)
{
	t_lst		*current;
	int			res;
	t_coords	zdvig;

	set_zdvig_to_zero(&zdvig);
	current = *head;
	rewrite_tmp_x_y(&current, 0, 0);
	while (current)
	{
		res = try_to_write_tetr(*square, current);
		if (res == 1)
			move_zdvig(*square, current, &zdvig.zdvig_x, &zdvig.zdvig_y);
		else if (res == -1)
			is_twins(current) ? skip_repack(*head, &current, square, &zdvig) :
				do_repack(*head, &current, square, &zdvig);
		else if (res == 2)
		{
			zdvig.zdvig_y = calc_pole(*square);
			move_zdvig(*square, current, &zdvig.zdvig_x, &zdvig.zdvig_y);
		}
		else if (res == 0)
			if (!(save_tetr_to_sqr(&(*square), &current, &zdvig)))
				break ;
	}
}
