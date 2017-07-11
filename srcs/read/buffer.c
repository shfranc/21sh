/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/06 16:56:23 by sfranc            #+#    #+#             */
/*   Updated: 2017/07/11 17:50:05 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"
#include <stdio.h>

void	ft_insertchar(char *buff, t_input *input)
{
	char	*begin;
	char	*end;
	int		start;
	int		cur_y;

	if (input->x < INPUTSIZE - 2)
	{
		ft_clear(input);
		start = input->y * (input->width + 1) + input->x - input->prompt;
		begin = ft_strsub(input->line, 0, start);
		end = ft_strsub(input->line, start, input->len - ft_strlen(begin));
		ft_bzero(input->line, INPUTSIZE);
		input->line = ft_strcpy(input->line, begin);
		input->line = ft_strcat(input->line, buff);
		input->line = ft_strcat(input->line, end);
		ft_putstr(input->line);
		ft_increase_cursorpos(input);
		input->len++;
		cur_y = (input->len + input->prompt - 1) / (input->width + 1);
		ft_goto_newpos(input, cur_y);
		free(begin);
		free(end);
	}
	else
		tputs(tgetstr("bl", NULL), 1, &ft_intputchar);
}

void	ft_deletechar(t_input *input)
{
	char	*begin;
	char	*end;
	int		start;
	int		cur_y;

	if ((input->y == 0 && input->x > input->prompt) || input->y > 0)
	{
		ft_clear(input);
		start = input->y * (input->width + 1) + input->x - input->prompt;
		begin = ft_strsub(input->line, 0, start - 1);
		end = ft_strsub(input->line, start, input->len - ft_strlen(begin));
		ft_bzero(input->line, INPUTSIZE);
		input->line = ft_strcpy(input->line, begin);
		input->line = ft_strcat(input->line, end);
		ft_putstr(input->line);
		ft_decrease_cursorpos(input);
		input->len--;
		cur_y = (input->len + input->prompt - 1) / (input->width + 1);
		ft_goto_newpos(input, cur_y);
		free(begin);
		free(end);
	}
	else
		tputs(tgetstr("bl", NULL), 1, &ft_intputchar);
}
