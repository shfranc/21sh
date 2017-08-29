/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 11:28:24 by sfranc            #+#    #+#             */
/*   Updated: 2017/08/29 16:31:30 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# define CMD_NOT_FOUND 127

int		ft_execute(t_ast *ast);
int		ft_launch_simple_cmd(t_ast *ast);
char	*ft_get_path(char *cmd);

#endif
