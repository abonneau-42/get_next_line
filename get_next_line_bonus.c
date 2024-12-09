/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 17:19:07 by abonneau          #+#    #+#             */
/*   Updated: 2024/12/09 20:23:10 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void	*handle_free(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
	return (NULL);
}

static int	has_join_remaining(char **remaining, char *buffer)
{
	char	*tmp;

	tmp = ft_strjoin(*remaining, buffer);
	handle_free(remaining);
	if (!tmp)
		return (0);
	*remaining = tmp;
	return (1);
}

static char	*handle_line(char **remaining)
{
	char	*tmp;
	char	*substr;
	char	*end_of_line;

	tmp = NULL;
	substr = NULL;
	end_of_line = NULL;
	if (!**remaining)
		return (handle_free(remaining));
	end_of_line = get_line_break(*remaining);
	if (end_of_line)
	{
		substr = ft_strndup(*remaining, end_of_line - *remaining + 1);
		if (!substr)
			return (handle_free(remaining));
		tmp = ft_strdup(end_of_line + 1);
		handle_free(remaining);
		if (!tmp)
			return (handle_free(&substr));
		*remaining = tmp;
		return (substr);
	}
	substr = ft_strdup(*remaining);
	handle_free(remaining);
	return (substr);
}

char	*get_next_line(int fd)
{
	static char	*remaining[OPEN_MAX];
	char		buffer[BUFFER_SIZE + 1];
	int			read_bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!remaining[fd])
		remaining[fd] = ft_strdup("");
	if (!remaining[fd])
		return (NULL);
	while (get_line_break(remaining[fd]) == NULL)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == 0)
			break ;
		if (read_bytes == -1)
			return (handle_free(&remaining[fd]));
		buffer[read_bytes] = '\0';
		if (!has_join_remaining(&remaining[fd], buffer))
			return (NULL);
	}
	return (handle_line(&remaining[fd]));
}
