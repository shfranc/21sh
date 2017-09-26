/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 12:49:58 by sfranc            #+#    #+#             */
/*   Updated: 2017/09/26 12:57:21 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

#include <stdio.h>

void	ft_signals_handler(int sig)
{
	printf("signal:n*%d\n", sig);
}

void	ft_sigint_handler(int sig)
{
	(void)sig;
	g_shell->ret_cmd = EXIT_FAILURE;
	write(1, "\n", 1);
	g_shell->sigint = 1;
	g_shell->input.len = ft_display_prompt();
	ft_clear_screen(&g_shell->input);
}

int		ft_catch_signals()
{
	signal(SIGTERM, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);


	
	signal(SIGINT, ft_sigint_handler);
	
	return (1);
}

static void	ft_run_cmd(char **argv, t_lexer *lexer)
{
	t_ast	*ast;

	ast = ft_create_ast(&lexer->first);
	if (ft_strequ(argv[1], "--ast") || ft_strequ(argv[2], "--ast"))
		ft_print_ast(ast, "root", 0);
	g_shell->ret_cmd = ft_execute(ast);
	ft_del_ast(&ast);
}

int			main(int argc, char **argv, char **environ)
{
	char	*line;
	t_lexer	*lexer;
	int		ret_cmd;

	(void)argc;
	ft_catch_signals();
	g_shell = ft_init(environ);
	while (1)
	{
		g_shell->sigint = 0;
		ft_read_line(&line, ft_display_prompt(), DEFAULT);
		ft_tokenize(&lexer, line);
		ret_cmd = ft_parser(lexer);	
		if (ft_strequ(argv[1], "--lexer"))
			ft_printlexer(lexer->first, lexer->nbr_token);
		if (ret_cmd == PARSER_SUCCESS)
			ft_run_cmd(argv, lexer);
		else
			g_shell->ret_cmd = ret_cmd;
		ft_dellexer(&lexer);
		ft_strdel(&line);
	}
	return (0);
}

/*
 ** SIGNALS
 **  1 SIGHUP	-- hangup == exit
 **  2 SIGINT	-- RAS --> ctrl + C
 **  3 SIGQUIT	-- RAS
 **  4 SIGILL	-- illegal hardware instruction == exit
 **  5 SIGTRAP	-- trace trap == exit
 **  6 SIGABRT	-- abort == exit
 **  7 SIGEMT	-- EMT (Emulator trap) instruction == exit
 **  8 -- floating point excepton == exit
 **  9 -- killed == exit
 ** 10 SIGBUS	-- bus error == exit
 ** 11 -- segmentation fault == exit
 ** 12 -- invalid system call == exit
 ** 13 -- exit sans \n ni message...
 ** 14 -- alarm ==  exit
 ** 15 -- RAS
 ** 16 -- RAS
 ** 17 -- suspended (signal) arriere plan ? fg le ramene (+ continued) mais exit tout de suite apres
 ** 18 -- RAS
 ** 19 -- RAS
 ** 20 -- RAS
 ** 21 -- RAS
 ** 22 -- RAS
 ** 23 -- RAS
 ** 24 -- cpu limit exceeded == exit
 ** 25 -- file size limit exceeded == exit
 ** 26 -- virtual time alarm == exit
 ** 27 -- profile signal == exit
 ** 28 -- RAS
 ** 29 -- RAS
 ** 30 -- user-defined signal 1 == exit
 ** 31 -- user-defined signal 2 == exit
 */

