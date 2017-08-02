/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 11:48:41 by sfranc            #+#    #+#             */
/*   Updated: 2017/08/02 19:37:55 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

/*void	ft_strmerge(char **origin, char *add)
{
	char *temp;

	if (!*origin)
		*origin = ft_strdup(add);
	else
	{
		temp = *origin;
		*origin = ft_strjoin(*origin, add);
		free(temp);
	}
}*/

char	*ft_remove_quotes(char *str)
{
	char	*new;
	int		escape;
	int		len;
	
	new = NULL;
	escape = 0;
	ft_putendl(str);
	while (*str)
	{
		ft_putendl("1");
		if (*str == '\\')
		{
			str++;
			escape |= ESCAPE;
		}
		if (!escape && *str == '"')
		{
			len = ft_goto_next_quote_withescape(str, *str);
			ft_strmerge(&new, ft_strsub(str, 1, len - 1));
		//	if (!new)
		//		new = ft_strsub(str, 1, len - 1);
		//	else
		//		new = ft_strjoin(new, ft_strsub(str, 1, len - 1));
			str += len;
		}
	//	else if (!escape && *str == '\'')
	//		;
		else
		{
			new = ft_charappend(new, *str);
			str++;
			escape = (escape & ESCAPE) ? escape ^ ESCAPE: 0;
		}

	}
	ft_putendl(new);
	return (new);
}

/*
int		ft_get_word(t_lexer *lexer, char *line)
{
	t_token	*token;
	char	*tmp;
	int		len;
	int		quoting;

	quoting = 0;
	len = 0;
	while (*(line + len) && !ft_part_operator(*(line + len))\
			&& !ft_isspace(*(line + len)))
	{
		if (*(line + len) == '\\')
		{
			len++;
			quoting |= ESCAPE;
		}
//		printbit(quoting);
		if (!quoting && *(line + len) == '"')
		{
			quoting |= DQUOTES;
			len += ft_goto_next_quote_withescape(line + len, *(line + len));
			if (*(line + len) == '"')
			{
				quoting ^= DQUOTES;
				len++;
			}
		}
		else if (!quoting && *(line + len) == '\'')
		{
			quoting |= SQUOTES;
			len += ft_goto_next_quote(line + len, *(line + len));
			if (*(line + len) == '\'')
			{
				quoting ^= SQUOTES;
				len++;
			}
		}
		else
		{
			if (*(line + len) != '\n')
				quoting = (quoting & ESCAPE) ? quoting ^ ESCAPE: 0;
			len++;
		}
	}
	tmp = ft_strsub(line, 0, len);
	token = ft_newtoken(tmp, WORD, NONE);
	token->quoting = quoting;
	ft_addtoken(lexer, token);
	free(tmp);
	return (len);
}*/
