/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_function3_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mou <zael-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 11:30:17 by zael-mou          #+#    #+#             */
/*   Updated: 2025/02/03 10:42:01 by zael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	get_path(char **env, t_pipex *pipex, char **av, int p[2])
{
	int	i;

	i = 0;
	while (ft_strnstr(env[i], "PATH=") == NULL && env[i])
		i++;
	if (!env[i])
		exit(1);
	pipex->path = ft_split(av[p[0]], ' ');
	pipex->full_path = ft_substr(env[i], 5, ft_strlen(env[i]) - 5);
	pipex->array = ft_split(pipex->full_path, ':');
	pipex->command = find_path(pipex, pipex->path[0], p);
	execve(pipex->command, &(pipex->path[0]), env);
	exit(1);
}

int	child(char **av, char **env, t_pipex *pipex)
{
	int	fd[2];
	int	p[2];
	int	take;

	p[0] = 2;
	p[1] = 1;
	take = check_path(pipex, env, av, 2);
	if (take > -1)
		exit(0);
	fd[1] = open(av[1], O_RDONLY);
	if (fd[1] == -1)
		return (perror(av[1]), 0);
	dup2(fd[1], 0);
	dup2(pipex->fd[1], 1);
	close(pipex->fd[1]);
	close(pipex->fd[0]);
	close(fd[1]);
	get_path(env, pipex, av, p);
	return (0);
}

int	child_two(char **av, char **env, t_pipex *pipex, int prev_fd)
{
	int	p[2];
	int	take;

	p[0] = pipex->i;
	p[1] = 1;
	take = check_path(pipex, env, av, pipex->i);
	if (take > -1)
		exit(0);
	dup2(prev_fd, 0);
	dup2(pipex->fd[1], 1);
	close(prev_fd);
	close(pipex->fd[0]);
	close(pipex->fd[1]);
	get_path(env, pipex, av, p);
	return (0);
}

int	parent(char **av, char **env, t_pipex *pipex, int prev_fd)
{
	int	fd[2];
	int	p[2];
	int	take;

	p[0] = pipex->ac - 2;
	p[1] = 0;
	if (ft_strncmp(av[1], "here_doc"))
		fd[0] = open(av[pipex->ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd[0] = open(av[pipex->ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd[0] == -1)
		return (perror("pipex"), 1);
	take = check_path(pipex, env, av, pipex->ac - 2);
	if (take > -1)
		exit(0);
	dup2(prev_fd, 0);
	dup2(fd[0], 1);
	close(prev_fd);
	close(pipex->fd[0]);
	close(pipex->fd[1]);
	close(fd[0]);
	get_path(env, pipex, av, p);
	return (0);
}

void	ft_putstr_fd(char *s, int fd)
{
	unsigned int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
		write(fd, &s[i++], 1);
}
