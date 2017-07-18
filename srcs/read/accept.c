/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   accept.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/17 18:45:04 by sfranc            #+#    #+#             */
/*   Updated: 2017/07/17 18:45:26 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

void	ft_accept_line(t_input *input)
{
		ft_clear(input);
		input->line = ft_strcat(input->line, "\n");
		ft_putstr(input->line);
}
