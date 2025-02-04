/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mou <zael-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 09:52:24 by zael-mou          #+#    #+#             */
/*   Updated: 2025/01/29 14:37:00 by zael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (!str)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (str[i])
		write(2, &str[i++], 1);
	return (i);
}

int	checkchar(va_list args, const char str)
{
	int	i;

	i = 0;
	if (str == 's')
		i += ft_putstr(va_arg(args, char *));
	return (i);
}

int	check_arg(char **av, int ac, t_pipex *pipex, int p)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	pipex->ac = ac;
	while (j < ac - 1)
	{
		if (!av[j][0])
		{
			if (p)
				ft_printf("pipex: permession denied:\n");
			i = 126;
		}
		else
			check_spaces(av, j, p, &i);
		j++;
	}
	return (i);
}

void	check_spaces(char **av, int j, int p, int *i)
{
	int	index;

	index = 0;
	while (av[j][index] == ' ')
		index++;
	if (!av[j][index])
	{
		if (p)
			ft_printf("pipex: command not found:\n");
		*i = 127;
	}
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		i;

	if (!str)
		return (-1);
	i = 0;
	va_start(args, str);
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			if (*str == 'c' || *str == '%' || *str == 's' || *str == 'p')
				i += checkchar(args, *str);
		}
		else
			i += write(2, &(*str), 1);
		if (*str)
			str++;
	}
	va_end(args);
	return (i);
}
