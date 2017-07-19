/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_editing.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/30 14:55:24 by sfranc            #+#    #+#             */
/*   Updated: 2017/07/19 15:13:31 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_EDITING_H
# define LINE_EDITING_H

# include <term.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <pwd.h>
# include <uuid/uuid.h>

# define	INPUTSIZE 4096

typedef struct	s_input
{
	char	*line;
	char	*tmp;
	int		width;
	int		len;
	int		x;
	int		y;
	int		prompt;
	char	*right;
	char	*left;
	char	*up;
	char	*down;
	char	*cr;
}				t_input;

/*
** READLINE
*/
void	ft_read_line(char **line, int len_prompt);

/*
** TERM
*/
void	ft_init_input_struct(t_input *input, int len_prompt);
void	ft_raw_term(void);
void	ft_canonic_term(void);
int		ft_interpret(char *buff, t_input *input);
int		ft_intputchar(int c);

/*
** CURSOR MOVES
*/
void	ft_move_left(t_input *input);
void	ft_move_right(t_input *input);
void	ft_move_up(t_input *input);
void	ft_move_down(t_input *input);

/*
** MOVE COMMANDS
*/
void	ft_beginning_of_line(t_input *input);
void	ft_end_of_line(t_input *input);
void	ft_jumpword_forward(t_input *input);
void	ft_jumpword_backward(t_input *input);

/*
** MOVES NOT LINKED TO USER COMMANDS
*/
void	ft_goto_begin(t_input *input);
void	ft_goto_prompt(t_input *input);
void	ft_goto_newpos(t_input *input, int cur_y);
void	ft_goto_lastpos(t_input *input);

/*
** BUFFER 
*/
void	ft_insertchar(char *buff, t_input *input);
void	ft_back_deletechar(t_input *input);
void	ft_deletechar(t_input *input);
void	ft_accept_line(t_input *input);

/*
** COPY N CUT
*/
void	ft_copy(t_input *input);
void	ft_cut(t_input *input);

/*
** SCREEN
*/
void	ft_clear(t_input *input);
void	ft_clear_screen(t_input *input);

/*
** PROMPT
*/
int		ft_display_prompt(void);

#endif
