/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/20 17:21:10 by sfranc            #+#    #+#             */
/*   Updated: 2017/07/24 12:24:15 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef struct	s_token
{
	char			*str;
	char			*token;
	struct s_token	*next;
	struct s_token	*prev;
}				t_token;

typedef struct	s_lexer
{
	t_token	*first;
	t_token	*last;
	int		nbr_token;
}				t_lexer;

typedef enum e_tokentype
{
	WORD,
	OPERATOR,
	REDIRECT,
	IO_NUMBER,
	NEW_LINE,
}			t_tokentype;

t_lexer	*ft_tokenize(char *line);

/*
** LIST LEXER
*/
t_token	*ft_newtoken(char *str, char *token);
void	ft_addtoken(t_lexer *lexer, t_token *token);
void	ft_printlexer(t_lexer *lexer);
void	ft_dellexer(t_lexer *lexer);

#endif
