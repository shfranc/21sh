/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/19 15:01:31 by sfranc            #+#    #+#             */
/*   Updated: 2017/09/26 19:44:44 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

void		ft_accept_line(t_input *input)
{
	ft_clear(input);
	input->line = ft_strcat(input->line, "\n");
	ft_putstr(input->line);
}

static void	ft_save_in_history(char *line)
{
	char *tmp;

	tmp = ft_strsub(line, 0, ft_strlen(line) - 1);
	ft_addtotab(&g_shell->history, tmp);
	free(tmp);
	g_shell->histo_index = ft_tablen(g_shell->history);
}

void		ft_read_line(char **line, int len_prompt, int mode)
{
	char	buff[6];

	ft_init_input_struct(&g_shell->input, len_prompt);
	while (1)
	{
		ft_raw_term();
		ft_bzero(buff, 6);
		if ((read(0, buff, 5)) == -1)
			break ;
		if (g_shell->sigint || ft_interpret(buff, &g_shell->input, mode))
		{
			*line = ft_strdup(g_shell->input.line);
			break ;
		}
	}
	if (!g_shell->sigint && (mode == DEFAULT || mode == QUOTES || mode == LIST)\
			&& !ft_strequ(*line, "\n") && !ft_strequ(*line, ""))
		ft_save_in_history(*line);
	ft_canonic_term();
	free(g_shell->input.line);
	free(g_shell->input.tmp);
}
