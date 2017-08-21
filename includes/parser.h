/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/30 17:58:31 by sfranc            #+#    #+#             */
/*   Updated: 2017/08/15 12:14:54 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define PARSER_SUCCESS 0
# define PARSER_ERROR 1
# define SHELL "21sh: "
# define SYNTAX_ERR "syntax error near unexpected token `"
# define UNEXPECTED_EOF "syntax error: unexpected end of file"
# define END_ERR "'"
# define SQUOTES_PROMPT "squote> "
# define DQUOTES_PROMPT "dquote> "
# define ESCAPE_PROMPT "escape> "
# define PIPE_PROMPT "pipe> "
# define AND_IF_PROMPT "and_if> "
# define OR_IF_PROMPT "or_if> "
# define HEREDOC_PROMPT "heredoc> "

typedef struct	s_ast
{
	struct s_ast	*parent;
	struct s_ast	*left;
	struct s_ast	*right;
	t_lexer			*token;
}				t_ast;

int		ft_parser(t_lexer *lexer);
void	ft_create_ast(t_lexer *lexer);

/*
** SYNTAX ERROR
*/
int		ft_syntax_error(t_lexer *lexer);

/*
** INCOMPLETE INPUT
*/
int		ft_read_again_quoting(t_lexer *lexer);
int		ft_read_again_heredoc(t_lexer *lexer, t_token *dless);
int		ft_read_again_list(t_lexer *lexer, int list_type);

/*
** QUOTES for heredoc delimiter
*/
char	*ft_remove_quotes(char *str);

#endif
