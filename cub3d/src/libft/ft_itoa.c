/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchbouki <rchbouki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 22:08:26 by rchbouki          #+#    #+#             */
/*   Updated: 2024/01/21 22:29:49 by rchbouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	ft_size(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		len += 1;
		n *= -1;
	}
	while (n / 10 != 0)
	{
		len++;
		n /= 10;
	}
	len++;
	return (len);
}

static char	*ft_revstr(char *str, int size)
{
	int	rev;
	int	temp;
	int	i;

	i = 0;
	rev = size - 1;
	while (i < size / 2)
	{
		temp = *(str + i);
		*(str + i) = *(str + rev);
		*(str + rev) = temp;
		i++;
		rev--;
	}
	return (str);
}

static char	*ft_exc(char *str, int n)
{
	if (n == 0)
		ft_strlcpy(str, "0", 2);
	else if (n == -2147483648)
		ft_strlcpy(str, "-2147483648", 12);
	return (str);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*str;
	int		minus;

	i = 0;
	minus = 1;
	str = malloc(sizeof(char) * (ft_size(n) + 1));
	if (!str)
		return (NULL);
	if (n == 0 || n == (-2147483648))
		return (ft_exc(str, n));
	if (n < 0)
	{
		n *= -1;
		minus = -1;
	}
	while (n != 0)
	{
		str[i++] = (n % 10) + '0';
		n = n / 10;
	}
	if (minus == -1)
		str[i++] = '-';
	str[i] = '\0';
	return (ft_revstr(str, i));
}
