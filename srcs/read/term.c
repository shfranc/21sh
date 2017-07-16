/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 18:47:15 by sfranc            #+#    #+#             */
/*   Updated: 2017/07/16 19:18:17 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"
#include <stdio.h>

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
	ft_goto_prompt(input);
	tputs(tgetstr("cd", NULL), 1, &ft_intputchar);
}

void	ft_clear_screen(t_input *input)
{
	ft_clear(input);
	ft_bzero(input->line, INPUTSIZE);
	input->x = input->prompt;
	input->y = 0;
	input->len = 0;
}

void	ft_beginning_of_line(t_input *input)
{
	ft_goto_prompt(input);
	input->x = input->prompt;
	input->y = 0;
}

void	ft_end_of_line(t_input *input)
{
	while ((input->y * (input->width + 1) + input->x) < (input->prompt + input->len))
		ft_move_right(input);
}

int		ft_interpret(char *buff, t_input *input)
{
		(void)input;
//		printf("\nkey: %d %d %d %d %d %d\n", buff[0], buff[1], buff[2], buff[3], buff[4], buff[5]);
		//	printf("\nwidth:%d x:%d y:%d\n", input->width, input->x, input->y);

		
	if (buff[0] == 27 && buff[1] == 91 && buff[2] == 67)
		ft_move_right(input);

	if (buff[0] == 27 && buff[1] == 91 && buff[2] == 68)
		ft_move_left(input);

	if (buff[0] == 27 && buff[1] == 91 && buff[2] == 53 && buff[3] == 126)
		ft_move_up(input);

	if (buff[0] == 27 && buff[1] == 91 && buff[2] == 54 && buff[3] == 126)
		ft_move_down(input);

	if (buff[0] == 1 || (buff[0] == 27 && buff[1] == 91 && buff[2] == 72))
		ft_beginning_of_line(input);
	
	if (buff[0] == 5 || (buff[0] == 27 && buff[1] == 91 && buff[2] == 70))
		ft_end_of_line(input);

	if (buff[0] == '\n')
	{
		ft_clear(input);
		input->line = ft_strcat(input->line, "\n");
		ft_putstr(input->line);
		return (1);
	}

	if (buff[0] == 12)
		ft_clear_screen(input);

	if (ft_isprint(buff[0])) // buff entier est isprint
		ft_insertchar(buff, input);

	if (buff[0] == 127)
		ft_back_deletechar(input);	

	if (buff[0] == 4 && *input->line)
		ft_deletechar(input);

	if (buff[0] == 4 && !*input->line)
		ft_exit("exit", 1);

	return (0);
}
/*
 ** MOVE COMMANDS
 ** > --> move right ((buff[0] == 27 && buff[1] == 91 && buf[2] == 67)
 ** < --> move left ((buff[0] == 27 && buff[1] == 91 && buf[2] == 68)
 ** ctlr + a --> beginning-of-line (buff[0] == 1 || buff[0] == 27 && buff[1] == 91 && buff[2] == 72)
 ** ctlr + e --> end-of-line (buff[0] == 5 || buff[0] = 27 && buff[1] == 91 && buff[2] == 70)
 ** meta + f --> forward-word (buff[0] == 102)
 ** meta + b --> backward-word (buff[0] == 98)
 ** ctrl + l --> clear-screen (buff[0] == 12)
 ** EDITING COMMANDS
 ** ctrl + d --> delete-char/EOF (buff[0] = 4)
 **
 */
