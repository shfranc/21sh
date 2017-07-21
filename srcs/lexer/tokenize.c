/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/20 17:15:55 by sfranc            #+#    #+#             */
/*   Updated: 2017/07/20 19:06:00 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

t_lexer	*ft_tokenize(char *line)
{
	t_lexer	*lexer;
	t_token	*token;

	lexer = ft_memalloc(sizeof(t_lexer));
	while (*line)
	{
		token = ft_newtoken(line, "TEST");
		ft_addtoken(lexer, token);
		line++;
	}
	ft_printlexer(lexer);
	return (lexer);
}
