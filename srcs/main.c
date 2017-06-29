/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 12:49:58 by sfranc            #+#    #+#             */
/*   Updated: 2017/06/29 19:04:10 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

int		main(void)
{
	char buff[3];

//	intercepter les signaux avant les termcaps
	ft_init_term();
	while (1)
	{
		ft_bzero(buff, 3);
		read(0, buff, 3);
		ft_interpret(buff);
	}
	return (0);
}
