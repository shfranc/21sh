/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 11:01:55 by sfranc            #+#    #+#             */
/*   Updated: 2017/08/29 11:57:18 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

int		ft_execute(t_ast *ast)
{
	int ret;

	if (!ast)
		return (0);

	if (ast->node_type == WORD)
		ret = ft_launch_simple_cmd(ast);
	else
		ret = CMD_NOT_FOUND;
	return (ret);
}
