/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 12:49:58 by sfranc            #+#    #+#             */
/*   Updated: 2017/06/30 19:19:44 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

int		main(void)
{
	char	buff[6];
	t_input	input;
	struct winsize	win;


	ft_bzero(&input, sizeof(t_input));
	input.line = ft_memalloc(INPUTSIZE);

	if ((ioctl(0, TIOCGWINSZ, &win)) == -1)
		ft_exit("Unable to get winsize struct", 1);
	input.width = win.ws_col;
	input.height = 1;

	input.prompt = ft_display_prompt();
	input.x = input.prompt;

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
