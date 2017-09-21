/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 14:21:40 by sfranc            #+#    #+#             */
/*   Updated: 2017/09/21 15:01:57 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

void	ft_history_back(t_input *input)
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

void	ft_history_forth(t_input *input)
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
