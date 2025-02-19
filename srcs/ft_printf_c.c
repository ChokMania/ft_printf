/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_c.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmauffr <anmauffr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 12:03:58 by anmauffr          #+#    #+#             */
/*   Updated: 2019/01/23 12:04:01 by anmauffr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

static t_printf		*ft_printf_c_champ(t_printf *p)
{
	size_t		tmp;
	char		*str;
	char		*buf;

	if (p->champ != -1 && (size_t)p->champ > 1 && (tmp = (size_t)p->champ - 1))
	{
		if (!(str = ft_strnew(tmp))
			&& (p->error = -1))
			return (p);
		if (p->flags->zero && !p->flags->less)
			str = ft_strfill(str, '0', tmp);
		else
			str = ft_strfill(str, ' ', tmp);
		if (p->flags->less)
			buf = ft_strjoin(p->conv_ret, str);
		else
			buf = ft_strjoin(str, p->conv_ret);
		if (!buf && (p->error = -1))
			return (p);
		ft_strdel(&p->conv_ret);
		ft_strdel(&str);
		p->conv_ret = buf;
	}
	return (p);
}

t_printf			*ft_printf_c(t_printf *p)
{
	__int8_t	arg;

	if (!(p->conv == FT_PRINTF_C && p->modifier != FT_PRINTF_L))
		return (p);
	arg = (__int8_t)va_arg(p->ap, __int32_t);
	if (!(p->conv_ret = ft_strnew(1))
		&& (p->error = -1))
		return (p);
	p->conv_ret[0] = arg;
	p = ft_printf_c_champ(p);
	if (p->error)
		return (p);
	if (!p->flags->less)
		ft_putstr(p->conv_ret);
	if (!arg && ++p->ret)
		ft_putchar(arg);
	if (p->flags->less)
		ft_putstr(p->conv_ret);
	p->ret += ft_strlen(p->conv_ret);
	return (p);
}
