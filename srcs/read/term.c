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

int		ft_interpret(char *buff, t_input *input)
{
	char	*cap;
	int		i;

	if (buff[0] == 27)
		write(1, "c'est une fleche !", 18);
	else if (buff[0] == 4)
		ft_exit("exit", 1);
	else if (buff[0] == '\n')
		return (1);
	else
	{
		input->x += 1;
		if (input->x == input->width + 1)
		{
			input->y += 1;
			input->x = 1;
		}
		ft_strcat(input->line, buff);
	}

	// se deplacer en colonne 1
	cap = tgetstr("le", NULL);
	i = input->x;
	while (i--)
		tputs(cap, 1, &ft_intputchar);

	// se deplacer en ligne 1
	cap = tgetstr("up", NULL);
	i = input->y;
	while (--i)
		tputs(cap, 1, &ft_intputchar);

	cap = tgetstr("cd", NULL);
	tputs(cap, 1, &ft_intputchar);	
	
	printf("x:%d y:%d\n", input->x, input->y);
	ft_putstr(input->line);
	return (0);
}
