/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/17 18:54:44 by sfranc            #+#    #+#             */
/*   Updated: 2017/07/17 18:55:05 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

int		ft_interpret(char *buff, t_input *input)
{
		(void)input;
//		printf("\nkey: %d %d %d %d %d %d\n", buff[0], buff[1], buff[2], buff[3], buff[4], buff[5]);
		//	printf("\nwidth:%d x:%d y:%d\n", input->width, input->x, input->y);

	if (buff[0] == 27 && buff[1] == 91 && buff[2] == 67)
		ft_move_right(input);

	if (buff[0] == 27 && buff[1] == 91 && buff[2] == 68)
		ft_move_left(input);

	if (buff[0] == 27 && buff[1] == 91 && buff[2] == 53 && buff[3] == 126)
		ft_move_up(input);

	if (buff[0] == 27 && buff[1] == 91 && buff[2] == 54 && buff[3] == 126)
		ft_move_down(input);

	if (buff[0] == 1 || (buff[0] == 27 && buff[1] == 91 && buff[2] == 72))
		ft_beginning_of_line(input);
	
	if (buff[0] == 5 || (buff[0] == 27 && buff[1] == 91 && buff[2] == 70))
		ft_end_of_line(input);

	if (buff[0] == 6)
		ft_jumpword_forward(input);

	if (buff[0] == 2)
		ft_jumpword_backward(input);

	if (buff[0] == '\n')
	{
		ft_accept_line(input);
		return (1);
	}

	if (buff[0] == 12)
		ft_clear_screen(input);

	if (ft_isprint(buff[0])) // buff entier est isprint pas de \n.
		ft_insertchar(buff, input);

	if (buff[0] == 127)
		ft_back_deletechar(input);	

	if (buff[0] == 4 && *input->line)
		ft_deletechar(input);

	if (buff[0] == 4 && !*input->line)
		ft_exit("exit", 1);

	return (0);
}
/*
 ** MOVE COMMANDS
 ** > --> move right ((buff[0] == 27 && buff[1] == 91 && buf[2] == 67)
 ** < --> move left ((buff[0] == 27 && buff[1] == 91 && buf[2] == 68)
 ** ctlr + a --> beginning-of-line (buff[0] == 1 || buff[0] == 27 && buff[1] == 91 && buff[2] == 72)
 ** ctlr + e --> end-of-line (buff[0] == 5 || buff[0] = 27 && buff[1] == 91 && buff[2] == 70)
 ** meta + f --> forward-word (buff[0] == 102)
 ** meta + b --> backward-word (buff[0] == 98)
 ** ctrl + l --> clear-screen (buff[0] == 12)
 ** EDITING COMMANDS
 ** ctrl + d --> delete-char/EOF (buff[0] = 4)
 **
 */
