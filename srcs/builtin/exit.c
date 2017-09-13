/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 16:02:43 by sfranc            #+#    #+#             */
/*   Updated: 2017/09/13 16:32:10 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

void	ft_builtin_exit(char **cmd)
{
	ft_putendl_fd(CMD_EXIT, 2);
	if (!cmd[1])
		exit(g_ret_cmd);
	else if (!ft_isnumber(cmd[1]))
	{
		ft_put_cmd_error(CMD_EXIT, STR_NUM);
		exit (EXIT_ERROR);
	}
	else if (cmd[2])
		ft_put_cmd_error(CMD_EXIT, STR_TOO_MANY);
	else
		exit(ft_atoi(cmd[1]));
}

