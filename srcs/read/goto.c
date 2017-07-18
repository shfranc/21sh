/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   goto.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 15:13:47 by sfranc            #+#    #+#             */
/*   Updated: 2017/07/17 17:20:03 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

/*
** Bring the cursor to the beginning of the input, BEFORE the prompt.
*/

void	ft_goto_begin(t_input *input)
{
	int i;

	if (input->y != 0)
	{
		i = input->y;
		while (i--)
			tputs(tgetstr("up", NULL), 1, &ft_intputchar);
	}
	tputs(tgetstr("cr", NULL), 1, &ft_intputchar);
}

/*
** Bring the cursor right after the prompt.
*/

void	ft_goto_prompt(t_input *input)
{
	int i;
	
	ft_goto_begin(input);
	i = input->prompt;
	while (i--)
		tputs(tgetstr("nd", NULL), 1, &ft_intputchar);
}

/*
** After "write", the cursor is moved at the end of the string printed,
** bring the cursor next to the last inserted char.
*/

void	ft_goto_newpos(t_input *input, int cur_y)
{
	int x;
	int	y;
	int	i;


	if (cur_y != 0)
	{
		i = cur_y;
		while (i--)
			tputs(tgetstr("up", NULL), 1, &ft_intputchar);
	}
	tputs(tgetstr("cr", NULL), 1, &ft_intputchar);
	
	y = 0;
	while (y++ < input->y)
		tputs(tgetstr("do", NULL), 1, &ft_intputchar);
	
	x = 0;
	while (x++ < input->x)
		tputs(tgetstr("nd", NULL), 1, &ft_intputchar);

}
