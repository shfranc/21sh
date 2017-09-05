/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/02 13:53:15 by sfranc            #+#    #+#             */
/*   Updated: 2017/09/05 18:53:38 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

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
			// open or create occording to redir type
			if (tmp->operator_type == DGREAT)
			{
				tmp->fd = open(tmp->next->str, O_WRONLY | O_CREAT | O_APPEND,\
						S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
			}
			else
			{
				tmp->fd = open(tmp->next->str, O_WRONLY | O_CREAT | O_TRUNC,\
						S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
			}

			// dup2 according to redir type and default values
			//if (tmp->token_type == GREAT || tmp->token_type == DGREAT\
			//		|| tmp->token_type == GREAT_AND)
				dup2(tmp->fd, STDOUT_FILENO);
			//else if (tmp->token_type == LESS || tmp->token_type == LESS_AND)
			//	dup2(tmp->fd, STDIN_FILENO);

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
			close(tmp->fd);
		tmp = tmp->next;
	}
	ft_putendl("redir restaurees");
}
