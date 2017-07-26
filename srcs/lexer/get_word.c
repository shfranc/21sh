/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/26 17:51:10 by sfranc            #+#    #+#             */
/*   Updated: 2017/07/26 17:56:24 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

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
	int		flags;

	flags = 0;
	len = 0;
	while (*(line + len) && !ft_part_operator(*(line + len)) && !ft_isspace(*(line + len)))
	{
		if (*(line + len) == '\\')
		{
			len++;
			flags |= ESCAPE;
		}
//		printbit(flags);
		if (!flags && *(line + len) == '"')
		{
			flags |= DQUOTES;
			len += ft_goto_next_quote_withescape(line + len, *(line + len));
			if (*(line + len) == '"')
			{
				flags ^= DQUOTES;
				len++;
			}
		}
		else if (!flags && *(line + len) == '\'')
		{
			flags |= SQUOTES;
			len += ft_goto_next_quote(line + len, *(line + len));
			if (*(line + len) == '\'')
			{
				flags ^= SQUOTES;
				len++;
			}
		}
		else
		{
			if (*(line + len) != '\n')
				flags = (flags & ESCAPE) ? flags ^ ESCAPE: 0;
			len++;
		}
	}
	tmp = ft_strsub(line, 0, len);
	token = ft_newtoken(tmp, "WORD");
	token->flags = flags;
	ft_addtoken(lexer, token);
	free(tmp);
	return (len);
}
