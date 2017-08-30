/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 11:01:55 by sfranc            #+#    #+#             */
/*   Updated: 2017/08/30 16:41:11 by sfranc           ###   ########.fr       */
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
		ret = 99;
	return (ret);
}
