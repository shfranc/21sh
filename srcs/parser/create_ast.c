/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 11:38:13 by sfranc            #+#    #+#             */
/*   Updated: 2017/08/15 19:12:48 by sfranc           ###   ########.fr       */
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

t_ast	ft_create_leaf(t_token *token)
{
	t_ast	*new;

	new = ft_memalloc(sizeof(t_ast));
	new->parent = NULL;
	new->left = NULL;
	new->right = NULL;
	new->token = ft_memmove(token, sizeof(token)); // copier tous les mots dont les redirections
	return (new);
}

t_ast	ft_create_node(t_ast *left, t_ast *node, t_ast *right)
{
	node->left = left;
	node->right = right;
	left->parent = node;
	right->parent = node;
	return (node);
}

t_ast	ft_create_pipeline(t_token *token)
{

	return (ast);
}

t_ast	ft_create_list(t_token *token)
{
	t_ast *node

	ft_create_pipeline(&token);


	return (node);
}

t_ast	ft_create_ast(t_token *token)
{
	t_ast	*ast;

	ast = ft_create_list(&token);
	while (token == SEMI)

	return (ast)
}
