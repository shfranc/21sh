/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/20 17:30:17 by sfranc            #+#    #+#             */
/*   Updated: 2017/07/31 19:16:07 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

t_token	*ft_newtoken(char *str, int token, int operator)
{
	t_token	*elem;

	elem = ft_memalloc(sizeof(t_token));
	elem->str = ft_strdup(str);
	elem->token_type = token;
	elem->operator_type = operator;
	elem->next = NULL;
	elem->prev = NULL;
	return (elem);
}

void	ft_addtoken(t_lexer *lexer, t_token *token)
{
	t_token	*temp;

	lexer->nbr_token++;
	if (lexer->first == NULL)
	{
		lexer->first = token;
		lexer->last = token;
	}
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

void	ft_del_lasttoken(t_lexer *lexer)
{
	t_token *suppr;

	suppr = lexer->last;
	if (lexer->last != lexer->first)
	{
		lexer->last = suppr->prev;
		suppr->prev->next = NULL;
	}
	else
	{
		lexer->first = NULL;
		lexer->last = NULL;
	}
	lexer->nbr_token--;
	free(suppr->str);
	free(suppr);
}

void	ft_dellexer(t_lexer **lexer)
{
	t_token	*temp;
	t_token	*prev;

	if (!*lexer || !(*lexer)->first)
		return ;
	temp = (*lexer)->first;
	while (temp)
	{
		free(temp->str);
		prev = temp;
		temp = temp->next;
		free(prev);
	}
	free(*lexer);
	*lexer = NULL;
}

/*
** DEBUG
*/

void	ft_reverseprint(t_lexer *lexer)
{
	t_token	*temp;

	temp = lexer->last;
	while(temp)
	{
		ft_putendl(temp->str);
		temp = temp->prev;
	}
}

void	ft_printlexer(t_lexer *lexer)
{
	static char	*operator[] = {"", "DSEMI", "SEMI", "AND_IF", "AND", "OR_IF", "PIPE", "DLESS_DASH", "DLESS", "LESS_AND", "LESS_GREAT", "LESS", "DGREAT", "GREAT_AND", "CLOBBER", "GREAT"};
	static char *token[] = {"WORD", "OPERATOR", "REDIRECT", "IO_NUMBER", "NEWLINE"};
	t_token	*temp;

	temp = lexer->first;
	ft_putstr("\n"BBLUE);
	ft_putstr("--- NB TOKEN = ");
	ft_putnbr(lexer->nbr_token);
	ft_putendl(RESET);
	while (temp)
	{
		ft_putstr(token[temp->token_type]);
		ft_putstr(" ");
		ft_putstr(operator[temp->operator_type]);
		if (ft_strlen(token[temp->token_type]) + 1 >= 8)
			ft_putstr("\t");
		else
			ft_putstr("\t\t");
		ft_putstr(temp->str);
		if (temp->quoting & DQUOTES)
			ft_putstr("\t// DQUOTE non fermée");
		if (temp->quoting & SQUOTES)
			ft_putstr("\t// SQUOTE non fermée");
		if (temp->quoting & ESCAPE)
			ft_putstr("\t// ESCAPE newline");
		ft_putchar('\n');
		temp = temp->next;
	}
	ft_putstr(BBLUE"-----------------"RESET"\n");
}
