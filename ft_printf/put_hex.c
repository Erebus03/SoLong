/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_hex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araji <araji@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 18:01:21 by araji             #+#    #+#             */
/*   Updated: 2024/12/13 19:07:06 by araji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	put_hex(unsigned int n, char mode)
{
	char	final_res[8];
	char	*hex;
	int		len;
	int		i;

	len = 0;
	if (n == 0)
		return (write(1, "0", 1));
	if (mode == 'x')
		hex = "0123456789abcdef";
	else
		hex = "0123456789ABCDEF";
	i = 7;
	while (n > 0)
	{
		final_res[i--] = hex[n % 16];
		n = n / 16;
	}
	i++;
	while (i < 8)
	{
		write(1, &final_res[i++], 1);
		len++;
	}
	return (len);
}
