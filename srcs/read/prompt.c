/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/06 17:10:16 by sfranc            #+#    #+#             */
/*   Updated: 2017/07/21 11:21:52 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

static char	*ft_get_user(void)
{
	struct passwd *ret_pwd;

	if (!(ret_pwd = getpwuid(getuid())))
		return (NULL);
	return (ft_strdup(ret_pwd->pw_name));
}

/*
** Initialisation cwd et user a NULL inutile ?
*/

int			ft_display_prompt(void)
{
	char	*user;
	char	*cwd;
	int		len;

	len = 6;
	ft_putstr(BWHITE);
	if ((user = ft_get_user()))
	{
		ft_putstr(user);
		ft_putstr(": "RESET);
		len += ft_strlen(user);
	}
	else
	{
		ft_putstr("21sh: "RESET);
		len += 4;
	}
	free(user);
	ft_putstr(BLUE);
	if ((cwd = getcwd(NULL, 0)))
		ft_putstr(cwd);
	len += ft_strlen(cwd);
	free(cwd);
	ft_putstr(RESET" $> ");
	return (len);
}
