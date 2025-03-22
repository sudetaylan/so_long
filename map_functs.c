/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_functs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: staylan <staylan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:31:56 by staylan           #+#    #+#             */
/*   Updated: 2025/03/22 20:54:07 by staylan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	map_rowlen(char *row)
{
	unsigned int	i;

	i = 0;
	while (row[i])
		i++;
	return (i);
}

int	arg_check(char *str, char *p)
{
	int	i;

	i = map_rowlen(str) - 4;
	while (str[i])
	{
		if (str[i++] != *p++)
			return (0);
	}
	return (1);
}

static void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int nb)
{
	if (nb == -2147483648)
	{
		write(1, "-2147483648", 11);
	}
	else if (nb < 0)
	{
		ft_putchar('-');
		nb = (-nb);
		ft_putnbr(nb);
	}
	else if (nb >= 10)
	{
		ft_putnbr(nb / 10);
		ft_putnbr(nb % 10);
	}
	else
		ft_putchar(nb + '0');
}
