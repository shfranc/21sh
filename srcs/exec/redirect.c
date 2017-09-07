/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/02 13:53:15 by sfranc            #+#    #+#             */
/*   Updated: 2017/09/07 12:45:39 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

int		ft_make_dup2(char *dest_name, int fd_dest, int fd_src)
{
	errno = 0;
	if ((dup2(fd_dest, fd_src)) != -1)
		return (REDIR_OK);
	else
	{
		if (errno == EBADF)
			ft_put_cmd_error(dest_name, STR_BAD_FD);
		else
			ft_put_cmd_error(dest_name, STR_DUP_ERROR);
		return (REDIR_ERROR);
	}
}

int		ft_agreg_files(t_token *redir)
{
	int	fd_dest;
	int	fd_src;

	fd_dest = ft_atoi(redir->next->str);
	if (redir->prev && redir->prev->token_type == IO_NUMBER)
		fd_src = ft_atoi(redir->prev->str);
	else if (redir->operator_type == LESS_AND)
		fd_src = STDIN_FILENO;
	else
		fd_src = STDOUT_FILENO;
	if (ft_isnumber(redir->next->str))
		return (ft_make_dup2(redir->next->str, fd_dest, fd_src));
	else if (ft_strequ(redir->next->str, "-"))
	{
		close(fd_src);
		return (REDIR_OK);
	}
	else
	{
		ft_put_cmd_error(redir->next->str, STR_AMB_REDIR);
		return (REDIR_ERROR);
	}
}

int		ft_heredoc_pipe(t_token *redir)
{
	int fd[2];

	if (pipe(fd) == -1)
	{
		ft_put_cmd_error(redir->str, STR_PIPE_ERROR);
		return (REDIR_ERROR);
	}
	write(fd[1], redir->heredoc, ft_strlen(redir->heredoc));
	close(fd[1]);
	ft_make_dup2(redir->str, fd[0], STDIN_FILENO);
	close(fd[0]);
	return (REDIR_OK);
}

int		ft_open_error(int fd, int err, char *file_name)
{
	if (fd != -1)
		return (REDIR_OK);
	else
	{
		if (err == EACCES)
			ft_put_cmd_error(file_name, STR_PERM_DENIED);
		else if (err == EISDIR)
			ft_put_cmd_error(file_name, STR_IS_DIR);
		else if (err == ENOENT)
			ft_put_cmd_error(file_name, STR_NO_FILE);
		else		
			ft_put_cmd_error(file_name, STR_OPEN_ERROR);
		return (REDIR_ERROR);
	}
}

int		ft_open_file(t_token *redir)
{
	errno = 0;
	if (redir->operator_type == DGREAT)
	{
		if ((redir->fd = open(redir->next->str, O_WRONLY | O_CREAT | O_APPEND,\
						S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
			return (ft_open_error(redir->fd, errno, redir->next->str));
	}
	else if (redir->operator_type == LESS)
	{
		if ((redir->fd = open(redir->next->str, O_RDONLY)) == -1)
			return (ft_open_error(redir->fd, errno, redir->next->str));
	}
	else
	{
		if ((redir->fd = open(redir->next->str, O_WRONLY | O_CREAT | O_TRUNC,\
						S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
			return (ft_open_error(redir->fd, errno, redir->next->str));
	}
	return (REDIR_OK);
}

int		ft_redirect(t_token *redir)
{
	if (redir->prev && redir->prev->token_type == IO_NUMBER)
	{
		return (ft_make_dup2(redir->next->str, redir->fd,\
					ft_atoi(redir->prev->str)));
	}
	else if (redir->operator_type == LESS)
		return (ft_make_dup2(redir->next->str, redir->fd, STDIN_FILENO));
	else
		return (ft_make_dup2(redir->next->str, redir->fd, STDOUT_FILENO));
}

int		ft_init_redirection(t_ast *ast)
{
	t_token	*tmp;

	tmp = ast->token;
	while (tmp)
	{
		if (tmp->token_type == REDIRECT)
		{
			if (tmp->operator_type == LESS_AND
					|| tmp->operator_type == GREAT_AND)
			{
				if (ft_agreg_files(tmp) == REDIR_ERROR)
					return (REDIR_ERROR);
			}
			else if (tmp->operator_type == DLESS)
			{
				if (ft_heredoc_pipe(tmp) == REDIR_ERROR)
					return (REDIR_ERROR);
			}
			else
			{
				if (ft_open_file(tmp) == REDIR_ERROR)
					return (REDIR_ERROR);
				if (ft_redirect(tmp) == REDIR_ERROR)
					return (REDIR_ERROR);
			}
			tmp = tmp->next->next;
		}
		else
			tmp = tmp->next;
	}
	return (REDIR_OK);
}
