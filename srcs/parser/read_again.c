/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_again.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/31 14:43:16 by sfranc            #+#    #+#             */
/*   Updated: 2017/07/31 18:28:45 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

void	ft_read_again_heredoc(t_lexer *lexer, t_token *dless)
{
	static char	*hdoc_buff;
	char		*line;

	ft_read_line(&line, write(1, HEREDOC_PROMPT, ft_strlen(HEREDOC_PROMPT)));
	(void)lexer;
	(void)dless;
	if (ft_strequ(dless->next->str, ft_strsub(line, 0, ft_strlen(line -1))))
	{
		dless->heredoc = hdoc_buff;
		ft_strdel(&hdoc_buff);
	}
	else
	{
		hdoc_buff = ft_strjoin(hdoc_buff, line);
	}
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
	ft_parser(lexer);
	free(line);
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
	ft_parser(lexer);
	
	free(tmp);
	free(line);
}

