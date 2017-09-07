/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_removal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 17:11:04 by sfranc            #+#    #+#             */
/*   Updated: 2017/09/07 18:05:13 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

void	ft_remove_quoting(t_token *token)
{
	t_token *tmp;
	char	*new;

	tmp = token;
	while (tmp)
	{
		if (tmp->token_type == WORD)
		{
			new = ft_remove_quotes(tmp->str);
			free(tmp->str);
			tmp->str = new;
		}
		if (tmp->token_type == DLESS)
			ft_putendl("enlever les quotes dans le heredoc");
		tmp = tmp->next;
	}
}
