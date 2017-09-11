/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 15:31:14 by sfranc            #+#    #+#             */
/*   Updated: 2017/09/11 18:24:40 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

int		ft_launch_one_side(t_ast *side)
{
	int	save[3];
	char **cmd;
	char *path;
	int	status;

	ft_save_std_fd(save);
//	ft_expand(ast->token);
//	ft_remove_quoting(ast->token);

	if (ft_init_redirection(side) != REDIR_OK)
	{
		ft_restore_std_fd(side, save);
		return (REDIR_ERROR);
	}

	if ((cmd = ft_cmd_into_tab(side)))
	{
		if ((status = ft_get_path(cmd[0], &path)) == PATH_OK)
		{
			if ((status = execve(path, cmd, g_env)) == -1)
				ft_exit("21sh: execve: failed to execute the command", 1);
			free(path);
		}
		else
			return (status);
		ft_freetab(&cmd);
	}
	else
		return (EXIT_SUCCESS);

	ft_restore_std_fd(side, save);
	return (status);
}

int		ft_launch_pipeline(t_ast *node_left, t_ast *node_right)
{
	int		fd[2];
//	static int i = 0;

	pid_t	pid_right;
	pid_t	pid_left;
	int		status_left;
	int		status_right;

//	ft_putstr("pipeline start LVL= ");
//	ft_putnbr_endl(i++);

	if (pipe(fd) == -1)
	{
		ft_put_cmd_error(node_left->left->token->str, STR_PIPE_ERROR);
		return (EXIT_FAILURE);
	}

	if ((pid_left = fork()) == -1)
		ft_exit("21sh: fork: fork failed, no child created", 1);

	if (pid_left == 0)
	{
//		ft_putstr("pipeline LEFT: ");
//		ft_putendl(node_left->token->str);
		close(fd[0]);
		ft_make_dup2(node_left->token->str, fd[1], STDOUT_FILENO);
		exit(ft_launch_one_side(node_left));
	}
	else
	{

		if (node_right->parent->parent && node_right->parent->parent->operator_type == PIPE)
		{
//			ft_save_std_fd(save);
			close(fd[1]);
			ft_make_dup2(node_right->token->str, fd[0], STDIN_FILENO);
			status_right = ft_launch_pipeline(node_right, node_right->parent->parent->right);
			close(fd[0]);
//			ft_restore_std_fd()
			return (WEXITSTATUS(status_right));
			//return (ft_launch_pipeline(node_right, node_right->parent->parent->right));
		}

		// ft_pipe_to_right(int pif, t_ast *node, int pid)

		if ((pid_right = fork()) == -1)
			ft_exit("21sh: fork: fork failed, no child created", 1);
		if (pid_right == 0)
		{
//			ft_putstr("pipeline RIGHT: ");
//			ft_putendl(node_right->token->str);
			close(fd[1]);
			ft_make_dup2(node_right->token->str, fd[0], STDIN_FILENO);
			exit(ft_launch_one_side(node_right));
		}
		else
		{
			close(fd[1]);
			waitpid(pid_right, &status_right, 0);
		}
		close(fd[0]);
		waitpid(pid_left, &status_left, 0);
	}
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
