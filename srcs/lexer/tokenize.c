/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/20 17:15:55 by sfranc            #+#    #+#             */
/*   Updated: 2017/07/25 13:13:43 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

int		ft_part_operator(char c)
{
	return (c == ';' || c == '|' || c == '&' || c == '<' || c == '>' ? 1 : 0);
}

int		ft_get_operator(t_lexer *lexer, char *line)
{
	static char	*ope_ctrl[] = {";;", ";", "&&", "&", "||", "|", "<<-", "<<", "<&", "<>", "<", ">>", ">&",">|", ">"};
	int			i;
	t_token				*token;

	i = 0;
	while (ope_ctrl[i])
	{
		if (ft_strncmp(line, ope_ctrl[i], ft_strlen(ope_ctrl[i])) == 0)
		{
			if (i < 6)
				token = ft_newtoken(ope_ctrl[i], "OPERATOR");
			else
				token = ft_newtoken(ope_ctrl[i], "REDIRECT");
			ft_addtoken(lexer, token);
			return (ft_strlen(ope_ctrl[i]));
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
	return (len);
}

int		ft_part_word(char c)
{
	if (ft_isprint(c) && !ft_isspace(c)\
			&& c != ';' && c != '|' && c != '&' && c != '<' && c != '>')
		return (1);
	return (0);
}

int		ft_get_word(t_lexer *lexer, char *line)
{
	t_token	*token;
	char	*tmp;
	int		len;
	
	len = 0;
	while (*(line + len) && !ft_part_operator(*(line + len)) && *(line + len) != ' ' && *(line + len) != '\n')
	{
		len++;
	}
	tmp = ft_strsub(line, 0, len);
	token = ft_newtoken(tmp, "WORD");
	ft_addtoken(lexer, token);
	free(tmp);
	return (len);
}

t_lexer	*ft_tokenize(char *line)
{
	t_lexer		*lexer;
//	t_token		*token;
	char		*tmp;

	lexer = ft_memalloc(sizeof(t_lexer));
	tmp = NULL;
	while (*line)
	{
		ft_putendl(line);
		if (ft_part_operator(*line))
			line = line + ft_get_operator(lexer, line);
		else if (ft_part_word(*line))
			line = line + ft_get_word(lexer, line);
		else
			line++;
	}
	ft_printlexer(lexer);
	return (lexer);
}
