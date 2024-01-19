/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchbouki <rchbouki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:29:11 by rchbouki          #+#    #+#             */
/*   Updated: 2024/01/19 15:31:44 by rchbouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	ft_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\f'
		|| str[i] == '\r' || str[i] == '\v')
		i++;
	return (i);
}

static int	ft_isdigit(int c)
{
	if ((c == 26) || (c < 48) || (c > 57))
		return (0);
	return (1);
}

int	ft_atoi(char *str)
{
	char	*s;
	int		i;
	int		minus;
	int		res;

	s = (char *)(str);
	i = ft_spaces(s);
	res = 0;
	minus = 1;
	if (s[i] == '-' && ft_isdigit(s[i + 1]) == 1)
	{
		i++;
		minus = -1;
	}
	if (s[i] == '+' && ft_isdigit(s[i + 1]) == 1)
		i++;
	while ((s[i] >= '0') && (s[i] <= '9'))
	{
		res = res * 10 + s[i] - '0';
		i++;
	}
	return (res * minus);
}
