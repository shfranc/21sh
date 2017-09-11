/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 15:31:14 by sfranc            #+#    #+#             */
/*   Updated: 2017/09/11 15:08:34 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

int		ft_launch_pipeline(t_ast *node)
{
	int		save[3];
	int		fd[2];
	
	pid_t	pid_right;
	pid_t	pid_left;
	int		status_left;
	int		status_right;
	char	*path_right;
	char	*path_left;
	char	**cmd_left;
	char	**cmd_right;


	if (pipe(fd) == -1)
	{
		ft_put_cmd_error(node->left->token->str, STR_PIPE_ERROR);
		return (EXIT_FAILURE);
	}
	
	if ((pid_left = fork()) == -1)
		ft_exit("21sh: fork: fork failed, no child created", 1);
	
	if (pid_left == 0)
	{
		close(fd[0]);
		ft_make_dup2(node->left->token->str, fd[1], STDOUT_FILENO);
		close(fd[1]);

		ft_save_std_fd(save);
		if ((cmd_left = ft_cmd_into_tab(node->left)))
		{
			if ((status_left = ft_get_path(cmd_left[0], &path_left)) == PATH_OK)
			{
				if ((status_left = execve(path_left, cmd_left, g_env)) == -1)
					ft_exit("21sh: execve: failed to execute the command", 1);
			}
			else
				exit(status_left);
		}
		else
			exit(EXIT_SUCCESS);
		
		ft_restore_std_fd(node->right, save);
			
	}
	else
	{
		if ((pid_right = fork()) == -1)
			ft_exit("21sh: fork: fork failed, no child created", 1);
		if (pid_right == 0)
		{
			close(fd[1]);
			ft_make_dup2(node->right->token->str, fd[0], STDIN_FILENO);
			close(fd[0]);

			ft_save_std_fd(save);
			if ((cmd_right = ft_cmd_into_tab(node->right)))
			{
				if ((status_right = ft_get_path(cmd_right[0], &path_right)) == PATH_OK)
				{
					if ((status_right = execve(path_right, cmd_right, g_env)) == -1)
						ft_exit("21sh: execve: failed to execute the command", 1);
				}
				else
					exit(status_right);
			}
			else
				exit(EXIT_SUCCESS);
			ft_restore_std_fd(node->right, save);
		}
		else
		{
			close(fd[1]);
			wait(&status_right);
		}
		close(fd[0]);
		wait(&status_left);
	}

	if (node->parent && node->parent->operator_type == PIPE)
		ft_launch_pipeline(node->parent);


	return (WEXITSTATUS(status_right));
}

/*


int		ft_fork(char *path, char **cmd)
{
	pid_t	pid;
	int		status;
	int 	ret_cmd;

	if ((pid = fork()) == -1)
		ft_exit("21sh: fork: fork failed, no child created", 1);
	if (pid == 0)
	{
		if ((status = execve(path, cmd, g_env)) == -1)
			ft_exit("21sh: execve: failed to execute the command", 1);
	}
	else
		wait(&status);
	ret_cmd = WEXITSTATUS(status);
	return (ret_cmd);
}

int		ft_launch_simple_cmd(t_ast *ast)
{
	char	*path;
	char	**cmd;
	int		ret_cmd;
	int		save[3];

	ft_save_std_fd(save);
//	ft_expand(ast->token);
//	ft_remove_quoting(ast->token);
	if (ft_init_redirection(ast) != REDIR_OK)
	{
		ft_restore_std_fd(ast, save);
		return (REDIR_ERROR);
	}
	if ((cmd = ft_cmd_into_tab(ast)))
	{
		if ((ret_cmd = ft_get_path(cmd[0], &path)) == PATH_OK)
		{
			ret_cmd = ft_fork(path, cmd);
			free(path);
		}
		ft_freetab(&cmd);
	}
	else
		ret_cmd = EXIT_SUCCESS;
	ft_restore_std_fd(ast, save);
	return (ret_cmd);
}*/