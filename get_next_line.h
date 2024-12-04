
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#define BUFFER_SIZE 127

char	*get_next_line(int fd);
size_t 	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s);
char	*ft_strchr(const char *s, int c);
char	*has_line_break(char *s);

typedef struct s_gnl_buf
{
        char    temp_buffer[BUFFER_SIZE + 1];
		char    *dynamic_buffer;
		char	*preset_buffer;
		char	*static_buffer;
}       t_gnl_buf;
#endif