/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 18:47:15 by sfranc            #+#    #+#             */
/*   Updated: 2017/09/13 18:15:21 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

void	ft_init_input_struct(t_input *input, int len_prompt)
{
	struct winsize	win;

	ft_bzero(input, sizeof(t_input));
	input->line = ft_memalloc(INPUTSIZE);
	input->tmp = ft_memalloc(INPUTSIZE);
	if ((ioctl(0, TIOCGWINSZ, &win)) == -1)
		ft_exit("ioctl: Unable to get winsize struct", 1);
	input->width = win.ws_col - 1;
	input->prompt = len_prompt;
	input->x = input->prompt;
}

void	ft_raw_term(void)
{
	const char		*term_type;
	int				ret;
	struct termios	term;

	if (!(term_type = ft_get_env_variable(g_shell->env, "TERM")))
		term_type = ft_strdup(DEFAULT_TERM);
	ret = tgetent(NULL, term_type);
	if (ret < 0)
		ft_exit("tgetent: No access to the termcap database.", 1);
	if (ret == 0)
		ft_exit("tgetent: Terminal type is not defined.", 1);
	if (tcgetattr(0, &term) == -1)
		ft_exit("tcgetattr: Unable to fetch termios struct", 1);
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSANOW, &term) == -1)
		ft_exit("tcsetattr: Unable to set raw mode", 1);
}

void	ft_canonic_term(void)
{
	struct termios	term;

	if (tcgetattr(0, &term) == -1)
		ft_exit("tcgetattr: Unable to fetch termios struct", 1);
	term.c_lflag |= ICANON;
	term.c_lflag |= ECHO;
	if (tcsetattr(0, TCSANOW, &term) == -1)
		ft_exit("tcgetattr: Unable to set canonic mode", 1);
}
