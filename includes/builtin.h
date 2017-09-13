/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/29 16:15:50 by sfranc            #+#    #+#             */
/*   Updated: 2017/09/13 16:09:08 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# define EXIT_ERROR		255

# define CMD_CD			"cd"
# define CMD_ECHO		"echo"
# define CMD_EXIT		"exit"
# define STR_NUM		"numeric argument required"
# define STR_TOO_MANY	"too many arguments"
# define STR_HOME		"HOME not set"
# define STR_OLDPWD		"OLDPWD not set"

int		ft_is_builtin(char *cmd);
int		ft_builtin_echo(char **cmd);
void	ft_builtin_exit(char **cmd);

/*
** ENV
*/
char	*ft_get_env_variable(char **env, char *var);

#endif
