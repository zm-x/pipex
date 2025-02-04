/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mou <zael-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:44:39 by zael-mou          #+#    #+#             */
/*   Updated: 2025/02/03 16:12:00 by zael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <sys/wait.h>

void	here_doc(t_pipex *pipex, char **av)
{
	char	*str;

	if (pipex->ac != 6)
	{
		ft_printf("argument : here_doc LIMITER cmd cmd1 file\n");
		exit(22);
	}
	write(2, "heredoc> ", 10);
	str = get_next_line(0);
	if (!str)
		return ;
	while (!ft_strscmp(str, av[2]))
	{
		ft_putstr_fd(str, pipex->fd[1]);
		free(str);
		write(2, "heredoc> ", 10);
		str = get_next_line(0);
		if (!str)
			return ;
	}
	free(str);
	close(pipex->fd[1]);
}

int	check_command(char **av, char **env, t_pipex *pipex)
{
	int	i;
	int	take;
	int	eturn;

	i = 2;
	eturn = 0;
	if (ft_strncmp("here_doc", av[1]))
		i = 3;
	while (i < pipex->ac - 1)
	{
		take = check_path(pipex, env, av, i);
		if (take > -1)
			ft_printf("pipex: command not found: %s\n", av[i]);
		if (i == pipex->ac - 2 && take > -1)
			eturn = take;
		i++;
	}
	return (eturn);
}

int	middle_child(char **av, int ac, char **env, t_pipex *pipex)
{
	int	prev_fd;
	int	pid;

	prev_fd = pipex->fd[0];
	close(pipex->fd[1]);
	pipex->i = 3;
	while (pipex->i < ac - 2)
	{
		pipe(pipex->fd);
		pid = fork();
		if (pid == -1)
			return (perror("fork"), 1);
		if (pid == 0)
			child_two(av, env, pipex, prev_fd);
		close(pipex->fd[1]);
		close(prev_fd);
		prev_fd = pipex->fd[0];
		pipex->i++;
	}
	return (prev_fd);
}

int	close_all(int prev_fd, t_pipex *pipex, char **av, char **env)
{
	close(prev_fd);
	close(pipex->fd[0]);
	close(pipex->fd[1]);
	while (wait(NULL) > 0)
		;
	if (access(av[pipex->ac - 1], W_OK) == -1 || access(av[pipex->ac - 1],
			R_OK) == -1)
		return (1);
	return (check_command(av, env, pipex));
}

int	main(int ac, char **av, char *env[])
{
	t_pipex	pipex;

	if (ac < 5)
		return (ft_printf("argument : infile cmnd1 cmnd2 outfile\n"), 22);
	if (check_arg(av, ac, &pipex, 1))
		return (check_arg(av, ac, &pipex, 0));
	if (pipe(pipex.fd) == -1 || !*env)
		return (perror("pipe"), 1);
	if (ft_strncmp(av[1], "here_doc"))
		here_doc(&pipex, av);
	else
	{
		pipex.pid[0] = fork();
		if (pipex.pid[0] == 0)
			child(av, env, &pipex);
	}
	pipex.prev_fd = middle_child(av, ac, env, &pipex);
	pipex.pid[1] = fork();
	if (pipex.pid[1] == 0)
		parent(av, env, &pipex, pipex.prev_fd);
	waitpid(pipex.pid[1], &pipex.status, 0);
	pipex.out_exit = close_all(pipex.prev_fd, &pipex, av, env);
	if (pipex.out_exit > 0)
		return (pipex.out_exit);
	exit(WEXITSTATUS(pipex.status));
}
