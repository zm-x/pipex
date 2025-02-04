/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mou <zael-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:34:54 by zael-mou          #+#    #+#             */
/*   Updated: 2025/02/03 16:14:09 by zael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "get_next_line.h"
# include <fcntl.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct pipex_s
{
	char	*full_path;
	char	**array;
	char	*last_path;
	char	**path;
	char	*command;
	int		fd[2];
	int		ac;
	int		i;
	int		out_exit;
	pid_t	pid[2];
	int		prev_fd;
	int		status;
}			t_pipex;

char		**ft_split(char const *s, char c);
char		*find_path(t_pipex *pipex, char *command, int p[2]);
char		*ft_strnstr(char *big, char *little);
int			check_cmnd(t_pipex *pipex, char *command);
int			ft_stlen(char *s);
void		get_path(char **env, t_pipex *pipex, char **av, int p[2]);
void		ft_putstr_fd(char *s, int fd);
int			parent(char **av, char **env, t_pipex *pipex, int prev_fd);
int			child_two(char **av, char **env, t_pipex *pipex, int prev_fd);
int			ft_printf(const char *str, ...);
int			child(char **av, char **env, t_pipex *pipex);
int			check_path(t_pipex *pipex, char **env, char **av, int p);
char		*ft_substr(char *s, unsigned int start, int len);
char		*ft_stjoin(char *s1, char *s2);
void		free_array(char **array);
void		check_spaces(char **av, int j, int p, int *i);
int			ft_strscmp(char *s1, char *s2);
int			ft_strncmp(char *s1, char *s2);
int			check_arg(char **av, int ac, t_pipex *pipex, int p);

#endif
