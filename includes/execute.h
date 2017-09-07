/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 11:28:24 by sfranc            #+#    #+#             */
/*   Updated: 2017/09/07 19:27:22 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>

# define PATH_OK			0
# define REDIR_OK			0
# define REDIR_ERROR		1
# define CMD_NOT_FOUND		127
# define NO_FILE 			127
# define IS_DIR 			126
# define PERM_DENIED 		126

# define STR_CMD_NOT_FOUND	"command not found"
# define STR_NO_FILE 		"No such file or directory"
# define STR_IS_DIR 		"is a directory"
# define STR_PERM_DENIED 	"Permission denied"
# define STR_BAD_FD 		"Bad file descriptor"
# define STR_AMB_REDIR		"ambiguous redirection"
# define STR_OPEN_ERROR		"open error"
# define STR_DUP_ERROR 		"dup error"
# define STR_PIPE_ERROR 	"pipe failed"

int		ft_execute(t_ast *ast);
int		ft_launch_simple_cmd(t_ast *ast);

/*
** EXPANSION AND QUOTES
*/
void	ft_expand(t_token *token);
void	ft_remove_quoting(t_token *token);

/*
** REDIRECTION
*/
void	ft_save_std_fd(int save[3]);
void	ft_restore_std_fd(t_ast *ast, int save[3]);
int		ft_init_redirection(t_ast *ast);
int		ft_agreg_files(t_token *redir);
int		ft_heredoc_pipe(t_token *redir);
int		ft_make_dup2(char *dest_name, int fd_dest, int fd_src);

/*
** PATH
*/
int		ft_get_path(char *cmd, char **path);
void	ft_put_cmd_error(char *cmd, char *error);
//int		ft_check_given_path(char *cmd, char **cmd_path);
//int		ft_search_through_path(char *cmd, char **cmd_path);

#endif
