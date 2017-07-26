/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/26 18:03:46 by sfranc            #+#    #+#             */
/*   Updated: 2017/07/26 18:04:21 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

int		ft_goto_next_quote(char *line, char quote)
{
	int	len;

	len = 1;
	while (*(line + len) && *(line + len) != quote)
		len++;
	return (len);
}

int		ft_goto_next_quote_withescape(char *line, char quote)
{
	int	len;

	len = 1;
	while (*(line + len) && *(line + len) != quote)
	{
		if (*(line + len) == '\\')
			len++;
		len++;
	}
	return (len);
}
