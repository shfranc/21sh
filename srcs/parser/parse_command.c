/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/30 17:52:50 by sfranc            #+#    #+#             */
/*   Updated: 2017/07/30 19:46:23 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

void	ft_put_syntax_error(char *token)
{
	ft_putstr_fd(SHELL, 2);
	ft_putstr_fd(SYNTAX_ERR, 2);
	ft_putstr_fd(token, 2);
	ft_putendl_fd(END_ERR, 2);
}

int		ft_token_not_handled(t_lexer *lexer)
{
	if (tmp->token_type == DSEMI || tmp->token_type == AND\
			|| tmp->token_type == CLOBBER || tmp->token_type == LESS_GREAT\
			|| tmp->token_type == DLESS_DASH)
	{
		ft_put_syntax_error(tmp->str);
		return (1);
	}
	return (0);
}

int		ft_syntax_error(t_lexer *lexer)
{
	t_token *tmp;

	tmp = lexer->first;
	while (tmp)
	{
		tmp = tmp->next;
	}
	return (0);
}

void	ft_parser(t_lexer *lexer)
{
	if (ft_token_not_handled(lexer))
		return ;
	if (ft_or_and_list(lexer))
		return ;
}
