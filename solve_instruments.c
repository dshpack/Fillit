/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_instruments.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkostrub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 18:30:13 by kkostrub          #+#    #+#             */
/*   Updated: 2018/06/02 18:31:50 by kkostrub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

char	*delete_sqr(char **square)
{
	free(*square);
	*square = NULL;
	return (*square);
}

void	rewrite_tmp_x_y(t_lst **node, int x, int y)
{
	int		i;

	i = 0;
	while (i < 4)
	{
		(*node)->tmp_x[i] = (*node)->x[i] + x;
		(*node)->tmp_y[i] = (*node)->y[i] + y;
		i++;
	}
}

int		try_to_write_tetr(char *square, t_lst *node)
{
	int		i;
	int		pos;
	int		d_polya;
	int		pole_end;

	d_polya = calc_pole(square) + 1;
	i = 3;
	while (i >= 0)
	{
		pole_end = (d_polya * (node->tmp_x[i] + 1)) - 1;
		pos = node->tmp_x[i] * d_polya + node->tmp_y[i];
		if (pos >= (int)ft_strlen(square) - 1)
			return (-1);
		else if (square[pos] == '\n')
			return (2);
		else if (pos == pole_end)
			return (1);
		else if (square[pos] != '.')
			return (1);
		i--;
	}
	return (0);
}

t_lst	*delete_listfrom_tail(t_lst **node)
{
	t_lst	*current;
	t_lst	*tail;

	current = *node;
	if (!current)
		return (NULL);
	if (current->next != NULL)
		while (current->next)
			current = current->next;
	while (current->prev)
	{
		tail = current;
		current = current->prev;
		tail->prev = NULL;
		current->next = NULL;
		free(tail);
		tail = NULL;
	}
	free(current);
	current = NULL;
	return (NULL);
}
