#include "utils.h"
#include <stdio.h>
#include <limits.h>

char	*ft_itoa(unsigned int n) //free
{
	char			*str;
	unsigned int	tmp;
	int				len;

	len = 1;
	tmp = n;
	while (tmp /= 10)
		len++;

	str = malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len--)
	{
		str[len] = n % 10 + '0';
		n /= 10;
	}
	return (str);
}
