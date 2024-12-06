/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:00:18 by abonneau          #+#    #+#             */
/*   Updated: 2024/12/05 00:54:08 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdio.h>

static char    *return_next_line(char *buf, char *line)
{
    char   *next_line;
    char   *temp;
    
    if (!line)
    {
        temp = ft_strdup(buf);
        free(buf);
        return (temp);
    }
    next_line = ft_strjoin(line, buf);
    free(line);
    free(buf);
    return (next_line);
}

static int  method(char **remaining, char **line)
{
    char    *c;
    char    *temp;
    
    if (*remaining)
    {
        c = has_line_break(*remaining);
        if (c)
        {
            *c = '\0';
            *line = ft_strdup(*remaining);
            temp = ft_strdup(c + 1);
            free(*remaining);
            *remaining = temp;
            if (!temp)
                return (1);
            return (0);
        }
        *line = ft_strdup(*remaining);
        free(*remaining);
        *remaining = NULL;
    }
    return (0);
}

char	*get_next_line(int fd)
{
    static  char    *remaining;
    char	temp_buffer[BUFFER_SIZE + 1];
    char    *dynamic_buffer; 
    char	*preset_buffer;
    int		ret;
    char    *c;
    char    *temp;

    preset_buffer = NULL;
    dynamic_buffer = NULL;
    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    if (!method(&remaining, &preset_buffer))
    {
        if (remaining)
            return (preset_buffer);
    }
    else
        return (NULL);




    while (1)
    {
        ret = read(fd, temp_buffer, BUFFER_SIZE);
        if (ret <= 0)
            return (return_next_line(dynamic_buffer, preset_buffer));
        temp_buffer[ret] = '\0';
        if (!dynamic_buffer)
            dynamic_buffer = ft_strdup(temp_buffer);
        else
        {
            temp = ft_strjoin(dynamic_buffer, temp_buffer);
            free(dynamic_buffer);
            dynamic_buffer = temp;
        }
        c = has_line_break(dynamic_buffer);
        if (c)
        {
            *c = '\0';
            remaining = ft_strdup(c + 1);
            return (return_next_line(dynamic_buffer, preset_buffer));
        }
    }
    return (NULL);
}
