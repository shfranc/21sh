/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/06 16:56:23 by sfranc            #+#    #+#             */
/*   Updated: 2017/07/18 17:33:54 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"
#include <stdio.h>

/*
** 2 functions to change cursos coordinate, without moves.
*/

/*void	ft_increase_cursorpos(t_input *input)
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
}*/

/*
** Insert an char or a string into the current line.
*/

void	ft_insertchar(char *buff, t_input *input)
{
	char	*begin;
	char	*end;
	int		start;
	int		buff_size;

	if (!*buff)
		return ;

	buff_size = ft_strlen(buff);
	if (input->len < INPUTSIZE - buff_size - 2)
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
		input->len += buff_size;
		ft_goto_lastpos(input);
		while (buff_size-- > 0)
			ft_move_right(input);
		free(begin);
		free(end);
	}
	else
		tputs(tgetstr("bl", NULL), 1, &ft_intputchar);
}

/*
** Delete the char right on the left, with "delete" key.
*/

void	ft_back_deletechar(t_input *input)
{
	char	*begin;
	char	*end;
	int		start;

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
		input->len--;
		ft_goto_lastpos(input);
		ft_move_left(input);
		free(begin);
		free(end);
	}
	else
		tputs(tgetstr("bl", NULL), 1, &ft_intputchar);
}

/*
** Delete the char right below the cursor with ctrl + D.
*/

void	ft_deletechar(t_input *input)
{
	char	*begin;
	char	*end;
	int 	start;

	start = input->y * (input->width + 1) + input->x - input->prompt;
	if (start >= 0 && start < input->len)
	{
		ft_clear(input);
		begin = ft_strsub(input->line, 0, start);	
		end = ft_strsub(input->line, start + 1, input->len - ft_strlen(begin));
		ft_bzero(input->line, INPUTSIZE);
		input->line = ft_strcpy(input->line, begin);
		input->line = ft_strcat(input->line, end);
		ft_putstr(input->line);
		input->len--;
		ft_goto_lastpos(input);
		free(begin);
		free(end);
	}
	else
		tputs(tgetstr("bl", NULL), 1, &ft_intputchar); 
}
