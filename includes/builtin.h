/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/29 16:15:50 by sfranc            #+#    #+#             */
/*   Updated: 2017/09/13 11:38:13 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# define CMD_CD		"cd"
# define CMD_ECHO	"echo"
# define STR_HOME	"HOME not set"
# define STR_OLDPWD	"OLDPWD not set"

int		ft_launcher(char **cmd);
int		ft_builtin_echo(char **cmd);
//int		ft_builtin_cd(char **cmd);

/*
** ENV
*/
char	*ft_get_env_variable(char **env, char *var);

#endif
