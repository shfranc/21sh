/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 12:49:58 by sfranc            #+#    #+#             */
/*   Updated: 2017/06/30 19:19:44 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

/*static char	*ft_get_user(void)
{
	struct passwd *ret_pwd;

	if (!(ret_pwd = getpwuid(getuid())))
		return (NULL);
	return (ft_strdup(ret_pwd->pw_name));
}

static void	ft_display_prompt(void)
{
	char *user;
	char *cwd;

	user = NULL;
	cwd = NULL;
	ft_putstr(BCYAN);
	if ((user = ft_get_user()))
	{
		ft_putstr(user);
		ft_putstr(": ");
	}
	else
		ft_putstr("minishell: ");
	free(user);
	ft_putstr(RESET);
	ft_putstr(BBLUE);
	if ((cwd = getcwd(NULL, 0)))
		ft_putstr(cwd);
	free(cwd);
	ft_putstr(RESET);
	ft_putstr("\n$> ");
}*/

int		main(void)
{
	char	buff[6];
	t_input	input;
	struct winsize	win;


	ft_bzero(&input, sizeof(t_input));
	input.line = ft_memalloc(INPUTSIZE);

	if ((ioctl(0, TIOCGWINSZ, &win)) == -1)
		ft_exit("Unable to get winsize struct", 1);
	input.width = win.ws_col;
	//	ft_putnbr_endl(input.width);

	//	intercepter les signaux avant les termcaps
	while (1)
	{
		ft_raw_term();
		ft_bzero(buff, 6);
		read(0, buff, 6);
		if (ft_interpret(buff, &input))
			break ;
	}
	ft_canonic_term();
	return (0);
}
