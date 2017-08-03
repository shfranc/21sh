/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_again.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/31 14:43:16 by sfranc            #+#    #+#             */
/*   Updated: 2017/08/02 19:37:57 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

void	ft_create_delimiter(t_token *dless, char **delimiter)
{
	if (*delimiter)
	{
		ft_putendl("** delim existe");
		return ;
	}
	if (ft_strchr(dless->next->str, '"') || ft_strchr(dless->next->str, '\'')\
			|| ft_strchr(dless->next->str, '\\'))
	{
		ft_putendl("** quotes a a enlever");
		*delimiter = ft_remove_quotes(dless->next->str);
		*delimiter = ft_charappend(*delimiter, '\n');
	}
	else
	{
		ft_putendl("** pas de quotes");
		*delimiter = ft_strjoin(dless->next->str, "\n");
	}
}

void	ft_read_again_heredoc(t_lexer *lexer, t_token *dless)
{
	static char	*hdoc_buff;
	static char	*delimiter;
	char		*line;

	ft_create_delimiter(dless, &delimiter);
	ft_putstr("** delim = ");
	ft_putstr(delimiter);
	ft_read_line(&line, write(1, HEREDOC_PROMPT, ft_strlen(HEREDOC_PROMPT)));
	if (ft_strequ(line, delimiter))
	{
		if (!hdoc_buff)
			hdoc_buff = ft_strdup("");
		dless->heredoc = ft_strdup(hdoc_buff);
		ft_strdel(&hdoc_buff);
		ft_strdel(&delimiter);
	}
	else
	{
		ft_strmerge(&hdoc_buff, line);
		ft_putendl(hdoc_buff);
	}
	free(line);
	ft_parser(lexer);
}

void	ft_read_again_list(t_lexer *lexer, int list_type)
{
	char *line;

	line = NULL;
	if (list_type == PIPE)
		ft_read_line(&line, write(1, PIPE_PROMPT, ft_strlen(PIPE_PROMPT)));
	if (list_type == AND_IF)
		ft_read_line(&line, write(1, AND_IF_PROMPT, ft_strlen(AND_IF_PROMPT)));
	if (list_type == OR_IF)
		ft_read_line(&line, write(1, OR_IF_PROMPT, ft_strlen(OR_IF_PROMPT)));
	ft_del_lasttoken(lexer);
	ft_tokenize(&lexer, line);
	free(line);
	ft_parser(lexer);
}

void	ft_read_again_quoting(t_lexer *lexer)
{
	char *line;
	char *tmp;

	lexer->last->quoting & SQUOTES ? ft_read_line(&tmp,\
			write(1, SQUOTES_PROMPT, ft_strlen(SQUOTES_PROMPT))) : 0;
	lexer->last->quoting & DQUOTES ? ft_read_line(&tmp,\
			write(1, DQUOTES_PROMPT, ft_strlen(DQUOTES_PROMPT))) : 0;
	lexer->last->quoting & ESCAPE ? ft_read_line(&tmp,\
			write(1, ESCAPE_PROMPT, ft_strlen(ESCAPE_PROMPT))) : 0;
	line = ft_strjoin(lexer->last->str, tmp);
	ft_del_lasttoken(lexer);
	ft_tokenize(&lexer, line);
	free(line);
	free(tmp);
	ft_parser(lexer);
}
