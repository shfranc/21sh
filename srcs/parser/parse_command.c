/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/30 17:52:50 by sfranc            #+#    #+#             */
/*   Updated: 2017/07/31 18:28:46 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

int		ft_incomplete_list(t_lexer *lexer)
{
	if (lexer->last->token_type == NEWLINE && lexer->nbr_token > 1\
			&& lexer->last->prev->operator_type == PIPE)
	{
		return (PIPE);
	}
	if (lexer->last->token_type == NEWLINE && lexer->nbr_token > 1\
			&& lexer->last->prev->operator_type == AND_IF)
	{
		return (AND_IF);
	}
	if (lexer->last->token_type == NEWLINE && lexer->nbr_token > 1\
			&& lexer->last->prev->operator_type == OR_IF)
	{
		return (OR_IF);
	}
	return (0);
}

t_token	*ft_is_heredoc(t_lexer *lexer)
{
	t_token	*tmp;

	tmp = lexer->first;
	while (tmp)
	{
		if (tmp->operator_type == DLESS && tmp->heredoc == NULL)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	ft_parser(t_lexer *lexer)
{
	int		list_type;
	t_token	*heredoc;

	if (ft_syntax_error(lexer))
		return ;
	
	if ((heredoc = ft_is_heredoc(lexer)))
		ft_read_again_heredoc(lexer, heredoc);

	if ((list_type = ft_incomplete_list(lexer)))
		ft_read_again_list(lexer, list_type);
		
	if (lexer->last->quoting)
		ft_read_again_quoting(lexer);
}
