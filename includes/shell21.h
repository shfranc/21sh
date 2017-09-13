/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell21.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 12:35:19 by sfranc            #+#    #+#             */
/*   Updated: 2017/09/13 18:26:44 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL21_H
# define SHELL21_H

# include <stdio.h> // debug a suppr

# include <signal.h>

# include "libft.h"
# include "builtin.h"
# include "line_editing.h"
# include "lexer.h"
# include "parser.h"
# include "execute.h"

typedef struct	s_shell
{
	char		**env;
	int			ret_cmd;
}				t_shell;

t_shell *g_shell;

t_shell	*ft_init(char **env);

#endif
