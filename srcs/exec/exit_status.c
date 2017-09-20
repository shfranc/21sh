/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 13:00:37 by sfranc            #+#    #+#             */
/*   Updated: 2017/09/20 15:03:18 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

int		ft_exit_status(int ret)
{
	if (WIFEXITED(ret))
		return (WEXITSTATUS(ret));
	else if (WIFSIGNALED(ret))
	{
		if ((WTERMSIG(ret)) == 6)
			ft_putendl_fd(STR_SIGABORT, 2);
		if ((WTERMSIG(ret)) == 10)
			ft_putendl_fd(STR_BUS_ERROR, 2);
		if ((WTERMSIG(ret)) == 11)
			ft_putendl_fd(STR_SEGFAULT, 2);
		return (WTERMSIG(ret));
	}
	else
		return (EXIT_FAILURE);
}
