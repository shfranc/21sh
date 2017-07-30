/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/30 17:58:31 by sfranc            #+#    #+#             */
/*   Updated: 2017/07/30 18:52:47 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define SHELL "21sh: "
# define SYNTAX_ERR "syntax error near unexpected token `"
# define END_ERR "'"

void	ft_parser(t_lexer *lexer);

#endif
