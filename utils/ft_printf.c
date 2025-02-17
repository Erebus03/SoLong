/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araji <araji@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 17:07:31 by araji             #+#    #+#             */
/*   Updated: 2024/12/21 15:34:54 by araji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	put_nb(int n)
{
	int		len;
	char	c;

	len = 0;
	if (n == -2147483648)
		return (write(1, "-2147483648", 11));
	if (n < 0)
	{
		len += write(1, "-", 1);
		n = -n;
	}
	if (n > 9)
	{
		len += put_nb(n / 10);
		len += put_nb(n % 10);
	}
	else
	{
		c = n + '0';
		len += write(1, &c, 1);
	}
	return (len);
}

int	put_s(char *s)
{
	int	len;

	len = 0;
	if (s == NULL)
		return (write(1, "(null)", 6));
	while (*s)
	{
		len += write(1, s, 1);
		s++;
	}
	return (len);
}

int	ft_printf(const char *input, ...)
{
	va_list		args;
	int			count;
	int			i;

	i = 0;
	count = 0;
	if (input == NULL)
		return (-1);
	va_start(args, input);
	while (input[i])
	{
		if (input[i] == '%' && input[i + 1] == '\0')
			return (-1);
		else if (input[i] == '%')
		{
			++i;
			if (input[i] == 's')
				count += put_s(va_arg(args, char *));
			else if (input[i] == 'd' || input[i] == 'i')
				count += put_nb(va_arg(args, int));
		}
		else
			count += write(1, &input[i], 1);
		i++;
	}
	va_end(args);
	return (count);
}
