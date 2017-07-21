/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/20 17:15:55 by sfranc            #+#    #+#             */
/*   Updated: 2017/07/21 15:58:33 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

void	ft_createtoken(t_lexer *lexer, char *tmp)
{
	t_token	*token;

	if (tmp && *tmp)
	{
		token = ft_newtoken(tmp, "TOKEN");
		ft_addtoken(lexer, token);
		ft_strdel(&tmp);
	}
}

t_lexer	*ft_tokenize(char *line)
{
	t_lexer	*lexer;
	t_token	*token;
	char	*tmp;

	lexer = ft_memalloc(sizeof(t_lexer));
	tmp = NULL;
	while (*line)
	{
		// test split spaces
		while (*line && *line != ' ' && *line != '\n')
		{
			tmp = ft_charappend(tmp, *line);
			line++;
		}
		//

		line++;
	}
	ft_printlexer(lexer);
	return (lexer);
}
