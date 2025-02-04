/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_function_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mou <zael-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:20:43 by zael-mou          #+#    #+#             */
/*   Updated: 2025/02/03 14:20:52 by zael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_stlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strnstr(char *big, char *little)
{
	int	j;

	j = 0;
	if (!big)
		return (NULL);
	while (little[j] == big[j])
		j++;
	if (!little[j])
		return (big);
	return (NULL);
}

char	*ft_substr(char *s, unsigned int start, int len)
{
	char	*str;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	while (i < len && s[start])
	{
		str[i++] = s[start++];
	}
	str[i] = '\0';
	return (str);
}

char	*ft_stjoin(char *s1, char *s2)
{
	int		i;
	char	*str;
	int		j;

	if (!s1 && !s2)
		return (NULL);
	i = 0;
	if (!s1)
		return ((char *)s2);
	else if (!s2)
		return ((char *)s1);
	str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
	if (!str)
		return (NULL);
	j = 0;
	while (s1[j])
		str[i++] = s1[j++];
	str[i++] = '/';
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}

char	*find_path(t_pipex *pipex, char *command, int p[2])
{
	int		fd;
	int		i;
	char	*str;

	i = 0;
	p[1] = i;
	str = ft_stjoin(pipex->array[i++], command);
	while (access(str, X_OK) == -1 && pipex->array[i])
	{
		free(str);
		str = ft_stjoin(pipex->array[i++], command);
	}
	if (access(str, X_OK) == -1)
	{
		free(str);
		exit(EXIT_FAILURE);
	}
	free(str);
	return (ft_stjoin(pipex->array[i - 1], command));
}
