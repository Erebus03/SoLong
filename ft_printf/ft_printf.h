/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araji <araji@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 17:00:07 by araji             #+#    #+#             */
/*   Updated: 2025/02/02 23:22:30 by araji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int	ft_printf(const char *format, ...);
int	put_c(int c);
int	put_s(char *s);
int	put_nb(int n);
int	put_addr(unsigned long n);
int	put_unb(unsigned int u_nb);
int	put_hex(unsigned int n, char mode);
int	input_is_valid(const char *s, char c);

#endif
