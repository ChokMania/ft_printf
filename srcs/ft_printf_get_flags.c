/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_get_flags.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmauffr <anmauffr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 12:04:56 by anmauffr          #+#    #+#             */
/*   Updated: 2019/01/23 12:04:57 by anmauffr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

void			ft_printf_get_flag(t_printf *p, const char *format)
{
	if (format[p->index] == '#')
		p->flags->hash = 1;
	else if (format[p->index] == '0')
		p->flags->zero = 1;
	else if (format[p->index] == '-')
		p->flags->less = 1;
	else if (format[p->index] == ' ')
		p->flags->space = 1;
	else if (format[p->index] == '+')
		p->flags->plus = 1;
	++p->index;
}
