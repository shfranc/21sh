/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 18:03:31 by sfranc            #+#    #+#             */
/*   Updated: 2017/09/08 16:48:15 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

static int	ft_dollar_isquoted(char *begin, char *dollar)
{
	int		escape;
	char	*before;

	ft_putendl("1");
	if (dollar != begin && *(dollar - 1) == '\\')
		return (1);
	before = begin;
	ft_putendl("2");
	while (*before && before < dollar)
	{
		ft_putendl("3");
		if (*before == '\\')
			escape = ESCAPE;
		if (!escape && *before == '\'')
		{
			before = before + ft_goto_next_quote(before, *before);
			ft_putendl(before);
			if (before > dollar)
				return (1);
		}
		else if (!escape && *before == '"')
		{
			ft_putendl("4");
			before = before + ft_goto_next_quote_withescape(before, *before);
			ft_putendl("5");
			ft_putendl(before);
			if (before > dollar)
				return (1);
		}
		else
		{
			before++;
			escape = (escape & ESCAPE) ? escape ^ ESCAPE : 0;
		}
	}
	return (0);
}

static void	ft_replace_dollar(char **str, char *dollar)
{
	char	*begin;
	char	*end;
	char	*var;
	char	*replace;
	char	*tmp;

	begin = ft_strsub(*str, 0, dollar - *str);
	ft_putstr("begin : ");
	ft_putendl(begin);
	var = NULL;
	++dollar;
	while (*dollar && ft_isalnum(*dollar))
		var = ft_charappend(var, *dollar++);

	ft_putstr("var a chercher : ");
	ft_putendl(var);

	replace = NULL;
	if (var)
		replace = ft_get_env_variable(g_env, var);

	ft_putstr("replace : ");
	ft_putendl(replace);

	end = ft_strsub(*str, ft_strlen(begin) + ft_strlen(var) + 1, ft_strlen(dollar));
	ft_putstr("end : ");
	ft_putendl(end);

	if (replace)
	{
		tmp = ft_strjoin3(begin, replace, end);
		free(*str);
		*str = tmp;
	}
	else
	{
		tmp = ft_strjoin(begin, end);
		free(*str);
		*str = tmp;
	}
}

// ~ expansion : ne remplace que le 1er ~ si pas de ~ a la suite. (~~ n'est pas expandu)
// PATH:expand tout du long

void		ft_expand(t_token *token)
{
	t_token *tmp;
	char	*dollar;

	tmp = token;
	while (tmp)
	{
		if (tmp->token_type == WORD)
		{
			while ((dollar = ft_strchr(tmp->str, '$'))\
					&& !ft_dollar_isquoted(tmp->str, dollar))
			{
				ft_putstr("replace $ :");
				ft_putendl(dollar);
				ft_replace_dollar(&tmp->str, dollar);
				ft_putstr("RESULT :");
				ft_putendl(tmp->str);
			}
		}
		tmp = tmp->next;
	}
}
