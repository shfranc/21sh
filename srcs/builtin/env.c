/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/29 16:29:24 by sfranc            #+#    #+#             */
/*   Updated: 2017/09/13 17:40:44 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

int		ft_builtin_env(char **cmd)
{
	if (!cmd[1])
		ft_puttab(g_shell->env);
	return (1);
}

char	*ft_get_env_variable(char **env, char *var)
{
	char	*temp;
	char	*stop;
	int		i;

	i = 0;
	while (*(env + i))
	{
		temp = ft_strsub(*(env + i), 0,\
				ft_strchr(*(env + i), '=') - *(env + i));
		if (ft_strequ(temp, var))
		{
			stop = ft_strchr(*(env + i), '=');
			free(temp);
			return (ft_strsub(*(env + i), stop - *(env + i) + 1,\
						ft_strlen(stop)));
		}
		i++;
		free(temp);
	}
	return (NULL);
}
