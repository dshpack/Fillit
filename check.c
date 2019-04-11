/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkostrub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 11:53:47 by kkostrub          #+#    #+#             */
/*   Updated: 2018/05/15 12:10:20 by kkostrub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		check_symb(char *str)
{
	int		i;
	int		hash;
	int		point;

	i = 0;
	hash = 0;
	point = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '.')
			point++;
		if (str[i] == '#')
			hash++;
		if (str[i] != '#' && str[i] != '.' && str[i] != '\n')
			return (0);
		i++;
	}
	if (hash % 4 != 0 || point % 12 != 0 || !hash || !point)
		return (0);
	return (1);
}

int		check_slash_n1(char *str)
{
	int		i;
	int		flag;
	int		tetr;
	int		size;

	i = -1;
	flag = 0;
	tetr = 0;
	size = (int)ft_strlen(str);
	while (i <= size + 1 && size != 0)
	{
		i += 21;
		if (str[i] == '\n')
			tetr++;
		else if (str[i] == '\0')
		{
			tetr++;
			break ;
		}
		else
			return (0);
	}
	if (tetr != 0)
		return (1);
	return (0);
}

int		check_slash_n(char *str)
{
	int		i;
	int		flag;

	flag = 0;
	i = 4;
	while (str[i] != '\0')
	{
		if (str[i] == '\n' && str[i + 1] == '\n' &&
				(str[i + 2] == '\0' || str[i + 2] == '\n'))
			return (0);
		flag = (str[i] == '\n') ? flag++ : flag;
		if (flag == 4)
		{
			i += 1;
			if (str[i] != '\n' && str[i] != '\0')
				return (0);
			if (str[i] == '\n' && (str[i + 1] == '.' || str[i + 1] == '#'))
				flag++;
			flag = (flag == 5) ? 5 : flag;
			if (str[i] == '\0')
				return (1);
		}
		i += 5;
	}
	return (1);
}

int		check_shape(char *str)
{
	int		i;
	int		y;
	int		connection;
	int		x;

	i = -1;
	x = 0;
	while (str[x] != '\0')
	{
		i += 0;
		y = i + 21;
		connection = 0;
		while (++i < y)
		{
			if (str[i] == '#' && (str[i + 1] == '#'))
				connection++;
			if (str[i] == '#' && (str[i + 5] == '#') && i < (y - 5))
				connection++;
		}
		if (connection != 4 && connection != 3)
			return (0);
		x = i;
	}
	return (1);
}

int		check(char *str)
{
	int		i;
	int		len;

	i = 0;
	len = (int)ft_strlen(str) + 1;
	if ((str[0] == '#' || str[0] == '.') && (len >= 21 && len <= 546))
	{
		if (check_symb(str) != 1)
			return (0);
		if (check_slash_n1(str) != 1)
			return (0);
		if (check_slash_n(str) != 1)
			return (0);
		if (check_shape(str) != 1)
			return (0);
	}
	else
		return (0);
	return (1);
}
