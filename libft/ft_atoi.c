/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 16:54:45 by araji             #+#    #+#             */
/*   Updated: 2024/11/17 00:47:43 by araji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *s)
{
	int	sign;
	int	result;

	sign = 1;
	result = 0;
	while (*s == 32 || (*s >= 9 && *s <= 13))
		s++;
	if (*s == 43 || *s == 45)
	{
		if (*s == 45)
			sign *= -1;
		s++;
	}
	while (ft_isdigit(*s))
	{
		result = (result * 10) + (*s - 48);
		s++;
	}
	return (result * sign);
}
