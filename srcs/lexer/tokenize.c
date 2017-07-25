/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/20 17:15:55 by sfranc            #+#    #+#             */
/*   Updated: 2017/07/25 18:32:56 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

int		ft_part_operator(char c)
{
	return (c == ';' || c == '|' || c == '&' || c == '<' || c == '>' ? 1 : 0);
}

void	ft_get_io_number(t_lexer *lexer, char *line)
{
	if (lexer->last && ft_isnumber(lexer->last->str) &&\
			ft_strncmp(line - ft_strlen(lexer->last->str),\
				lexer->last->str, ft_strlen(lexer->last->str)) == 0)
	{
		free(lexer->last->token);
		lexer->last->token = ft_strdup("IO_NUMBER");
	}
}

int		ft_get_operator(t_lexer *lexer, char *line)
{
	static char	*operator[] = {";;", ";", "&&", "&", "||", "|",\
		"<<-", "<<", "<&", "<>", "<", ">>", ">&", ">|", ">"};
	int			i;
	t_token		*token;

	i = 0;
	while (operator[i])
	{
		if (ft_strncmp(line, operator[i], ft_strlen(operator[i])) == 0)
		{
			if (i < 6)
			{
				token = ft_newtoken(operator[i], "OPERATOR");
				ft_addtoken(lexer, token);
			}
			else
			{
				ft_get_io_number(lexer, line);
				token = ft_newtoken(operator[i], "REDIRECT");
				ft_addtoken(lexer, token);
			}
			if (ft_strequ(operator[i], ">&") || ft_strequ(operator[i], "<&"))
				;	// dans le cas de >& ou <& --> aller chercher le - si coller au prochain mot.
			return (ft_strlen(operator[i]));
		}
		++i;
	}
	return (0);
}

int		ft_goto_next_dquote(char *line)
{
	int	len;

	len = 1;
	while (*(line + len) && *(line + len) != '"')
		len++;
	if (*(line + len))
		len++;
	return (len);
}

int		ft_part_word(char c)
{
	if (ft_isprint(c) && !ft_isspace(c) && !ft_part_operator(c))
		return (1);
	return (0);
}

int		ft_get_word(t_lexer *lexer, char *line)
{
	t_token	*token;
	char	*tmp;
	int		len;
	int		quotes;

	quotes = 0;
	len = 0;
	while (*(line + len) && !ft_part_operator(*(line + len)) && *(line + len) != ' ' && *(line + len) != '\n')
	{
		if (*(line + len) == '"')
		{
			quotes = DQUOTES;
			len += ft_goto_next_dquote(line + len);
			if (*(line + len - 1) == '"')
				quotes = 0;
		}
		else
			len++;
	}
	tmp = ft_strsub(line, 0, len);
	token = ft_newtoken(tmp, "WORD");
	token->flags = quotes;
	ft_addtoken(lexer, token);
	free(tmp);
	return (len);
}

int		ft_get_newline(t_lexer *lexer)
{
	t_token	*token;

	token = ft_newtoken("<newline>", "NEWLINE");
	ft_addtoken(lexer, token);
	return (1);
}

t_lexer	*ft_tokenize(char *line)
{
	t_lexer		*lexer;
	char		*tmp;

	lexer = ft_memalloc(sizeof(t_lexer));
	tmp = NULL;
	while (*line)
	{
		//	ft_putstr(line);
		if (ft_part_operator(*line))
			line = line + ft_get_operator(lexer, line);
		else if (ft_part_word(*line))
			line = line + ft_get_word(lexer, line);
		else if (*line == '\n' && !*(line + 1))
			line = line + ft_get_newline(lexer);
		else
			line++;
	}
	return (lexer);
}
