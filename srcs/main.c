/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 12:49:58 by sfranc            #+#    #+#             */
/*   Updated: 2017/07/18 18:30:54 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"
/*
void	ft_signals_handler(int sig)
{
	printf("signal:n*%d\n", sig);
}

int		ft_catch_signals()
{
	int i = 0;
	while (++i < 32)
		signal(i, &ft_signals_handler);
	return (1);
}
*/
int		main(void)
{
	char	buff[6];
	t_input	input;

//	ft_catch_signals();

	ft_init_input_struct(&input);

	while (1)
	{
		ft_raw_term();
		ft_bzero(buff, 6);
		read(0, buff, 6);
		if (ft_interpret(buff, &input))
			break ;
	}
	ft_canonic_term();
	return (0);
}
