/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev_leakless.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judumay <judumay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 13:29:19 by judumay           #+#    #+#             */
/*   Updated: 2019/01/25 13:29:20 by judumay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev_leakless(char *s)
{
	char		*dup;
	char		tmp;
	size_t		start;
	size_t		end;

	dup = ft_strdup(s);
	start = 0;
	end = ft_strlen(dup) - 1;
	while (dup && dup[start] && start < end)
	{
		tmp = dup[start];
		dup[start++] = dup[end];
		dup[end--] = tmp;
	}
	ft_memdel((void**)&s);
	return (dup);
}
