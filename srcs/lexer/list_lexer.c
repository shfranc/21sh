/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/20 17:30:17 by sfranc            #+#    #+#             */
/*   Updated: 2017/07/20 19:05:58 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

t_token	*ft_newtoken(char *str, char *token)
{
	t_token	*elem;

	elem = ft_memalloc(sizeof(t_token));
	elem->str = ft_strdup(str);
	elem->token = ft_strdup(token);
	elem->next = NULL;
	elem->prev = NULL;
	return (elem);
}

void	ft_addtoken(t_lexer *lexer, t_token *token)
{
	t_token	*temp;

	lexer->nbr_token++;
	if (lexer->first == NULL)
		lexer->first = token;
	else
	{
		temp = lexer->first;
		while (temp->next)
			temp = temp->next;
		temp->next = token;
		token->prev = temp;
		lexer->last = token;
	}
}

void	ft_printlexer(t_lexer *lexer)
{
	t_token	*temp;

	temp = lexer->first;
	ft_putstr(BBLUE);
	ft_putstr("--- NB TOKEN = ");
	ft_putnbr(lexer->nbr_token);
	ft_putendl(RESET);
	while (temp)
	{
		ft_putstr(temp->token);
		ft_putstr("\t\t");
		ft_putendl(temp->str);
		temp = temp->next;
	}
}

void	ft_dellexer(t_lexer *lexer)
{
	t_token	*temp;
	t_token	*prev;

	if (!lexer || !lexer->first)
		return ;
	temp = lexer->first;
	while (temp)
	{
		free(temp->str);
		free(temp->token);
		prev = temp;
		temp = temp->next;
		free(prev);
	}
	free(lexer);
	lexer = NULL;
}
