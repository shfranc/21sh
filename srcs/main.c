/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 12:49:58 by sfranc            #+#    #+#             */
/*   Updated: 2017/07/30 18:32:39 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

/*void	ft_signals_handler(int sig)
{
	printf("signal:n*%d\n", sig);
}

int		ft_catch_signals()
{
	int i;

	i = 0;
	while (i++ <= 31)
		signal(i, SIG_IGN);
	return (1);
}*/

int		main(int argc, char **argv)
{
	char	*line;
	int		len_prompt;
	t_lexer	*lexer;

	(void)argc;
//	ft_catch_signals();

	while (1)
	{
		len_prompt = ft_display_prompt();
		ft_read_line(&line, len_prompt);
		lexer = ft_tokenize(line);
		if (ft_strequ(argv[1], "--lexer"))
			ft_printlexer(lexer);
		ft_parser(lexer);
		ft_dellexer(lexer);
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

