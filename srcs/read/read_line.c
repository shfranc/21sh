/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/19 15:01:31 by sfranc            #+#    #+#             */
/*   Updated: 2017/07/31 16:30:45 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

void	ft_accept_line(t_input *input)
{
	ft_clear(input);
	input->line = ft_strcat(input->line, "\n");
	ft_putstr(input->line);
}

void	ft_read_line(char **line, int len_prompt)
{
	char	buff[6];
	t_input	input;

	ft_init_input_struct(&input, len_prompt);
	while (1)
	{
		ft_raw_term();
		ft_bzero(buff, 6);
		read(0, buff, 5);
		if (ft_interpret(buff, &input))
		{
			*line = ft_strdup(input.line);
			break ;
		}
	}
	ft_canonic_term();
	free(input.line);
	free(input.tmp);
}
