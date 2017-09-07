/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 18:03:31 by sfranc            #+#    #+#             */
/*   Updated: 2017/09/07 19:50:52 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

static int	ft_dollar_isquoted(char *begin, char *dollar)
{
	char	*before;

	if (dollar != begin && *(dollar - 1) == '\\')
		return (1);
	before = begin;
	while (*before && before < dollar)
	{
		if (*before == '\'' && (before - 1) && *(before - 1) != '\\')
		{
			before = before + ft_goto_next_quote(before, *before);
			if (before > dollar)
				return (1);
		}
		else if (*before == '"' && (before - 1) && *(before - 1) != '\\')
		{
			before = before + ft_goto_next_quote_withescape(before, *before);
			if (before > dollar)
				return (1);
		}
		before++;
	}
	return (0);
}

// ~ expansion : ne remplace que le 1er ~ si pas de ~ a la suite. (~~ n'est pas expandu)
// PATH:expand tout du long

void	ft_expand(t_token *token)
{
	t_token *tmp;
	char	*dollar;

	tmp = token;
	while (tmp)
	{
		if (tmp->token_type == WORD)
		{
			if ((dollar = ft_strchr(tmp->str, '$'))\
					&& !ft_dollar_isquoted(tmp->str, dollar))
				ft_putendl("replace $");
			else
				ft_putendl("ne rien faire");
		}
		tmp = tmp->next;
	}
}
