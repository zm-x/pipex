/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_function2_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mou <zael-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:34:16 by zael-mou          #+#    #+#             */
/*   Updated: 2025/02/03 14:58:18 by zael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	check_cmnd(t_pipex *pipex, char *command)
{
	int		i;
	char	*str;

	i = 0;
	str = ft_stjoin(pipex->array[i++], command);
	while (access(str, X_OK | F_OK) == -1 && pipex->array[i])
	{
		free(str);
		str = ft_stjoin(pipex->array[i++], command);
	}
	if (access(str, X_OK | F_OK) == -1)
	{
		free(str);
		return (127);
	}
	free(str);
	return (-1);
}

int	check_path(t_pipex *pipex, char **env, char **av, int p)
{
	int		i;
	char	**test;
	int		take_return;

	i = 0;
	while (ft_strnstr(env[i], "PATH=") == NULL)
		i++;
	test = ft_split(av[p], ' ');
	pipex->full_path = ft_substr(env[i], 5, ft_strlen(env[i]) - 5);
	pipex->array = ft_split(pipex->full_path, ':');
	take_return = check_cmnd(pipex, test[0]);
	free_array(test);
	free_array(pipex->array);
	free(pipex->full_path);
	return (take_return);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
		free(array[i++]);
	free(array);
}

int	ft_strscmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	if (!s2[i] && !s1[i + 1])
		return (1);
	return (0);
}

int	ft_strncmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	if (s1[i] == '\0' && s2[i] == '\0')
		return (1);
	return (0);
}
