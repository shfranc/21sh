/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_editing.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/30 14:55:24 by sfranc            #+#    #+#             */
/*   Updated: 2017/06/30 19:19:47 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_EDITING_H
# define LINE_EDITING_H

# include <term.h>
# include <sys/ioctl.h>

# define INPUTSIZE 2048

typedef struct	s_input
{
	char	*line;
	int		width;
	int		len;
	int		x;
	int		y;
}				t_input;

/*
** TERM
*/
void	ft_raw_term(void);
void	ft_canonic_term(void);
int		ft_interpret(char *buff, t_input *input);

#endif
