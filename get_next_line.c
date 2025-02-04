/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mou <zael-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:33:30 by maddame           #+#    #+#             */
/*   Updated: 2025/02/03 15:12:48 by zael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ret_line(char **rst, char **line)
{
	char	*tmp;

	if (ft_strlen(*line) + 1 == ft_strlen(*rst))
	{
		free(*rst);
		tmp = *line;
		*line = ft_strjoin(tmp, "\n");
		free(tmp);
		*rst = NULL;
		return (*line);
	}
	tmp = *rst;
	*rst = ft_strjoin("", tmp + ft_strlen(*line) + 1);
	free(tmp);
	tmp = ft_strjoin(*line, "\n");
	return (free(*line), (tmp));
}

char	*return_line(char **rst, char **line, char **buffer)
{
	char	*tmp;

	if (ft_strlen(*line) + 1 == ft_strlen(*buffer))
	{
		(free(*buffer), tmp = *line);
		*line = ft_strjoin(tmp, "\n");
		return (free(tmp), (*line));
	}
	*rst = ft_strjoin("", *buffer + ft_strlen(*line) + 1);
	tmp = *line;
	*line = ft_strjoin(tmp, "\n");
	return (free(*buffer), free(tmp), *line);
}

char	*get_next_line(int fd)
{
	static char	*rst;
	char		*tmp;
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	tmp = NULL;
	while (1)
	{
		if (rst)
			return (check_static(fd, &rst, buffer, tmp));
		buffer = read_in_buf(fd, &rst, buffer);
		if (!buffer)
			return (NULL);
		line = ft_strdup(buffer);
		if (ft_strlen(buffer) - ft_strlen(line) > 0)
			return (return_line(&rst, &line, &buffer));
		else if (ft_strchr(line, '\n') == 0)
		{
			rst = ft_strjoin("", line);
			(free(line), free(buffer));
		}
	}
	return (line);
}

char	*check_static(int fd, char **rst, char *buffer, char *tmp)
{
	char	*line;
	ssize_t	b_r;

	while (1)
	{
		line = ft_strdup(*rst);
		if (ft_strlen(*rst) - ft_strlen(line) > 0)
			return (ret_line(rst, &line));
		else if (ft_strchr(line, '\n') == 0)
		{
			buffer = malloc(BUFFER_SIZE + 1);
			if (!buffer || (fd < 0 || BUFFER_SIZE <= 0))
				return (free(*rst), free(line), (NULL));
			b_r = read(fd, buffer, BUFFER_SIZE);
			buffer[b_r] = '\0';
			if (b_r == 0 && (ft_strlen(*rst) - ft_strlen(line)) == 0)
				return (free(*rst), free(buffer), *rst = NULL, (line));
			else if (b_r <= 0)
				return (free(buffer), free(line), free(*rst), (NULL));
			tmp = *rst;
			*rst = ft_strjoin(tmp, buffer);
			(free(tmp), free(line), free(buffer));
		}
	}
	return (0);
}

char	*read_in_buf(int fd, char **rst, char *buffer)
{
	ssize_t	b_r;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer || (fd < 0 || BUFFER_SIZE <= 0))
		return (free(*rst), NULL);
	b_r = read(fd, buffer, BUFFER_SIZE);
	if (b_r <= 0)
	{
		(free(buffer), free(*rst), *rst = NULL);
		return (NULL);
	}
	buffer[b_r] = '\0';
	return (buffer);
}
