/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 11:20:01 by sfranc            #+#    #+#             */
/*   Updated: 2017/09/14 16:41:41 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

int			ft_is_valid_name(char *str)
{
	while (*str)
	{
		if (ft_isalnum(*str) || *str == '_')
			str++;
		else
			return (0);
	}
	return (1);
}

int			ft_builtin_setenv(char **cmd)
{
	char	*var;

	if (!cmd[1])
		ft_puttab(g_shell->env);
	else if (ft_is_valid_name(cmd[1]))
	{
		if (!cmd[2])
			var = ft_strjoin(cmd[1], "=");
		else if (!cmd[3])
			var = ft_strjoin3(cmd[1], "=", cmd[2]);
		else
		{
			ft_put_cmd_error(CMD_SETENV, STR_TOO_MANY);
			return (EXIT_FAILURE);
		}
		ft_modify_variable(&g_shell->env, var);
		free(var);
	}
	else
	{
		ft_put_cmd_error(CMD_SETENV, STR_NAME);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	ft_modify_the_var(char ***env, char *new_var, char *temp_var)
{
	char	*temp_env;
	char	*to_free;
	int	i;

	i = 0;
	while (*(*env + i))
	{
		temp_env = ft_strsub(*(*env + i), 0,\
				ft_strchr(*(*env + i), '=') - *(*env + i));
		if (ft_strequ(temp_env, temp_var))
		{
			to_free = *(*env + i);
			*(*env + i) = ft_strdup(new_var);
			free(to_free);
			free(temp_var);
			free(temp_env);
			return (1);
		}
		free(temp_env);
		i++;
	}
	return (0);
}

void		ft_modify_variable(char ***env, char *new_var)
{
	char	*temp_var;

	if (!*env)
	{
		ft_addtotab(env, new_var);
		return ;
	}
	temp_var = ft_strsub(new_var, 0, ft_strchr(new_var, '=') - new_var);
	ft_addtotab(env, new_var);
	if ((ft_modify_the_var(env, new_var, temp_var)))
		return ;
	free(temp_var);
	ft_addtotab(env, new_var);
}
