/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 12:08:12 by sfranc            #+#    #+#             */
/*   Updated: 2017/09/21 14:44:37 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

int		ft_builtin_history(char **cmd)
{
	int len;
	int	i;

	(void)cmd;
	if (!g_shell->history)
		ft_putendl(STR_HIST_EMPTY);
	else
	{
		len = ft_tablen(g_shell->history);
		i = 0;
		while (i < len)
		{
			ft_putnbr(i + 1);
			ft_putstr("\t");
			ft_putendl(g_shell->history[i]);
			i++;
		}
	}
	return (EXIT_SUCCESS);
}
