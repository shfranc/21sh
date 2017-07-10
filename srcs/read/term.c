/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 18:47:15 by sfranc            #+#    #+#             */
/*   Updated: 2017/07/10 18:53:56 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

void	ft_raw_term(void)
{
	const char		*term_type;
	int				ret;
	//	struct termios	sauv;
	struct termios	term;

	term_type = getenv("TERM");
	if (term_type == NULL)
		ft_exit("No TERM in the environement.", 1);
	ret = tgetent(NULL, term_type);
	if (ret < 0)
		ft_exit("No access to the termcap database.", 1);
	if (ret == 0)
		ft_exit("Terminal type is not defined.", 1);
	if (tcgetattr(0, &term) == -1)
		ft_exit("Unable to fetch termios struct", 1);
	//	ft_memmove(&sauv, &term, sizeof(term));
	term.c_lflag &= ~ (ICANON);
	term.c_lflag &= ~ (ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		ft_exit("Unable to set raw mode", 1);
}

void	ft_canonic_term(void)
{
	struct	termios	term;

	if (tcgetattr(0, &term) == -1)
		ft_exit("Unable to fetch termios struct", 1);
	term.c_lflag |=  ICANON;
	term.c_lflag |=  ECHO;
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		ft_exit("Unable to set canonic mode", 1);
}

int		ft_intputchar(int c)
{
	write(1, &c, 1);
	return (0);
}

void	ft_clear(t_input *input)
{
	int i;

	if (input->y != 0)
	{
		i = input->y;
		while (i--)
			tputs(tgetstr("up", NULL), 1, &ft_intputchar);
	}

	tputs(tgetstr("cr", NULL), 1, &ft_intputchar);
	i = input->prompt;
	while (i--)
		tputs(tgetstr("nd", NULL), 1, &ft_intputchar);
	tputs(tgetstr("cd", NULL), 1, &ft_intputchar);

}

int		ft_interpret(char *buff, t_input *input)
{
	if (buff[0] == 27 && ft_strequ(&buff[1], "[C"))
		ft_move_right(input);

	if (buff[0] == 27 && ft_strequ(&buff[1], "[D"))
		ft_move_left(input);

	if (buff[0] == '\n')
	{
		write(1, &buff[0], 1);
		return (1);
	}

	if (ft_isprint(buff[0]))
	{
	/*	ft_clear(input);
		input->line = ft_strcat(input->line, buff);
		ft_putstr(input->line);
//		write(1, &buff[0], 1);
		input->len++;
		ft_increase_cursorpos(input);
		if (input->x == 0)
		{
			tputs(tgetstr("cr", NULL), 1, &ft_intputchar);
			tputs(tgetstr("do", NULL), 1, &ft_intputchar);
		}*/
		ft_insertchar(buff, input);
	}

	if (buff[0] == 'c')
	{
		ft_clear(input);
		ft_bzero(input->line, INPUTSIZE);
		input->x = input->prompt;
		input->y = 0;
		input->len = 0;
	}

	/*	if (buff[0] == 127)
		{
		ft_deletechar(input);	
		if (input->y == 0)
		input->x = input->prompt + input->len;
		else
		input->x = (input->prompt + input->len) % input->width;
		ft_clearndisplay(input);
		}
		*/
	if (buff[0] == 4 && !*input->line)
		ft_exit("exit", 1);

	return (0);
}
