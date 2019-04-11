/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkostrub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 12:14:44 by kkostrub          #+#    #+#             */
/*   Updated: 2018/06/02 17:31:12 by kkostrub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	ft_usage(void)
{
	ft_putendl("usage: ./fillit [Enter the input file]");
	exit(0);
}

void	ft_error(void)
{
	ft_putendl("error");
	exit(0);
}

t_lst	*check_file(int argc, char *str)
{
	int		fd;
	int		ret;
	char	buf[BUF_SIZE];
	t_lst	*head;
	int		len;

	head = NULL;
	if (argc != 2)
		ft_usage();
	if (!(fd = open(str, O_RDONLY)))
		ft_error();
	if (!(ret = (int)read(fd, buf, BUF_SIZE)))
		ft_error();
	buf[ret] = '\0';
	if (check(buf) == 0)
		ft_error();
	len = (int)ft_strlen(buf);
	if (!(head = save_tetrimino(head, buf, len)))
	{
		delete_listfrom_tail(&head);
		ft_error();
	}
	return (head);
}

int		main(int argc, char **argv)
{
	char	*square;
	t_lst	*head;

	head = check_file(argc, argv[1]);
	if (!(square = make_smallest_square(calc_smallest_square(head, 0))))
	{
		delete_listfrom_tail(&head);
		ft_error();
	}
	place_my_tetrimino(&head, &square);
	ft_putstr(square);
	delete_sqr(&square);
	delete_listfrom_tail(&head);
	return (0);
}
