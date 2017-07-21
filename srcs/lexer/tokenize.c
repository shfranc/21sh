/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/20 17:15:55 by sfranc            #+#    #+#             */
/*   Updated: 2017/07/21 16:57:14 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

void	ft_createtoken(t_lexer *lexer, char *tmp, char *type)
{
	t_token	*token;

	if (tmp && *tmp)
	{
		token = ft_newtoken(tmp, type);
		ft_addtoken(lexer, token);
		ft_strdel(&tmp);
	}
}

int		ft_part_operator(char *tmp, char c)
{
	if (!tmp)
		return (c == ';' || c == '|' || c == '&' || c == '<' || c == '>'? 1 : 0);
	else if (*tmp == c)
		return (2);
	else if (*tmp == '<' && (c == '&' || c == '>'))
		return (2);
	else if (*tmp == '>' && (c == '&' || c == '|'))
		return (2);
	//else if (ft_strequ(tmp, "<<") && c == '-')
	//	return (2);
	return (0);
}

int		ft_part_word(char c)
{
	if (ft_isprinpt(c) && !ft_isspace(c)\
			&& c != ';' && c != '|' && c != '&' && c != '<' && c != '>')
		return (1);
	return (0);
}

t_lexer	*ft_tokenize(char *line)
{
	t_lexer	*lexer;
	char	*tmp;

	lexer = ft_memalloc(sizeof(t_lexer));
	tmp = NULL;
	while (*line)
	{
		/*//test split spaces
		while (*line && *line != ' ' && *line != '\n')
		{
			tmp = ft_charappend(tmp, *line);
			line++;
		}*/
		if (!*(line + 1))
		{
			ft_createtoken(lexer, tmp, "UNDEFINED");
			ft_charappend(tmp, *line);
		}
		if (ft_part_operator(tmp, *line) == 2)
			ft_charappend(tmp, *line);
		if (*(line - 1) && ft_part_operator(tmp*(line - 1)) && !ft_part_operator(*line))
		{
			ft_createtoken(lexer, tmp, "OPERATOR");
			ft_charappend(tmp, *line);
		}
		if (*(line - 1) && !ft_part_operator(*(line - 1)) && ft_part_operator(*line))
		{
			ft_createtoken(lexer, tmp, "UNDEFINED");
			ft_charappend(tmp, *line);
		}
		if (*line == "\n")
		{
			ft_createtoken(lexer, tmp, "UNDEFINED");
			ft_charappend(tmp, *line);
		}
		if (*line == ' ')
			ft_createtoken(lexer, tmp, "UNDEFINED");
		if (ft_part_word(*line))
			ft_charappend(tmp, *line);

		line++;
	}
	ft_printlexer(lexer);
	return (lexer);
}
