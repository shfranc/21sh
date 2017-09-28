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

static void	ft_sigwinch_handler(int sig)
{
	char	*save_line;
	char	*save_tmp;
	int		save_prompt;
	int		save_index;

	(void)sig;
	if (g_shell->input.line)
		save_line = ft_strdup(g_shell->input.line);
	else
		save_line = NULL;
	if (g_shell->input.tmp)
		save_tmp = ft_strdup(g_shell->input.tmp);
	else
		save_tmp = NULL;
	save_prompt = g_shell->input.origin_prompt;
	save_index = g_shell->input.y * (g_shell->input.width + 1) + g_shell->input.x - g_shell->input.prompt;
	ft_init_input_struct(&g_shell->input, save_prompt);
	if (save_line)
		ft_memmove(g_shell->input.line, save_line, ft_strlen(save_line));
	if (save_tmp)
		ft_memmove(g_shell->input.tmp, save_tmp, ft_strlen(save_tmp));
	g_shell->input.len = ft_strlen(g_shell->input.line);
	g_shell->input.x = (save_index + g_shell->input.prompt) % (g_shell->input.width + 1);
	g_shell->input.y = (save_index + g_shell->input.prompt) / (g_shell->input.width + 1);
}

void		ft_catch_signals(int exec)
{
	signal(SIGTERM, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGWINCH, ft_sigwinch_handler);
	if (!exec)
		signal(SIGINT, ft_sigint_handler);
	else
		signal(SIGINT, ft_void_handler);
}
