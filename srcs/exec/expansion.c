/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 18:03:31 by sfranc            #+#    #+#             */
/*   Updated: 2017/09/12 17:51:31 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

// ~ expansion : ne remplace que le 1er ~ si pas de ~ a la suite. (~~ n'est pas expandu)
// PATH:expand tout du long

static int	ft_is_quoted(char *str, char *c)
{
	int	escape;

	escape = 0;
	while (str < c)
	{
		if (*str == '\\')
			escape = 1;
		if (*str == '\\' && (str + 1) && *(str + 1) == *c)
			return (1);
		if (!escape && *str == '"'\
				&& ((str = str\
						+ ft_goto_next_quote_withescape(str, *str) + 1) > c))
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

static int	ft_tilde_expansion(char **str, char *tilde)
{
	char *home;
	char *exp;

	if (!(home = ft_get_env_variable(g_env, "HOME")))
		return (0);	
	exp = ft_memalloc(ft_strlen(*str) + ft_strlen(home));
	ft_memmove(exp, *str, tilde - *str);
	ft_memmove(exp + ft_strlen(exp), home, ft_strlen(home));
	ft_memmove(exp + ft_strlen(exp), tilde +  1, ft_strlen(tilde + 1));
	free(home);
	free(*str);
	*str = exp;
	return (1);
}

static void	ft_var_expansion(char **str, char *dollar)
{
	char	*key;
	char	*value;
	char	*exp;
	char	*tmp;

	(void)str;
	tmp = dollar + 1;
	key = NULL;
	while (*tmp && (ft_isalnum(*tmp) || *tmp == '_'))
		key = ft_charappend(key, *tmp++);
	value = ft_get_env_variable(g_env, key);
	if (value)
		exp = ft_memalloc(ft_strlen(*str) - ft_strlen(key) + ft_strlen(value));
	else
		exp = ft_memalloc(ft_strlen(*str) - ft_strlen(key));

	ft_memmove(exp, *str, dollar - *str);
	if (value)
		ft_memmove(exp + ft_strlen(exp), value, ft_strlen(value));
	ft_memmove(exp + ft_strlen(exp), dollar +  ft_strlen(key) + 1, ft_strlen(dollar + ft_strlen(key) + 1));
	free(key);
	free(value);
	free(*str);
	*str = exp;
}

void		ft_expand(t_token *token)
{
	t_token *tmp;
	char	*tilde;
	char	*dollar;

	tmp = token;
	while (tmp)
	{
		if (tmp->token_type == WORD)
		{
			while ((tilde = ft_strchr(tmp->str, '~'))\
					&& !ft_is_quoted(tmp->str, tilde))
			{
				if (!(ft_tilde_expansion(&tmp->str, tilde)))
					break ;
			}
			while ((dollar = ft_strchr(tmp->str, '$'))\
					&& !ft_is_quoted(tmp->str, tilde))
			{
				if (ft_strequ(dollar, "$"))
					break ;
				ft_var_expansion(&tmp->str, dollar);
			}
		}
		tmp = tmp->next;
	}
}
