/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_moves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/03 15:53:23 by sfranc            #+#    #+#             */
/*   Updated: 2017/07/03 15:57:42 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

void	ft_move_right(t_input *input)
{
	int index;

	index = input->y * input->width + input->x;

	if (index < (input->prompt + input->len))
	{
		if (input->x < input->width - 1)
		{
			tputs(tgetstr("nd", NULL), 1, &ft_intputchar);
			input->x++;
		}
		else
		{
			tputs(tgetstr("cr", NULL), 1, &ft_intputchar);
			tputs(tgetstr("do", NULL), 1, &ft_intputchar);
			input->x = 0;
			input->y++;
		}
	}
	else
		tputs(tgetstr("bl", NULL), 1, &ft_intputchar);
}

void	ft_move_left(t_input *input)
{
	int i;
	
	if ((input->y == 0 && input->x > input->prompt) || (input->y > 0 && input->x > 0))
	{
		tputs(tgetstr("le", NULL), 1, &ft_intputchar);
		input->x--;
	}
	else if (input->y > 0 && input->x == 0)
	{
		i = input->width - 1;
		while (i--)
			tputs(tgetstr("nd", NULL), 1, &ft_intputchar);
		tputs(tgetstr("up", NULL), 1, &ft_intputchar);
		input->x = input->width - 1;
		input->y--;
	}
	else
		tputs(tgetstr("bl", NULL), 1, &ft_intputchar);
}
