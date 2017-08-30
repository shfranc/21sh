/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell21.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 12:35:19 by sfranc            #+#    #+#             */
/*   Updated: 2017/08/30 19:11:14 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL21_H
# define SHELL21_H

# include <stdio.h> // debug a suppr


# include <errno.h>
# include <sys/stat.h> 
# include <signal.h>

# include "libft.h"
# include "builtin.h"
# include "line_editing.h"
# include "lexer.h"
# include "parser.h"
# include "execute.h"

char	**g_env;

#endif
