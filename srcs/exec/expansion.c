/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 18:03:31 by sfranc            #+#    #+#             */
/*   Updated: 2017/09/12 14:55:16 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

// ~ expansion : ne remplace que le 1er ~ si pas de ~ a la suite. (~~ n'est pas expandu)
// PATH:expand tout du long

static int	ft_is_quoted(char *str, char *c)
{
	int	escape;

	if ((c - 1) && *(c - 1) == '\\')
		return (1);
	escape = 0;
	while (str < c)
	{
		if (*str == '\\')
			escape = 1;
		if (!escape && *str == '"'\
				&& ((str = str + ft_goto_next_quote_withescape(str, *str) + 1) > c))
			return (1);
		else if (!escape && *str == '\''\
				&& ((str = str + ft_goto_next_quote(str, *str)) > c))
			return (1);
		else
		{
			str++;
			escape = 0;
		}
	}
	return (0);
}

char	*ft_tilde_expansion(char *str, char *tilde)
{
	char *home;
	char *exp;

	if (!(home = ft_get_env_variable(g_env, "HOME")))
		return (str);
	exp = ft_memalloc(ft_strlen(str) + ft_strlen(home));
	ft_memmove(exp, str, tilde - str);
	ft_memmove(exp + ft_strlen(exp), home, ft_strlen(home));
	ft_memmove(exp + ft_strlen(exp), tilde +  1, ft_strlen(tilde + 1));
	return (exp);
}


void		ft_expand(t_token *token)
{
	t_token *tmp;
	char	*tilde;

	tmp = token;
	while (tmp)
	{
		if (tmp->token_type == WORD)
		{
			while ((tilde = ft_strchr(tmp->str, '~'))\
					&& !ft_is_quoted(tmp->str, tilde))
				tmp->str = ft_tilde_expansion(tmp->str, tilde);
		}
		tmp = tmp->next;
	}
}
