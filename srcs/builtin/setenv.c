/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 11:20:01 by sfranc            #+#    #+#             */
/*   Updated: 2017/09/14 11:31:22 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

void	ft_modify_variable(char ***env, char *new_var)
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
			return ;
		}
		free(temp_env);
		i++;
	}
	free(temp_var);
	ft_addtotab(env, new_var);
}
