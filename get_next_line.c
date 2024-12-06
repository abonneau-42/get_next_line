/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 17:19:07 by abonneau          #+#    #+#             */
/*   Updated: 2024/12/06 19:16:55 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char *handle_line(char **remaining)
{
	char *tmp;
	char *substr;
	char *end_of_line;

	if (!**remaining)
	{
		free(*remaining);
		return (NULL);
	}
	end_of_line = get_line_break(*remaining);
	if (end_of_line)
	{
		substr = ft_strndup(*remaining, end_of_line - *remaining + 1);
		tmp = ft_strdup(end_of_line + 1);
		free(*remaining);
		if (!tmp)
			return (NULL);
		*remaining = tmp;
		return (substr);
	}
	substr = ft_strdup(*remaining);
	free(*remaining);
	*remaining = NULL;
	return (substr);
}

char *get_next_line(int fd)
{
	static char *remaining;
	char buffer[BUFFER_SIZE + 1];
	char *tmp;
	int read_bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!remaining)
		remaining = ft_strdup("");
	if (!remaining)
		return (NULL);
	while (get_line_break(remaining) == NULL)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes <= 0)
		    break;
		buffer[read_bytes] = '\0';
		tmp = ft_strjoin(remaining, buffer);
		free(remaining);
		if (!tmp)
			return (NULL);
		remaining = tmp;
	}
	return (handle_line(&remaining));
}
