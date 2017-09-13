/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 17:20:21 by sfranc            #+#    #+#             */
/*   Updated: 2017/09/13 18:32:39 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

static int		ft_modify_variable(char ***env, char *new_var)
{
	char	*to_free;
	char	*temp_env;
	char	*temp_var;
	int		i;

	temp_var = ft_strsub(new_var, 0, ft_strchr(new_var, '=') - new_var);
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
	free(temp_var);
	return (0);
}

static void	ft_increase_shlvl(char ***env)
{
	char	*shlvl;
	char	*temp;
	char	*newlvl;
	int		lvl;

	if ((shlvl = ft_get_env_variable(*env, "SHLVL")))
	{
		lvl = ft_atoi(shlvl) + 1;
		newlvl = ft_itoa(lvl);
		temp = shlvl;
		shlvl = ft_strjoin("SHLVL=", newlvl);
		free(temp);
		free(newlvl);
		ft_modify_variable(env, shlvl);
		free(shlvl);
	}
	else
		ft_addtotab(env, "SHLVL=1");
}

static void	ft_update_pwd(char ***env)
{
	char	*cwd;
	char	*pwd;
	char	*temp;

	if (!(cwd = getcwd(NULL, 0)))
		return ;
	if ((pwd = ft_get_env_variable(*env, "PWD")))
	{
		temp = cwd;
		cwd = ft_strjoin("PWD=", cwd);
		free(temp);
		ft_modify_variable(env, cwd);
		free(pwd);
		free(cwd);
	}
	else
	{
		pwd = ft_strjoin("PWD=", cwd);
		ft_addtotab(env, pwd);
		free(pwd);
		free(cwd);
	}
}

t_shell		*ft_init(char **environ)
{
	t_shell	*shell;

	shell = ft_memalloc(sizeof(t_shell));
	shell->env = ft_tabdup(environ);
	ft_increase_shlvl(&(shell->env));
	ft_update_pwd(&shell->env);
	return (shell);
}
