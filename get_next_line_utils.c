/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddame <maddame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:35:23 by maddame           #+#    #+#             */
/*   Updated: 2024/11/24 17:18:49 by maddame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*ft_strdup(const char *s)
{
	size_t	i;
	size_t	len;
	char	*pt;

	if (!s)
		return (NULL);
	len = ft_strchr(s, '\n');
	if (len == 0)
		len = ft_strlen(s);
	pt = malloc(len + 1);
	if (pt == NULL)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '\n' && i < len)
	{
		pt[i] = s[i];
		i++;
	}
	pt[i] = '\0';
	return (pt);
}

int	ft_strchr(const char *s, int c)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if ((char)c == s[i])
			return (i);
		i++;
	}
	if (c == '\0')
		return (i);
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*pt;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	pt = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (pt == NULL)
		return (NULL);
	i = 0;
	while (*s1)
		pt[i++] = *s1++;
	while (*s2)
		pt[i++] = *s2++;
	pt[i] = '\0';
	return (pt);
}
