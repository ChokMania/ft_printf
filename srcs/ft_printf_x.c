/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_x.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judumay <judumay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 12:05:46 by anmauffr          #+#    #+#             */
/*   Updated: 2019/01/25 12:44:02 by judumay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

static __uint64_t	ft_printf_x_get_arg(t_printf *p)
{
	__uint64_t	ret;

	ret = 0;
	if (p->modifier == FT_PRINTF_NO_MODIFIERS)
		ret = va_arg(p->ap, __uint32_t);
	else if (p->modifier == FT_PRINTF_H)
		ret = (__uint16_t)va_arg(p->ap, __uint32_t);
	else if (p->modifier == FT_PRINTF_HH)
		ret = (__uint8_t)va_arg(p->ap, __uint32_t);
	else if (p->modifier == FT_PRINTF_L)
		ret = va_arg(p->ap, unsigned long);
	else if (p->modifier == FT_PRINTF_LL)
		ret = va_arg(p->ap, __uint64_t);
	return (ret);
}

static t_printf		*ft_printf_x_precision(t_printf *p, __uint64_t tmp)
{
	size_t		tmp2;
	char		*str;
	char		*buf;

	if (p->precision == 0 && !tmp)
	{
		str = ft_strnew(0);
		ft_strdel(&p->conv_ret);
		p->conv_ret = str;
	}
	else if (p->precision != -1 && (size_t)p->precision > ft_strlen(p->conv_ret)
		&& (tmp2 = (size_t)p->precision - ft_strlen(p->conv_ret)))
	{
		if (!(str = ft_strnew(tmp2))
			&& (p->error = -1))
			return (p);
		str = ft_strfill(str, '0', tmp2);
		buf = ft_strjoin(str, p->conv_ret);
		if (!buf && (p->error = -1))
			return (p);
		ft_strdel(&p->conv_ret);
		ft_strdel(&str);
		p->conv_ret = buf;
	}
	return (p);
}

static t_printf		*ft_printf_x_champ(t_printf *p)
{
	int			tmp;
	char		*str;
	char		*buf;

	if (p->champ != -1 && (size_t)p->champ > ft_strlen(p->conv_ret)
		&& (tmp = (size_t)p->champ - ft_strlen(p->conv_ret)))
	{
		if (p->flags->zero && p->precision == -1 && !p->flags->less
			&& p->flags->hash && p->conv_ret[0] != '0')
			tmp = tmp < 2 ? 0 : tmp - 2;
		str = ft_strnew(tmp);
		if (p->flags->zero && p->precision == -1 && !p->flags->less)
			str = ft_strfill(str, '0', tmp);
		else
			str = ft_strfill(str, ' ', tmp);
		if (p->flags->less)
			buf = ft_strjoin(p->conv_ret, str);
		else
			buf = ft_strjoin(str, p->conv_ret);
		ft_strdel(&p->conv_ret);
		ft_strdel(&str);
		p->conv_ret = buf;
	}
	return (p);
}

static t_printf		*ft_printf_x_flags(t_printf *p, __uint64_t tmp)
{
	char		*str;
	char		*buf;

	str = NULL;
	buf = NULL;
	if (p->flags->hash && tmp)
	{
		if ((!(str = ft_strnew(2)))
			&& (p->error = -1))
			return (p);
		str[0] = '0';
		str[1] = 'x';
		buf = ft_strjoin(str, p->conv_ret);
		ft_strdel(&p->conv_ret);
		p->conv_ret = buf;
		ft_strdel(&str);
	}
	return (p);
}

t_printf			*ft_printf_x(t_printf *p)
{
	__uint64_t	tmp;

	if (!(p->conv == FT_PRINTF_X || p->conv == FT_PRINTF_XX))
		return (p);
	p->conv_ret = ft_lltoabase_unsigned(
		(tmp = ft_printf_x_get_arg(p)), 16);
	p = ft_printf_x_precision(p, tmp);
	if (p->error)
		return (p);
	if (!(p->flags->zero && p->precision == -1 && !p->flags->less))
		p = ft_printf_x_flags(p, tmp);
	if (p->error)
		return (p);
	p = ft_printf_x_champ(p);
	if (p->error)
		return (p);
	if (p->flags->zero && p->precision == -1 && !p->flags->less)
		p = ft_printf_x_flags(p, tmp);
	if (p->error)
		return (p);
	if (p->conv == FT_PRINTF_XX)
		p->conv_ret = ft_strtoupper_leakless(p->conv_ret);
	ft_putstr(p->conv_ret);
	p->ret += ft_strlen(p->conv_ret);
	return (p);
}
