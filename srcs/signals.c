/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 17:36:22 by sfranc            #+#    #+#             */
/*   Updated: 2017/09/27 17:44:29 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

static void	ft_sigint_handler(int sig)
{
	write(1, "\n", 1);
	(void)sig;
	g_shell->ret_cmd = EXIT_FAILURE;
	g_shell->sigint = 1;
}

static void	ft_void_handler(int sig)
{
	(void)sig;
}

void		ft_catch_signals(int exec)
{
	signal(SIGTERM, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	if (!exec)
		signal(SIGINT, ft_sigint_handler);
	else
		signal(SIGINT, ft_void_handler);
}
