/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 12:03:10 by sfranc            #+#    #+#             */
/*   Updated: 2017/08/29 17:32:57 by sfranc           ###   ########.fr       */
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
*/

	while (tmp && tmp->token_type == WORD)
	{
		ft_addtotab(&cmd, tmp->str);
		tmp = tmp->next;
	}
	return (cmd);
}

int		ft_fork(char *path, char **cmd)
{
	pid_t	pid;
	int		status;
	int 	ret_cmd;

	if ((pid = fork()) == -1)
		ft_exit("21sh: fork: fork failed, no child created", 1); // utiliser errno ??
	if (pid == 0)
	{
		if ((status = execve(path, cmd, g_env)) == -1)
			ft_exit("21sh: execve: failed to execute the command", 1);
	}
	else
		wait(&status);
	ret_cmd = WEXITSTATUS(status);
	ft_putnbr_endl(ret_cmd);
	return (ret_cmd);
}

char	*ft_get_path(char *cmd)
{
	char **tmp;
	char *path;

	if (ft_strchr(cmd, "/"))
		return (ft_strdup(cmd));
	tmp = ft_get_env_variable("PATH");
	path = ft_strsplit(tmp, ':');

	if (path)
	{
	}
}

int		ft_launch_simple_cmd(t_ast *ast)
{
	char	*path;
	char	**cmd;
	int		ret_cmd;

	ret_cmd = 0;
	// redirection a sauvegarder + creer les fichiers si besoin
	cmd = ft_cmd_into_tab(ast);
	if (!cmd) // ne concerne pas le cas ou une redirection est seule.
		return (CMD_NOT_FOUND);
	else
	{
		ft_puttab(cmd);
		path = ft_get_path(cmd[0]);
		ret_cmd = ft_fork(path, cmd);
	}
	ft_freetab(&cmd);
	return (ret_cmd);
}
