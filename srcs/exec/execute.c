/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 11:01:55 by sfranc            #+#    #+#             */
/*   Updated: 2017/08/31 11:12:03 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

int		ft_execute_semi_list(t_ast *ast)
{
	ft_execute(ast->left);
	return (ft_execute(ast->right));
}

int		ft_execute_andif_list(t_ast *ast)
{
	if (ft_execute(ast->left) == EXIT_SUCCESS)
		return (ft_execute(ast->right));
	else
		return (EXIT_SUCCESS);
}

int		ft_execute_orif_list(t_ast *ast)
{
	if (ft_execute(ast->left) == EXIT_FAILURE)
		return (ft_execute(ast->right));
	else
		return (EXIT_SUCCESS);
}

int		ft_execute(t_ast *ast)
{
	int ret;

	if (!ast)
		return (EXIT_SUCCESS);

	if (ast->operator_type == SEMI)
		ret = ft_execute_semi_list(ast);
	else if (ast->operator_type == AND_IF)
		ret = ft_execute_andif_list(ast);
	else if (ast->operator_type == OR_IF)
		ret = ft_execute_orif_list(ast);
	else if (ast->node_type == WORD)
		ret = ft_launch_simple_cmd(ast);
	else
		ret = 99;
	return (ret);
}
