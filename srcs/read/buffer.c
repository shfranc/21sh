/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/06 16:56:23 by sfranc            #+#    #+#             */
/*   Updated: 2017/07/06 16:57:07 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

void	ft_insertchar(char *buff, t_input *input)
{
	char	*begin;
	char	*end;
	int		start;

	if (input->x < INPUTSIZE - 2)
	{
		start = input->y * input->width + input->x - input->prompt;

		begin = ft_strsub(input->line, 0, start);
		end = ft_strsub(input->line, start, ft_strlen(input->line) - ft_strlen(begin));
		ft_bzero(input->line, INPUTSIZE);
		input->line = ft_strcpy(input->line, begin);
		input->line = ft_strcat(input->line, buff);
		input->line = ft_strcat(input->line, end);
		input->len++;
		input->x = input->prompt + ft_strlen(input->line);
		if (input->x > input->width)
		{
			input->y++;
			input->height++;
			input->x = (input->prompt + ft_strlen(input->line)) % input->width;
		}
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

	if (input->x > input->prompt)
	{
		start = input->y * input->width + input->x - input->prompt;
		
		begin = ft_strsub(input->line, 0, start - 1);
		end = ft_strsub(input->line, start, ft_strlen(input->line) - ft_strlen(begin));
		ft_bzero(input->line, INPUTSIZE);
		input->line = ft_strcpy(input->line, begin);
		input->line = ft_strcat(input->line, end);
		input->len--;
		input->x = input->prompt + ft_strlen(input->line);
		free(begin);
		free(end);
	}
	else
		tputs(tgetstr("bl", NULL), 1, &ft_intputchar);
}
