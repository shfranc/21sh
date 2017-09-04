/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 12:03:10 by sfranc            #+#    #+#             */
/*   Updated: 2017/09/04 18:17:58 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

char	**ft_cmd_into_tab(t_ast *ast)
{
	char 	**cmd;
	t_token	*tmp;

	cmd = NULL;
	// expansion + quote removing
	tmp = ast->token;
	while (tmp && tmp->token_type == WORD)
	{
		ft_addtotab(&cmd, tmp->str);
		tmp = tmp->next;
	}

	// redirection a traiter avant de mettre la commande en tab.
	/*	while (tmp && tmp->token_type != WORD)
		{
		tmp = tmp->next;
		}
		if (tmp && tmp->prev && tmp->prev->token_type == REDIRECT && tmp->token_type == WORD)
		tmp = tmp->next;


		while (tmp && tmp->token_type == WORD)
		{
		ft_addtotab(&cmd, tmp->str);
		tmp = tmp->next;
		}*/
	return (cmd);
}

int		ft_fork(char *path, char **cmd)
{
	pid_t	pid;
	int		status;
	int 	ret_cmd;
	int		sauv_stdout;
	int		sauv_stderr;
	int		redirect;

	sauv_stdout = dup(STDOUT_FILENO);
	sauv_stderr = dup(STDERR_FILENO);
	ft_putstr("fd copie de std out: ");
	ft_putnbr_endl(sauv_stdout);
	ft_putstr("fd copie de std err: ");
	ft_putnbr_endl(sauv_stderr);
	redirect = open("coco", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	ft_putstr("fd du fichier de redir: ");
	ft_putnbr_endl(redirect);

	if ((pid = fork()) == -1)
		ft_exit("21sh: fork: fork failed, no child created", 1); // utiliser errno ??
	
	if (pid == 0)
	{
		ft_putstr("stdout is now: ");
		ft_putnbr_endl(dup2(redirect, STDOUT_FILENO));
		ft_putstr("stderr is now: ");
		ft_putnbr_endl(dup2(redirect, STDERR_FILENO));
		if ((status = execve(path, cmd, g_env)) == -1)
			ft_exit("21sh: execve: failed to execute the command", 1);
	}
	else
	{
		ft_putstr("stdout is now: ");
		ft_putnbr_endl(dup2(STDOUT_FILENO, sauv_stdout));
		ft_putstr("stderr is now: ");
		ft_putnbr_endl(dup2(STDERR_FILENO, sauv_stderr));
		close(redirect);
		close(sauv_stdout);
		close(sauv_stderr);
		wait(&status);
	}
	ret_cmd = WEXITSTATUS(status);
	return (ret_cmd);
}

int		ft_launch_simple_cmd(t_ast *ast)
{
	char	*path;
	char	**cmd;
	int		ret_cmd;

	// redirection a sauvegarder + creer les fichiers si besoin
	cmd = ft_cmd_into_tab(ast);
	if ((ret_cmd = ft_get_path(cmd[0], &path)) == PATH_OK)
	{
		ft_putstr(GREEN);
		ft_putstr(path);
		ft_putendl(RESET);
		ft_putendl("_____________________________________");

		ret_cmd = ft_fork(path, cmd);
		
		ft_putendl("_____________________________________");
		
		free(path);
	}
	ft_freetab(&cmd);
	return (ret_cmd);
}
