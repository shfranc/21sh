/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 18:47:15 by sfranc            #+#    #+#             */
/*   Updated: 2017/06/30 19:19:42 by sfranc           ###   ########.fr       */
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

static	int		ft_intputchar(int c)
{
	write(1, &c, 1);
	return (0);
}

void	ft_insertchar(char *buff, t_input *input)
{
	char	*begin;
	char	*end;

	begin = ft_strsub(input->line, 0, input->x);
	end = ft_strsub(input->line, input->x, ft_strlen(input->line) - ft_strlen(begin));
	ft_bzero(input->line, INPUTSIZE);
	input->line = ft_strcpy(input->line, begin);
	input->line = ft_strcat(input->line, buff);
	input->line = ft_strcat(input->line, end);
	input->len++;
	input->x = ft_strlen(input->line);
	free(begin);
	free(end);
}

void	ft_deletechar(t_input *input)
{
	char	*begin;
	char	*end;

	if (input->x > 0)
	{
		begin = ft_strsub(input->line, 0, input->x - 1);
		end = ft_strsub(input->line, input->x, ft_strlen(input->line) - ft_strlen(begin));
		ft_bzero(input->line, INPUTSIZE);
		input->line = ft_strcpy(input->line, begin);
		input->line = ft_strcat(input->line, end);
		input->len--;
		input->x = ft_strlen(input->line);
		free(begin);
		free(end);
	}
	else
		tputs(tgetstr("bl", NULL), 1, &ft_intputchar);
}

void	ft_move_right(t_input *input)
{
	if (input->x < input->len)
	{
		tputs(tgetstr("nd", NULL), 1, &ft_intputchar);
		input->x++;
	}
	else
		tputs(tgetstr("bl", NULL), 1, &ft_intputchar);
}

void	ft_move_left(t_input *input)
{
	if (input->x > 0)
	{
		tputs(tgetstr("le", NULL), 1, &ft_intputchar);
		input->x--;
	}
	else
		tputs(tgetstr("bl", NULL), 1, &ft_intputchar);
}

int		ft_interpret(char *buff, t_input *input)
{

	if (buff[0] == 27 && ft_strequ(&buff[1], "[C"))
		ft_move_right(input);

	if (buff[0] == 27 && ft_strequ(&buff[1], "[D"))
		ft_move_left(input);

	if (ft_isprint(buff[0]) || buff[0] == '\n')
	{
		ft_insertchar(buff, input);
		tputs(tgetstr("cr", NULL), 1, &ft_intputchar);	
		tputs(tgetstr("cd", NULL), 1, &ft_intputchar);	
		ft_putstr(input->line);
		if (buff[0] == '\n')
			return (1);
	}

	if (buff[0] == 127)
	{
		ft_deletechar(input);
		tputs(tgetstr("cr", NULL), 1, &ft_intputchar);	
		tputs(tgetstr("cd", NULL), 1, &ft_intputchar);	
		ft_putstr(input->line);
	}

	if (buff[0] == 4 && !*input->line)
		ft_exit("exit", 1);

	return (0);
}
