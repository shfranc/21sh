/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/20 17:15:55 by sfranc            #+#    #+#             */
/*   Updated: 2017/07/24 15:34:10 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

int		ft_part_operator(char c)
{
	return (c == ';' || c == '|' || c == '&' || c == '<' || c == '>'? 1 : 0);
}

int		ft_match_operator(char tmp, char c)
{
	if (tmp == c)
		return (1);
	else if (tmp ==  '<' && (c == '<' || c == '>' || c == '&')
}

int		ft_part_word(char c)
{
	if (ft_isprint(c) && !ft_isspace(c)\
			&& c != ';' && c != '|' && c != '&' && c != '<' && c != '>')
		return (1);
	return (0);
}

t_lexer	*ft_tokenize(char *line)
{
	t_lexer		*lexer;
	t_token		*token;
	char		*tmp;
	char		*type;

	lexer = ft_memalloc(sizeof(t_lexer));
	tmp = NULL;
	while (*line)
	{
		//test split spaces
		/*while (*line && *line != ' ' && *line != '\n')
		{
			tmp = ft_charappend(tmp, *line);
			line++;
		}*/
		if (*(line + 1) && ft_isamatch(*line, *(line + 1)))	
			tmp = ft_charappend(tmp, *line);
		else if (*(line + 1) && !ft_isamatch(*line, *(line + 1)))
		{
			delim token
				append new token
		}
		else if (!*(line + 1))
		{
			delim token
			END_OF_INPUT
		}

		if (tmp)
		{
			token = ft_newtoken(tmp, "TOKEN");
			ft_addtoken(lexer, token);
			ft_strdel(&tmp);
		}
		line++;
	}
	ft_printlexer(lexer);
	return (lexer);
}
