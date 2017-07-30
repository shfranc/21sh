/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/20 17:21:10 by sfranc            #+#    #+#             */
/*   Updated: 2017/07/30 19:46:26 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#define	DQUOTES 1
#define	SQUOTES 1 << 1
#define	ESCAPE 1 << 2

typedef struct	s_token
{
	char			*str;
	char			*token;
	int				token_type;
	int				flags; 		// inhibiteur
	struct s_token	*next;
	struct s_token	*prev;
}				t_token;

typedef struct	s_lexer
{
	t_token	*first;
	t_token	*last;
	int		nbr_token;
	int		flags;
}				t_lexer;

enum			e_tokenlst
{
	NONE,
	DSEMI,
	SEMI,
	AND_IF,
	AND,
	OR_IF,
	PIPE,
	DLESS_DASH,
	DLESS,
	LESS_AND,
	LESS_GREAT,
	LESS,
	DGREAT,
	GREAT_AND,
	CLOBBER,
	GREAT
};

t_lexer	*ft_tokenize(char *line);

/*
** GET WORD
*/
int		ft_part_word(char c);
int		ft_get_word(t_lexer *lexer, char *line);
int		ft_goto_next_quote_withescape(char *line, char quote);
int		ft_goto_next_quote(char *line, char quote);

/*
** GET OPERATOR
*/
int		ft_part_operator(char c);
int		ft_get_operator(t_lexer *lexer, char *line);
void	ft_get_io_number(t_lexer *lexer, char *line);
int		ft_aggreg_fetch_dash(t_lexer *lexer, char *line);

/*
** LIST LEXER
*/
t_token	*ft_newtoken(char *str, char *token);
void	ft_addtoken(t_lexer *lexer, t_token *token);
void	ft_dellexer(t_lexer *lexer);

void	ft_printlexer(t_lexer *lexer);
void	ft_reverseprint(t_lexer *lexer);

#endif
