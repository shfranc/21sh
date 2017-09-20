/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_again.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/31 14:43:16 by sfranc            #+#    #+#             */
/*   Updated: 2017/09/19 15:16:52 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

void	ft_create_delimiter(t_token *dless, char **delimiter)
{
	if (*delimiter)
		return ;
	if (ft_strchr(dless->next->str, '"') || ft_strchr(dless->next->str, '\'')\
			|| ft_strchr(dless->next->str, '\\'))
	{
		*delimiter = ft_remove_quotes(dless->next->str);
		*delimiter = ft_charappend(*delimiter, '\n');
	}
	else
		*delimiter = ft_strjoin(dless->next->str, "\n");
}

int		ft_read_again_heredoc(t_lexer *lexer, t_token *dless)
{
	static char	*hdoc_buff;
	static char	*delimiter;
	char		*line;

	ft_create_delimiter(dless, &delimiter);
	ft_read_line(&line, write(1, HEREDOC_PROMPT, ft_strlen(HEREDOC_PROMPT)), 1);
	if (!*line)
	{
		free(line);
		return (PARSER_ERROR);
	}
	if (ft_strequ(line, delimiter))
	{
		if (!hdoc_buff)
			hdoc_buff = ft_strdup("");
		dless->heredoc = ft_strdup(hdoc_buff);
		ft_strdel(&hdoc_buff);
		ft_strdel(&delimiter);
	}
	else
		ft_strmerge(&hdoc_buff, line);
	free(line);
	return (ft_parser(lexer));
}

int		ft_read_again_list(t_lexer *lexer, int list_type)
{
	char *line;

	line = NULL;
	if (list_type == PIPE)
		ft_read_line(&line, write(1, PIPE_PROMPT, ft_strlen(PIPE_PROMPT)), 1);
	if (list_type == AND_IF)
	{
		ft_read_line(&line, write(1, AND_IF_PROMPT,\
					ft_strlen(AND_IF_PROMPT)), 1);
	}
	if (list_type == OR_IF)
		ft_read_line(&line, write(1, OR_IF_PROMPT, ft_strlen(OR_IF_PROMPT)), 1);
	if (!*line)
	{
		free(line);
		return (PARSER_ERROR);
	}
	ft_del_lasttoken(lexer);
	ft_tokenize(&lexer, line);
	free(line);
	return (ft_parser(lexer));
}

int		ft_read_again_quoting(t_lexer *lexer)
{
	char *line;
	char *tmp;

	lexer->last->quoting & SQUOTES ? ft_read_line(&tmp,\
			write(1, SQUOTES_PROMPT, ft_strlen(SQUOTES_PROMPT)), 1) : 0;
	lexer->last->quoting & DQUOTES ? ft_read_line(&tmp,\
			write(1, DQUOTES_PROMPT, ft_strlen(DQUOTES_PROMPT)), 1) : 0;
	lexer->last->quoting & ESCAPE ? ft_read_line(&tmp,\
			write(1, ESCAPE_PROMPT, ft_strlen(ESCAPE_PROMPT)), 1) : 0;
	if (!*tmp)
	{
		lexer->last->quoting = 0;
		free(tmp);
		return (PARSER_ERROR);
	}
	line = ft_strjoin(lexer->last->str, tmp);
	ft_del_lasttoken(lexer);
	ft_tokenize(&lexer, line);
	free(line);
	free(tmp);
	return (ft_parser(lexer));
}
