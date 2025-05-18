/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahja <abahja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 02:42:09 by henix             #+#    #+#             */
/*   Updated: 2024/11/05 11:41:19 by abahja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

int	function(char *str)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd(" : numeric argument required\n", 2);
	return (2);
}

int	ft_atoi(const char *str)
{
	size_t	i;
	int		sign;
	size_t	res;

	i = 0;
	sign = 1;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		res = res * 10 + (str[i] - '0');
		if (res >= LLONG_MAX)
			return (function((char *)str));
		i++;
	}
	return (res * sign);
}
