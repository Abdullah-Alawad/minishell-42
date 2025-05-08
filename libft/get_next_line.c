/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalawad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 14:36:06 by aalawad           #+#    #+#             */
/*   Updated: 2024/11/17 14:47:44 by aalawad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*set_next(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	line = ft_calloc((ft_strlen(buffer) - i + 1), sizeof(char));
	if (!line)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	ft_copy(line, buffer, i);
	return (line);
}

char	*set_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] != '\0' && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] != '\0' && buffer[i] == '\n')
	{
		line[i] = '\n';
	}
	return (line);
}

char	*set_static(char *buffer, char *buf, int byte_read)
{
	char	*temp;

	if (byte_read == -1)
	{
		free(buf);
		buf = NULL;
		free(buffer);
		return (NULL);
	}
	buf[byte_read] = '\0';
	temp = ft_strjoin(buffer, buf);
	if (!temp)
	{
		free(buf);
		buf = NULL;
		free(buffer);
		return (NULL);
	}
	free(buffer);
	return (temp);
}

char	*read_file(int fd, char *res)
{
	char	*buffer;
	int		byte_read;

	if (!res)
		res = ft_calloc(1, 1);
	if (!res)
		return (NULL);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
	{
		free(res);
		return (NULL);
	}
	byte_read = 1;
	while (byte_read > 0)
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		res = set_static(res, buffer, byte_read);
		if (!res)
			return (NULL);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	buffer = read_file(fd, buffer);
	if (!buffer)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	line = set_line(buffer);
	buffer = set_next(buffer);
	if (!line)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	return (line);
}
