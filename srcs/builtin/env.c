/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/29 16:29:24 by sfranc            #+#    #+#             */
/*   Updated: 2017/09/14 17:24:05 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

static int		ft_launch_cmd_env(char **cmd, int i, char **exec_env)
{
	char	**new_cmd;
	char	*path;
	int		ret_cmd;

	ret_cmd = EXIT_SUCCESS;
//	new_cmd = NULL;
	while (cmd[i])
		ft_addtotab(&new_cmd, cmd[i++]);
	if (!new_cmd)
	{
		ft_puttab(exec_env);
		ft_freetab(&exec_env);
		return (ret_cmd);
	}
	g_shell->env = exec_env;
	if (ft_is_builtin(new_cmd[0]))
		ret_cmd = ft_launch_builtin(new_cmd);
	else if ((ret_cmd = ft_get_path(new_cmd[0], &path)) == PATH_OK)
	{
		ret_cmd = ft_fork(path, new_cmd);
		free(path);
	}
	ft_freetab(&new_cmd);
	ft_freetab(&exec_env);
	return (ret_cmd);
}

int		ft_builtin_env(char **cmd)
{
	char	**sauv_env;
	char	**exec_env;
	int		ret_cmd;
	int		i;

	ret_cmd = EXIT_SUCCESS;
	if (!cmd[1] || ft_strequ(cmd[1], CMD_ENV))
		ft_puttab(g_shell->env);
	else
	{
		exec_env = 0;
		sauv_env = g_shell->env;
		i = 1;

		if (!ft_strequ(cmd[i], "-i"))
			exec_env = ft_tabdup(g_shell->env);
		else
			++i;
		while (cmd[i] && ft_strchr(cmd[i], '='))
			ft_modify_variable(&exec_env, cmd[i++]);
		ret_cmd = ft_launch_cmd_env(cmd, i, exec_env);		
		g_shell->env = sauv_env;
	}
	return (ret_cmd);
}

char	*ft_get_env_variable(char **env, char *var)
{
	char	*temp;
	char	*stop;
	int		i;

	if (!env)
		return (NULL);
	i = 0;
	while (*(env + i))
	{
		temp = ft_strsub(*(env + i), 0,\
				ft_strchr(*(env + i), '=') - *(env + i));
		if (ft_strequ(temp, var))
		{
			stop = ft_strchr(*(env + i), '=');
			free(temp);
			return (ft_strsub(*(env + i), stop - *(env + i) + 1,\
						ft_strlen(stop)));
		}
		i++;
		free(temp);
	}
	return (NULL);
}
