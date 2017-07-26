/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/20 17:15:55 by sfranc            #+#    #+#             */
/*   Updated: 2017/07/26 13:12:40 by sfranc           ###   ########.fr       */
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

int		ft_aggreg_fetch_dash(t_lexer *lexer, char *line)
{
	(void)lexer;
	ft_putstr(line);
	return (0);
}

void	ft_init_operator(char operator[15][5])
{
	if (operator[14][0] == '>')
		return ;
	ft_memmove(operator[0], ";;", 3);
	ft_memmove(operator[1], ";", 2);
	ft_memmove(operator[2], "&&", 3);
	ft_memmove(operator[3], "&", 2);
	ft_memmove(operator[4], "||", 3);
	ft_memmove(operator[5], "|", 2);
	ft_memmove(operator[6], "<<-", 4);
	ft_memmove(operator[7], "<<", 3);
	ft_memmove(operator[8], "<&", 3);
	ft_memmove(operator[9], "<>", 3);
	ft_memmove(operator[10], "<", 2);
	ft_memmove(operator[11], ">>", 3);
	ft_memmove(operator[12], ">&", 3);
	ft_memmove(operator[13], ">|", 3);
	ft_memmove(operator[14], ">", 2);
}

int		ft_get_operator(t_lexer *lexer, char *line)
{
	static char	operator[15][5];
	t_token		*token;
	int			len;
	int			i;

	ft_init_operator(operator);
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
				if (ft_strequ(operator[i], ">&") || ft_strequ(operator[i], "<&"))
				{
					if ((len = ft_aggreg_fetch_dash(lexer, line + ft_strlen(operator[i]))))
						return(len + ft_strlen(operator[i]));	// dans le cas de >& ou <& --> aller chercher le - si coller au prochain mot.
				}
			}
			return (ft_strlen(operator[i]));
		}
		++i;
	}
	return (0);
}

int		ft_goto_next_quote(char *line, char quote)
{
	int	len;

	len = 1;
	while (*(line + len) && *(line + len) != quote)
		len++;
	if (*(line + len) == quote)
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
	while (*(line + len) && !ft_part_operator(*(line + len)) && !ft_isspace(*(line + len)))
	{
		if (*(line + len) == '"')
		{
			quotes |= DQUOTES;
			len += ft_goto_next_quote(line + len, *(line + len));
			if (*(line + len - 1) == '"')
				quotes ^= DQUOTES;
		}
		else if (*(line + len) == '\'')
		{
			quotes |= SQUOTES;
			len += ft_goto_next_quote(line + len, *(line + len));
			if (*(line + len - 1) == '\'')
				quotes ^= SQUOTES;
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
