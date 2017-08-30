/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 11:28:24 by sfranc            #+#    #+#             */
/*   Updated: 2017/08/30 19:11:12 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H



# define PATH_OK		0
# define CMD_NOT_FOUND	127
# define NO_FILE 		127
# define IS_DIR 		126
# define PERM_DENIED 	126

# define STR_CMD_NOT_FOUND	"command not found"
# define STR_NO_FILE 		"No such file or directory"
# define STR_IS_DIR 		"is a directory"
# define STR_PERM_DENIED 	"Permission denied"

int		ft_execute(t_ast *ast);
int		ft_launch_simple_cmd(t_ast *ast);

/*
** PATH
*/
int		ft_get_path(char *cmd, char **path);
//int		ft_check_given_path(char *cmd, char **cmd_path);
//int		ft_search_through_path(char *cmd, char **cmd_path);

#endif
