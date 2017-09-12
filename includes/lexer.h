/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/20 17:21:10 by sfranc            #+#    #+#             */
/*   Updated: 2017/09/12 17:42:47 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# define	DQUOTES 1
# define	SQUOTES 1 << 1
# define	ESCAPE 1 << 2

typedef struct	s_token
{
	char			*str;
	int				token_type;
	int				operator_type;
	int				quoting;
	int				fd;
	char			*heredoc;
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

enum			e_tokentype
{
	WORD,
	OPERATOR,
	REDIRECT,
	IO_NUMBER,
	NEWLINE
};

enum			e_operatorlst
{
	NONE,
	DSEMI,
	SEMI,
	AND_IF,
	AND,
	OR_IF,
	PIPE,
	DLESS_DASH, 	// ** SYNTAX ERR **
	DLESS, 			// HEREDOC - PIPE
	LESS_AND,		// AGREG STDIN
	LESS_GREAT,		// ** SYNTAC ERR **
	LESS,			// REDIR STDIN
	DGREAT,			// REDIR STOUT APPEND
	GREAT_AND,		// AGREG STDIN
	CLOBBER,		// ** SYNTAX ERR **
	GREAT			// REDIR STDOUT
};

void	ft_tokenize(t_lexer **lexer, char *line);

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
t_token	*ft_newtoken(char *str, int token_type, int operator_type);
void	ft_addtoken(t_lexer *lexer, t_token *token);
void	ft_del_lasttoken(t_lexer *lexer);
void	ft_dellexer(t_lexer **lexer);
void	ft_deltokens(t_token **token);
void	ft_printlexer(t_token *token, int nbr_token);
void	ft_reverseprint(t_lexer *lexer);

#endif
