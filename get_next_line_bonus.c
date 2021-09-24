/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostal- <acostal-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 20:03:55 by acostal-          #+#    #+#             */
/*   Updated: 2021/09/23 20:03:58 by acostal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlcat(char *dest, const char *src,
					 size_t dstsize)
{
	size_t	i;
	size_t	dst_len;
	size_t	src_len;
	size_t	dst_len_og;

	i = 0;
	dst_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	dst_len_og = ft_strlen(dest);
	if (dstsize == 0)
		return (src_len);
	if (dstsize < dst_len_og)
		return (src_len + dstsize);
	while (dst_len < dstsize - 1 && src[i] != '\0')
	{
		dest[dst_len] = src[i];
		i++;
		dst_len++;
	}
	dest[dst_len] = '\0';
	return (dst_len_og + src_len);
}

static char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	return ((char *) '\0');
}

static void	read_file(int fd, char *buffer, char **file, ssize_t r_bytes)
{
	char	*tmp_str;

	tmp_str = NULL;
	while (r_bytes > 0)
	{
		buffer[r_bytes] = '\0';
		if (!file[fd])
			file[fd] = ft_strdup("");
		tmp_str = ft_strjoin(file[fd], buffer);
		free(file[fd]);
		file[fd] = tmp_str;
		if (ft_strchr(buffer, '\n'))
			break ;
		r_bytes = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
}

static char	*return_next_line(char **s)
{
	char	*output_str;
	char	*tmp_str;
	size_t	len;

	len = 0;
	output_str = NULL;
	while ((*s)[len] != '\n' && (*s)[len])
		len++;
	if ((*s)[len] == '\n')
	{
		output_str = ft_substr(*s, 0, len + 1);
		tmp_str = ft_strdup(*s + len + 1);
		free(*s);
		*s = tmp_str;
		if (!**s)
		{
			free(*s);
			*s = NULL;
		}
		return (output_str);
	}
	output_str = ft_strdup(*s);
	free(*s);
	*s = NULL;
	return (output_str);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*file[MAX_FD];
	ssize_t		r_bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	r_bytes = read(fd, buffer, BUFFER_SIZE);
	read_file(fd, buffer, file, r_bytes);
	if (r_bytes < 0)
		return (NULL);
	if (!r_bytes && (!file[fd] || !*file[fd]))
		return (NULL);
	return (return_next_line(&file[fd]));
}
