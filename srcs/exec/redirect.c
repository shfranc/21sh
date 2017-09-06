/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/02 13:53:15 by sfranc            #+#    #+#             */
/*   Updated: 2017/09/06 12:54:24 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

int		ft_open_file(t_token *redir)
{
	errno = 0;
	if (redir->operator_type == LESS_AND || redir->operator_type == GREAT_AND\
			|| redir->operator_type == DLESS)
		return (REDIR_OK);

	if (redir->operator_type == DGREAT)
	{
		if ((redir->fd = open(redir->next->str, O_WRONLY | O_CREAT | O_APPEND,\
						S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
		{
			ft_put_cmd_error(redir->next->str, "open error");
			return (REDIR_ERROR);
		}
	}
/*	else if (redir->operator_type == LESS)
	{
		if ((redir->fd = open(redir->next->str, O_WRONLY)) == -1)
		{
			ft_put_cmd_error(redir->next->str, "open error");
			return (REDIR_ERROR);
		}
	}*/
	else
	{
		if ((redir->fd = open(redir->next->str, O_WRONLY | O_CREAT | O_TRUNC,\
						S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
		{
			ft_put_cmd_error(redir->next->str, "open error");
			return (REDIR_ERROR);
		}
	}
	return (REDIR_OK);
}

int		ft_redirect(t_token *redir)
{
	if (redir->operator_type == LESS_AND || redir->operator_type == GREAT_AND\
			|| redir->operator_type == DLESS)
		return (REDIR_OK);
	
	if (redir->prev && redir->prev->token_type == IO_NUMBER)
	{
		dup2(redir->fd, ft_atoi(redir->prev->str));
	}
	else if (redir->operator_type == LESS)
	{
		dup2(redir->fd, STDIN_FILENO);
	}
	else
	{
		dup2(redir->fd, STDOUT_FILENO);
	}
	return (REDIR_OK);
}

int		ft_init_redirection(t_ast *ast, int	save[3])
{
	t_token	*tmp;

	save[0] = dup(STDIN_FILENO);
	save[1] = dup(STDOUT_FILENO);
	save[2] = dup(STDERR_FILENO);

	tmp = ast->token;
	while (tmp)
	{
		if (tmp->token_type == REDIRECT)
		{
			if (ft_open_file(tmp) == REDIR_ERROR)
				return (REDIR_ERROR);
			if (ft_redirect(tmp) == REDIR_ERROR)
				return (REDIR_ERROR);
			tmp = tmp->next->next;
		}
		else
			tmp = tmp->next;

	}
	return (REDIR_OK);
}

void	ft_restore_std_fd(t_ast *ast, int save[3])
{
	t_token *tmp;

	dup2(save[0], STDIN_FILENO);
	dup2(save[1], STDOUT_FILENO);
	dup2(save[2], STDERR_FILENO);
	close(save[0]);
	close(save[1]);
	close(save[2]);
	tmp = ast->token;
	while (tmp)
	{
		if (tmp->token_type == REDIRECT)
		{
			if (tmp->fd > 0)
				close(tmp->fd);
		}
		tmp = tmp->next;
	}
}
