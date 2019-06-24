/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printtab_nb.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judumay <judumay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 18:17:04 by judumay           #+#    #+#             */
/*   Updated: 2019/01/23 12:37:13 by judumay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_printtab_nb(int *tab, int len)
{
	int i;

	i = 0;
	if (!tab)
		return ;
	while (i < len)
	{
		ft_putnbr(tab[i++]);
		ft_putchar('\n');
	}
}
