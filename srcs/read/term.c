/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 18:47:15 by sfranc            #+#    #+#             */
/*   Updated: 2017/07/17 18:56:07 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"
#include <stdio.h>

void	ft_init_input_struct(t_input *input)
{
	struct winsize	win;

	ft_bzero(input, sizeof(t_input));
	input->line = ft_memalloc(INPUTSIZE);
	if ((ioctl(0, TIOCGWINSZ, &win)) == -1)
		ft_exit("ioctl: Unable to get winsize struct", 1);
	input->width = win.ws_col - 1;
	input->prompt = ft_display_prompt();
	input->x = input->prompt;
	
	input->right = tgetstr("nd", NULL);
	input->left = tgetstr("le", NULL);
	input->up = tgetstr("up", NULL);
	input->down = tgetstr("sf", NULL);
	input->cr = tgetstr("cr", NULL);
	
//	if (!input->right || !input->left || !input->up || !input->down || !input->cr || !input->bl)
//		ft_exit("Unable to reach termcaps", 1);
}

void	ft_raw_term(void)
{
	const char		*term_type;
	int				ret;
	//	struct termios	sauv;
	struct termios	term;

	term_type = getenv("TERM");
	if (term_type == NULL)
		ft_exit("getenv: No TERM in the environement.", 1);
	ret = tgetent(NULL, term_type);
	if (ret < 0)
		ft_exit("tgetent: No access to the termcap database.", 1);
	if (ret == 0)
		ft_exit("tgetent: Terminal type is not defined.", 1);
	if (tcgetattr(0, &term) == -1)
		ft_exit("tcgetattr: Unable to fetch termios struct", 1);
	//	ft_memmove(&sauv, &term, sizeof(term));
	term.c_lflag &= ~ (ICANON);
	term.c_lflag &= ~ (ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		ft_exit("tcsetattr: Unable to set raw mode", 1);
}

void	ft_canonic_term(void)
{
	struct	termios	term;

	if (tcgetattr(0, &term) == -1)
		ft_exit("tcgetattr: Unable to fetch termios struct", 1);
	term.c_lflag |=  ICANON;
	term.c_lflag |=  ECHO;
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		ft_exit("tcgetattr: Unable to set canonic mode", 1);
}
