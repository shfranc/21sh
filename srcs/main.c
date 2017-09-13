/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 12:49:58 by sfranc            #+#    #+#             */
/*   Updated: 2017/09/13 17:37:40 by sfranc           ###   ########.fr       */
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

t_shell	*ft_init(char **environ)
{
	t_shell	*shell;

	shell = ft_memalloc(sizeof(t_shell));
	shell->env = ft_tabdup(environ);
//	if (!shell->env)
//		shell->env = ft_basic_env;
	return (shell);
}


int		main(int argc, char **argv, char **environ)
{
	char	*line;
	int		len_prompt;
	t_lexer	*lexer;
//	int		parser_ret;
	t_ast	*ast;
	int		ret_cmd;

	(void)argc;
	g_shell = ft_init(environ);
	//	ft_catch_signals();
	//	lexer = NULL;
	while (1)
	{

		len_prompt = ft_display_prompt();
		ft_read_line(&line, len_prompt, 0);
		ft_tokenize(&lexer, line);
		ret_cmd = ft_parser(lexer);

		if (ft_strequ(argv[1], "--lexer"))
		{
			ft_printlexer(lexer->first, lexer->nbr_token);
			ft_putstr("\nPARSER RET: ");
			if (ret_cmd == PARSER_SUCCESS)
				ft_putendl(BGREEN"OK\n"RESET);
			else
				ft_putendl(BRED"Error\n"RESET);
		}
		if (ret_cmd == PARSER_SUCCESS)
		{
			ast = ft_create_ast(&lexer->first);
			if (ft_strequ(argv[1], "--ast") || ft_strequ(argv[2], "--ast"))
				ft_print_ast(ast, "root", 0);
			g_shell->ret_cmd = ft_execute(ast);
		}
		else
			g_shell->ret_cmd = ret_cmd;

		ft_putstr(BYELLOW"RET CMD: ");
		ft_putnbr(ret_cmd);
		ft_putendl(RESET);
		
		ft_dellexer(&lexer);
		ft_strdel(&line);
		ft_del_ast(&ast);
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

