/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 18:47:15 by sfranc            #+#    #+#             */
/*   Updated: 2017/06/28 18:29:50 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

void	ft_init_term(void)
{
	const char 	*term_type;
	int		ret;

	term_type = getenv("TERM");
	ft_putendl(term_type);

	if (term_type == NULL)
		ft_exit("No TERM in the environement.", 1);
	
	ret = tgetent(NULL, term_type);
	if (ret < 0)
		ft_exit("No access to the termcap database.", 1);
	if (ret == 0)
		ft_exit("Terminal type is not defined.", 1);

	char *term_buff;
	char *temp;
	char PC;
	int	height;
	int width;
	char *cl;
	char *cm;

	term_buff = ft_memalloc(2048);

	height = tgetnum("li");
	width = tgetnum("co");
	ft_putnbr_endl(height);
	ft_putnbr_endl(width);
	cl = tgetstr("cl", &term_buff);
	ft_putendl(cl);
	cm = tgetstr("cm", &term_buff);
	ft_putendl(cm);

	temp = tgetstr("pc", &term_buff);
	PC = temp ? *temp : 0;
	write(1, &PC, 1);
	BC
}
