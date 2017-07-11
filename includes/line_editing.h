/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_editing.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/30 14:55:24 by sfranc            #+#    #+#             */
/*   Updated: 2017/07/11 18:15:00 by sfranc           ###   ########.fr       */
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
	int		prompt;
}				t_input;

/*
** TERM
*/
void	ft_raw_term(void);
void	ft_canonic_term(void);
int		ft_interpret(char *buff, t_input *input);
int		ft_intputchar(int c);

/*
** CURSOR
*/
void	ft_increase_cursorpos(t_input *input);
void	ft_decrease_cursorpos(t_input *input);
void	ft_move_left(t_input *input);
void	ft_move_right(t_input *input);
void	ft_goto_begin(t_input *input);
void	ft_goto_prompt(t_input *input);
void	ft_goto_newpos(t_input *input, int cur_y);
/*
** BUFFER
*/
void	ft_clear(t_input *input);
void	ft_insertchar(char *buff, t_input *input);
void	ft_deletechar(t_input *input);

/*
** PROMPT
*/
int		ft_display_prompt(void);

#endif
