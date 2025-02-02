/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_addr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araji <araji@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 18:05:30 by araji             #+#    #+#             */
/*   Updated: 2024/12/17 18:56:01 by araji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	put_addr(unsigned long n)
{
	char	final_res[16];
	char	*hex;
	int		len;
	int		i;

	if (n == 0)
		return (write(1, "(nil)", 5));
	write(1, "0x", 2);
	len = 2;
	hex = "0123456789abcdef";
	i = 15;
	while (n > 0)
	{
		final_res[i--] = hex[n % 16];
		n = n / 16;
	}
	i++;
	while (i < 16)
	{
		write(1, &final_res[i++], 1);
		len++;
	}
	return (len);
}
