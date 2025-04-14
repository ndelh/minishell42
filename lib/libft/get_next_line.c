/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agamay <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:19:52 by agamay            #+#    #+#             */
/*   Updated: 2024/11/04 17:18:34 by agamay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strlen_secu(const char *str)
{
	const char	*temp;

	if (!str)
		return (0);
	temp = str;
	while (*str)
		str++;
	return (str - temp);
}

static int	ft_istrchr(char *str, int c)
{
	char	*temp;

	if (!str)
		return (-1);
	temp = str;
	while (*str != c)
	{
		if (!*str)
			return (-1);
		str++;
	}
	return (str - temp);
}

char	*ft_strjoin_free(char *line, const char *n_line)
{
	char	*dest;
	char	*temp;
	size_t	size;

	if (!line && !n_line)
		return (NULL);
	size = ft_strlen_secu(line) + ft_strlen_secu(n_line);
	dest = (char *)malloc(sizeof(char) * size + 1);
	if (!dest)
		return (NULL);
	temp = dest;
	size = 0;
	while (line && *line && ++size)
		*temp++ = *line++;
	if (line)
		free(line - size);
	while (n_line && *n_line)
		*temp++ = *n_line++;
	*temp = '\0';
	return (dest);
}

static int	ft_cat(char **rest, int fd)
{
	char			*line;
	long long int	read_size;

	line = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	if (!line)
		return (0);
	read_size = read(fd, line, BUFFER_SIZE);
	if (read_size <= 0)
	{
		free(line);
		if (rest[fd] && !*rest[fd])
		{
			free(rest[fd]);
			rest[fd] = NULL;
		}
		return (read_size);
	}
	rest[fd] = ft_strjoin_free(rest[fd], line);
	free(line);
	return (read_size);
}

char	*get_next_line(int fd)
{
	static char		*rest[1024];
	char			*line;
	char			*temp;
	long long int	size;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	size = BUFFER_SIZE;
	while ((ft_istrchr(rest[fd], '\n') < 0 && size == BUFFER_SIZE)
		|| (ft_istrchr(rest[fd], '\0') < 0 && size < BUFFER_SIZE))
	{
		size = ft_cat(rest, fd);
		if (!rest[fd])
			return (NULL);
	}
	if (ft_istrchr(rest[fd], '\n') >= 0)
		line = ft_substr(rest[fd], 0, ft_istrchr(rest[fd], '\n') + 1);
	else
		line = ft_substr(rest[fd], 0, ft_istrchr(rest[fd], '\0'));
	size = ft_strlen_secu(line);
	temp = ft_substr(rest[fd], size, ft_strlen_secu(rest[fd]) - size);
	free(rest[fd]);
	rest[fd] = temp;
	return (line);
}
