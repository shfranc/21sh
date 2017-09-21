/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 14:21:40 by sfranc            #+#    #+#             */
/*   Updated: 2017/09/21 16:32:25 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

void		ft_history_back(t_input *input)
{
	if (!g_shell->history)
		tputs(tgetstr("bl", NULL), 1, &ft_intputchar);
	else
	{
		if (g_shell->histo_index > 0)
		{
			ft_clear_screen(input);
			ft_insertchar(g_shell->history[g_shell->histo_index - 1], input);
			g_shell->histo_index--;
		}
		else
			tputs(tgetstr("bl", NULL), 1, &ft_intputchar);
	}
}

void		ft_history_forth(t_input *input)
{
	if (!g_shell->history)
		tputs(tgetstr("bl", NULL), 1, &ft_intputchar);
	else
	{
		if (g_shell->histo_index < ft_tablen(g_shell->history) - 1)
		{
			ft_clear_screen(input);
			g_shell->histo_index++;
			ft_insertchar(g_shell->history[g_shell->histo_index], input);
		}
		else
			tputs(tgetstr("bl", NULL), 1, &ft_intputchar);
	}
}

static char	*ft_search_in_history(char *line)
{
	char	*tmp;
	int		len;

	tmp = ft_strsub(line, 0, ft_strlen(line) - 1);
	if (!*tmp)
		return (NULL);
	if (!g_shell->history)
		return (NULL);
	len = ft_tablen(g_shell->history);
	while (len--)
	{
		if (ft_strstr(g_shell->history[len], tmp))
			return (ft_strdup(g_shell->history[len]));
	}
	return (NULL);
}

void		ft_history_search(t_input *input)
{
	char	*line;
	char	*tmp;

	ft_clear_screen(input);
	g_shell->ret_cmd = EXIT_SUCCESS;
	write(1, "\n", 1);
	ft_read_line(&line, write(1, HISTO_PROMPT, ft_strlen(HISTO_PROMPT)), 3);	
	if (!(tmp = ft_search_in_history(line)))
	{
		ft_putendl("No match found...");
		tmp = ft_strsub(line, 0, ft_strlen(line) - 1);
	}
	ft_display_prompt();
	ft_insertchar(tmp, input);
	free(tmp);
}
