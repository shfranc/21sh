/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_moves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/03 15:53:23 by sfranc            #+#    #+#             */
/*   Updated: 2017/07/12 16:13:45 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"
#include <stdio.h>

void	ft_increase_cursorpos(t_input *input)
{
	if (input->x < input->width)
		input->x++;
	else
	{
		input->x = 0;
		input->y++;
	}
}

void	ft_decrease_cursorpos(t_input *input)
{
	if ((input->y == 0 && input->x > input->prompt) || (input->y > 0 && input->x > 0))
		input->x--;
	else if (input->y > 0 && input->x == 0)
	{
		input->x = input->width;
		input->y--;
	}

}

void	ft_move_right(t_input *input)
{
	if ((input->y * (input->width + 1) + input->x) < (input->prompt + input->len))
	{
		if (input->x < input->width)
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
		i = input->width;
		while (i--)
			tputs(tgetstr("nd", NULL), 1, &ft_intputchar);
		tputs(tgetstr("up", NULL), 1, &ft_intputchar);
		input->x = input->width;
		input->y--;
	}
	else
		tputs(tgetstr("bl", NULL), 1, &ft_intputchar);
}
