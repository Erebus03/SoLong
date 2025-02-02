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

#include "ft_printf.h"

void	output(char input, va_list args, int *count)
{
	int	len;

	len = 0;
	if (input == 'c')
		len = put_c(va_arg(args, int));
	else if (input == 's')
		len = put_s(va_arg(args, char *));
	else if (input == 'p')
		len = put_addr(va_arg(args, unsigned long));
	else if (input == 'd' || input == 'i')
		len = put_nb(va_arg(args, int));
	else if (input == 'u')
		len = put_unb(va_arg(args, unsigned int));
	else if (input == 'x')
		len = put_hex(va_arg(args, unsigned int), 'x');
	else if (input == 'X')
		len = put_hex(va_arg(args, int), 'X');
	else if (input == '%')
		len = put_c('%');
	*count += len;
}

int	ft_printf(const char *input, ...)
{
	const char	*valid_input;
	va_list		args;
	int			count;
	int			i;

	i = 0;
	count = 0;
	if (input == NULL)
		return (-1);
	valid_input = "cspdiuxX%";
	va_start(args, input);
	while (input[i])
	{
		if (input[i] == '%' && input[i + 1] == '\0')
			return (-1);
		else if (input[i] == '%' && input_is_valid(valid_input, input[i + 1]))
		{
			output(input[++i], args, &count);
			i++;
		}
		else
			count += put_c(input[i++]);
	}
	va_end(args);
	return (count);
}
