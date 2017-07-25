/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/20 17:21:10 by sfranc            #+#    #+#             */
/*   Updated: 2017/07/25 17:18:04 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#define	DQUOTES 1

typedef struct	s_token
{
	char			*str;
	char			*token;
	int				flags;
	struct s_token	*next;
	struct s_token	*prev;
}				t_token;

typedef struct	s_lexer
{
	t_token	*first;
	t_token	*last;
	int		nbr_token;
}				t_lexer;

t_lexer	*ft_tokenize(char *line);

/*
** LIST LEXER
*/
t_token	*ft_newtoken(char *str, char *token);
void	ft_addtoken(t_lexer *lexer, t_token *token);
void	ft_printlexer(t_lexer *lexer);
void	ft_dellexer(t_lexer *lexer);
void	ft_reverseprint(t_lexer *lexer);

#endif
