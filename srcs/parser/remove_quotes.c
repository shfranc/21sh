/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 11:48:41 by sfranc            #+#    #+#             */
/*   Updated: 2017/10/04 15:18:24 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

static char	*ft_remove_escape_withindquotes(char *str)
{
	if (*str == '\\')
	{
		if (*(str + 1) && (*(str + 1) == '"' || *(str + 1) == '$'\
					|| *(str + 1) == '\\' || *(str + 1) == '\n'))
			str++;
		if (*str == '\n')
		{
			if (*(str + 1) == '"')
				str += 2;
			else
				str++;
		}
	}
	return (str);
}

static int	ft_remove_escape(char **str)
{
	int escape;

	escape = 0;
	if (**str == '\\')
	{
		(*str)++;
		if (**str == '\n')
			(*str)++;
		else
			escape = ESCAPE;
	}
	return (escape);
}

static char	*ft_remove_squotes(char *new, char **str)
{
	(*str)++;
	while (**str && **str != '\'')
	{
		new = ft_charappend(new, **str);
		(*str)++;
	}
	(*str)++;
	return (new);
}

static char	*ft_remove_dquotes(char *new, char **str)
{
	(*str)++;
	while (**str && **str != '"')
	{
		*str = ft_remove_escape_withindquotes(*str);
		new = ft_charappend(new, **str);
		(*str)++;
	}
	(*str)++;
	return (new);
}

char		*ft_remove_quotes(char *str)
{
	char	*new;
	int		escape;

	new = NULL;
	while (*str)
	{
		escape = ft_remove_escape(&str);
		if (!escape && *str == '"')
			new = ft_remove_dquotes(new, &str);
		else if (!escape && *str == '\'')
			new = ft_remove_squotes(new, &str);
		else
		{
			if (*str != '\\')
			{
				new = ft_charappend(new, *str);
				str++;
				escape = (escape & ESCAPE) ? escape ^ ESCAPE : 0;
			}
		}
	}
	if (!new)
		new = ft_strdup("");
	return (new);
}
