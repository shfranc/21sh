/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 18:59:05 by sfranc            #+#    #+#             */
/*   Updated: 2017/09/13 18:05:21 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

int		ft_is_builtin(char *cmd)
{
	if (ft_strequ(cmd, CMD_ECHO) || ft_strequ(cmd, CMD_EXIT)\
			|| ft_strequ(cmd, CMD_ENV))
		return(1);
	return (0);
}

int		ft_launch_builtin(char **cmd)
{
	if (ft_strequ(*cmd, CMD_ECHO))
		return (ft_builtin_echo(cmd));
	if (ft_strequ(*cmd, CMD_ENV))
		return (ft_builtin_env(cmd));
	if (ft_strequ(*cmd, CMD_EXIT))
		ft_builtin_exit(cmd);
	return (0);
}
