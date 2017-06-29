/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 18:47:15 by sfranc            #+#    #+#             */
/*   Updated: 2017/06/29 19:04:08 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

void	ft_init_term(void)
{
	const char		*term_type;
	int				ret;
	struct termios	sauv;
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

	ft_memmove(&sauv, &term, sizeof(term));
//	write(0, &sauv, sizeof(sauv));
//	write(0, &term, sizeof(term));

	term.c_lflag &= ~ (ICANON);
	term.c_lflag &= ~ (ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;

	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		ft_exit("Unable to unset canonic mode", 1);

}

/*static	int		ft_termput(int c)
{
	write(1, &c, 1);
	return (0);
}*/

void	ft_interpret(char *buff)
{
//	char	*arrow;
	char	*cm;
//	char	*ic;

	cm = tgetstr("cm", NULL);
//	ic = tgetstr("ic", NULL);

//	arrow = tgetstr("kl", NULL);
//	ft_putendl(arrow);
	write(0, buff, ft_strlen(buff));
//	tputs(buff, 1, &ft_termput);

//	if (buff[0] == 27)
	if (ft_strequ(buff + 1, "[D" ) )
		;
//		write(1, "c'est une fleche !\n", 19);
	else if (buff[0] == 4)
		ft_exit("exit", 1);
}
