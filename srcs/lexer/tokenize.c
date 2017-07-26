/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/20 17:15:55 by sfranc            #+#    #+#             */
/*   Updated: 2017/07/26 18:08:03 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

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
