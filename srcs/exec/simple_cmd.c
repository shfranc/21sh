/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 12:03:10 by sfranc            #+#    #+#             */
/*   Updated: 2017/09/06 16:21:21 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

char	**ft_cmd_into_tab(t_ast *ast)
{
	char 	**cmd;
	t_token	*tmp;

	cmd = NULL;
	tmp = ast->token;
	while (tmp)
	{
		if (tmp->token_type == IO_NUMBER)
			tmp = tmp->next;
		else if (tmp->token_type == REDIRECT)
			tmp = tmp->next->next;
		else
		{
			ft_addtotab(&cmd, tmp->str);
			tmp = tmp->next;
		}
	}
	return (cmd);
}

int		ft_fork(char *path, char **cmd)
{
	pid_t	pid;
	int		status;
	int 	ret_cmd;

	if ((pid = fork()) == -1)
		ft_exit("21sh: fork: fork failed, no child created", 1);
	if (pid == 0)
	{
		if ((status = execve(path, cmd, g_env)) == -1)
			ft_exit("21sh: execve: failed to execute the command", 1);
	}
	else
		wait(&status);
	ret_cmd = WEXITSTATUS(status);
	return (ret_cmd);
}

int		ft_launch_simple_cmd(t_ast *ast)
{
	char	*path;
	char	**cmd;
	int		ret_cmd;
	int		save[3];

	ft_save_std_fd(save);
	if (ft_init_redirection(ast) != REDIR_OK)
	{
		ft_restore_std_fd(ast, save);
		return (REDIR_ERROR);
	}
	if ((cmd = ft_cmd_into_tab(ast)))
		ret_cmd = ft_get_path(cmd[0], &path);
	else
	{
		ft_restore_std_fd(ast, save);
		return (EXIT_SUCCESS);
	}
	if (ret_cmd == PATH_OK)
	{
		ft_putstr(GREEN);
		ft_putendl(path);
		ft_puttab(cmd);
		ft_putendl(RESET);

		ft_putendl("_____________________________________");

		ret_cmd = ft_fork(path, cmd);

		ft_putendl("_____________________________________");

		free(path);
	}

	ft_restore_std_fd(ast, save);
	ft_freetab(&cmd);
	return (ret_cmd);
}
