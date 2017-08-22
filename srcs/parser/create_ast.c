/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 11:38:13 by sfranc            #+#    #+#             */
/*   Updated: 2017/08/22 18:25:08 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

/*
** == Grammar (BNF form) ==
** compound_command:	list ((SEMI) list)*
** list: 				pipeline ((AND_IF | OR_IF) pipeline)*
** pipeline: 			simple_command ((PIPE) simple_command)*
** simple_command:		(WORD)+ (REDIRECT WORD)*
*/

t_ast	*ft_create_leaf(t_token **token, int delim)
{
	t_ast	*new;
	t_token	*tmp;

	if ((*token)->token_type == NEWLINE)
		return (NULL);
	new = ft_memalloc(sizeof(t_ast));
	new->parent = NULL;
	new->left = NULL;
	new->right = NULL;
	new->node_type = (*token)->token_type;
	
	new->token = *token;
	tmp = (*token)->next;

	while (tmp->next && tmp->token_type != delim)
		tmp = tmp->next;

	tmp->prev->next = NULL;
	tmp->prev = NULL;
	*token = tmp;

	return (new);
}

void	ft_create_node(t_ast *left, t_ast *node, t_ast *right)
{
	node->left = left;
	node->right = right;
	left->parent = node;
	right->parent = node;
}

/*t_ast	*ft_create_pipeline(t_token *token)
{

	return (ast);
}

t_ast	*ft_create_list(t_token *token)
{
	t_ast *node;

	ft_create_pipeline(&token);


	return (node);
}*/

void	ft_print_node(t_ast *ast, int node)
{
	t_token *tmp;

	ft_putstr(BYELLOW"** NODE ");
	ft_putnbr(node);
	ft_putendl(RESET);
	tmp = ast->token;
	while (tmp)
	{
		ft_putstr(tmp->str);
		ft_putstr(" ");
		tmp = tmp->next;
	}
	ft_putendl(BYELLOW"\n***********"RESET);
}

void	ft_print_ast(t_ast *ast)
{
	t_ast *tmp;
	int lvl;

	lvl = 1;
	tmp = ast;
	
	ft_putendl(GREEN"___left___"RESET);
	while (tmp->left)
	{
		tmp = tmp->left;
		lvl++;
	}	
	while (tmp->parent)
	{
		ft_print_node(tmp, lvl);
		tmp = tmp->parent;
		lvl--;
	}

	ft_putendl(GREEN"___root___"RESET);
	ft_print_node(ast, lvl++);

	ft_putendl(GREEN"___right___"RESET);
	tmp = tmp->right;
	while (tmp)
	{
		ft_print_node(tmp, lvl);
		tmp = tmp->right;
		lvl++;
	}
}

t_ast	*ft_create_ast(t_token **token)
{
	t_ast	*left;
	t_ast	*ast;

	left = ft_create_leaf(token, OPERATOR);
	while ((*token)->token_type != SEMI)
	{
		ast = ft_create_leaf(token, WORD);
		ft_create_node(left, ast, ft_create_leaf(token));
	}
	

	return (ast);
}

