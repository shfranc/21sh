/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 11:38:13 by sfranc            #+#    #+#             */
/*   Updated: 2017/08/23 19:26:28 by sfranc           ###   ########.fr       */
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
	new->operator_type = (*token)->operator_type;

	new->token = *token;
	tmp = (*token)->next;

	while (tmp->next && tmp->token_type != delim)
		tmp = tmp->next;

	tmp->prev->next = NULL;
	tmp->prev = NULL;
	*token = tmp;

	return (new);
}

t_ast	*ft_create_node(t_ast *left, t_ast *node, t_ast *right)
{
	node->left = left;
	node->right = right;
	if (left)
		left->parent = node;
	if (right)
		right->parent = node;
	return (node);
}

void	ft_balance_ast(t_ast **root)
{
	t_ast	*old_root;
	t_ast	*new_root;
	t_ast	*move_leaf;

	old_root = *root;
	new_root = (*root)->right;
	move_leaf = (*root)->right->left;

	new_root->parent = NULL;
	new_root->left = old_root;
	old_root->parent = new_root;
	old_root->right = move_leaf;

	*root = new_root;
}


t_ast	*ft_create_pipeline(t_token **token)
{
	t_ast	*root;
	t_ast	*node;

	root = ft_create_leaf(token, OPERATOR);

	if ((*token)->operator_type == PIPE)
	{
		node = ft_create_leaf(token, WORD);
		root = ft_create_node(root, node, ft_create_pipeline(token));
	}

	return (root);
}

t_ast	*ft_create_list(t_token **token)
{
	t_ast	*root;
	t_ast	*node;

	root = ft_create_pipeline(token);

	if ((*token)->operator_type == AND_IF || (*token)->operator_type == OR_IF)
	{
		node = ft_create_leaf(token, WORD);
		root = ft_create_node(root, node, ft_create_list(token));
	}

	return (root);
}

int		ft_check_next_operator(t_token *token, int op)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->operator_type == op)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

t_ast	*ft_create_ast(t_token **token)
{
	t_ast	*root;
	t_ast	*node;
	t_ast	*right;

	root = ft_create_list(token);

	if ((*token)->operator_type == SEMI)
	{
		if (ft_check_next_operator(*token, SEMI))
		{
			while (ft_check_next_operator(*token, SEMI))
			{
				node = ft_create_leaf(token, WORD);
				right = ft_create_list(token);
				root = ft_create_node(root, node, right);
			}
		}
		else
		{
			node = ft_create_leaf(token, WORD);
			root = ft_create_node(root, node, ft_create_ast(token));
		}
	}

	return (root);
}

void	ft_padding(int padd)
{
	int	i;

	i = 0;
	while (++i < padd)
		write (1, "\t", 1);
}
void	ft_print_node(t_ast *ast, char *side, int lvl)
{
	t_token *tmp;

//	if (!ast)
//		return ;

//	i = 0;
//	while (++i < lvl)
//		write (1, "\t", 1);
	ft_padding(lvl);
	ft_putstr("** ");
	ft_putstr(side);
	ft_putnbr(lvl);
	ft_putendl(" **");
	
//	i = 0;
//	while (++i < lvl)
//		write (1, "\t", 1);


	ft_padding(lvl);
	tmp = ast->token;
	ft_putstr(BMAGENTA);
	while (tmp)
	{
		ft_putstr(tmp->str);
		ft_putstr(" ");
		tmp = tmp->next;
	}
	
	ft_putendl(RESET);
	ft_padding(lvl);
//	i = 0;
//	while (++i < lvl)
//		write (1, "\t", 1);
	ft_putendl("************");
}

void	ft_print_ast(t_ast *ast, char *side, int lvl)
{

	if (ast->left)
		ft_print_ast(ast->left, "left", ++lvl);
	else
		++lvl;

	ft_print_node(ast, side, lvl);

	if (ast->right)
		ft_print_ast(ast->right, "right", lvl--);
	else
		--lvl;

}
