/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 18:59:05 by sfranc            #+#    #+#             */
/*   Updated: 2017/09/14 15:56:26 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

int		ft_is_builtin(char *cmd)
{
	if (ft_strequ(cmd, CMD_ECHO) || ft_strequ(cmd, CMD_EXIT)\
			|| ft_strequ(cmd, CMD_ENV) || ft_strequ(cmd, CMD_SETENV)\
			|| ft_strequ(cmd, CMD_UNSETENV))
		return(1);
	return (0);
}

int		ft_launch_builtin(char **cmd)
{
	if (ft_strequ(*cmd, CMD_ECHO))
		return (ft_builtin_echo(cmd));
	if (ft_strequ(*cmd, CMD_ENV))
		return (ft_builtin_env(cmd));
	if (ft_strequ(*cmd, CMD_SETENV))
		return (ft_builtin_setenv(cmd));
	if (ft_strequ(*cmd, CMD_UNSETENV))
		return (ft_builtin_unsetenv(cmd));
	if (ft_strequ(*cmd, CMD_EXIT))
		ft_builtin_exit(cmd);
	return (0);
}
