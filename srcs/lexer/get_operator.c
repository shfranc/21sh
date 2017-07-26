/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_operator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/26 17:50:55 by sfranc            #+#    #+#             */
/*   Updated: 2017/07/26 18:01:09 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

int			ft_part_operator(char c)
{
	return (c == ';' || c == '|' || c == '&' || c == '<' || c == '>' ? 1 : 0);
}

static void	ft_init_operator(char operator[15][5])
{
	if (operator[14][0] == '>')
		return ;
	ft_memmove(operator[0], ";;", 3);
	ft_memmove(operator[1], ";", 2);
	ft_memmove(operator[2], "&&", 3);
	ft_memmove(operator[3], "&", 2);
	ft_memmove(operator[4], "||", 3);
	ft_memmove(operator[5], "|", 2);
	ft_memmove(operator[6], "<<-", 4);
	ft_memmove(operator[7], "<<", 3);
	ft_memmove(operator[8], "<&", 3);
	ft_memmove(operator[9], "<>", 3);
	ft_memmove(operator[10], "<", 2);
	ft_memmove(operator[11], ">>", 3);
	ft_memmove(operator[12], ">&", 3);
	ft_memmove(operator[13], ">|", 3);
	ft_memmove(operator[14], ">", 2);
}

int			ft_get_operator(t_lexer *lexer, char *line)
{
	static char	operator[15][5];
	t_token		*token;
	int			len;
	int			i;

	ft_init_operator(operator);
	i = 0;
	while (operator[i])
	{
		if (ft_strncmp(line, operator[i], ft_strlen(operator[i])) == 0)
		{
			if (i < 6)
			{
				token = ft_newtoken(operator[i], "OPERATOR");
				ft_addtoken(lexer, token);
			}
			else
			{
				ft_get_io_number(lexer, line);
				token = ft_newtoken(operator[i], "REDIRECT");
				ft_addtoken(lexer, token);
				if (ft_strequ(operator[i], ">&") || ft_strequ(operator[i], "<&"))
				{
					if ((len = ft_aggreg_fetch_dash(lexer, line + ft_strlen(operator[i]))))
						return(len + ft_strlen(operator[i]));
				}
			}
			return (ft_strlen(operator[i]));
		}
		++i;
	}
	return (0);
}
