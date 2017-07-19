/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/17 18:54:44 by sfranc            #+#    #+#             */
/*   Updated: 2017/07/19 12:36:20 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

int		ft_interpret(char *buff, t_input *input)
{
		(void)input;
//		printf("\nkey: %d %d %d %d %d %d\n", buff[0], buff[1], buff[2], buff[3], buff[4], buff[5]);

	if (buff[0] == 27 && buff[1] == 91 && buff[2] == 67)
		ft_move_right(input);
	else if (buff[0] == 27 && buff[1] == 91 && buff[2] == 68)
		ft_move_left(input);
	else if (buff[0] == 27 && buff[1] == 91 && buff[2] == 53 && buff[3] == 126)
		ft_move_up(input);
	else if (buff[0] == 27 && buff[1] == 91 && buff[2] == 54 && buff[3] == 126)
		ft_move_down(input);
	else if (buff[0] == 1 || (buff[0] == 27 && buff[1] == 91 && buff[2] == 72))
		ft_beginning_of_line(input);
	else if (buff[0] == 5 || (buff[0] == 27 && buff[1] == 91 && buff[2] == 70))
		ft_end_of_line(input);
	else if (buff[0] == 6)
		ft_jumpword_forward(input);
	else if (buff[0] == 2)
		ft_jumpword_backward(input);

	else if (buff[0] == 11)
		ft_copy(input);
	else if (buff[0] == 24)
		ft_cut(input);
	else if (buff[0] == 9)
		ft_insertchar(input->tmp, input);
	else if (ft_isprint(buff[0]))
		ft_insertchar(buff, input);
	else if (buff[0] == 127)
		ft_back_deletechar(input);	
	else if (buff[0] == 27 && buff[1] == 91 && buff[2] == 51 && buff[3] == 126)
		ft_deletechar(input);
	
	else if (buff[0] == 12)
		ft_clear_screen(input);
	else if (buff[0] == '\n')
	{
		ft_accept_line(input);
		return (1);
	}
	else if (buff[0] == 4 && !*input->line)
		ft_exit("exit", 1);

	return (0);
}
