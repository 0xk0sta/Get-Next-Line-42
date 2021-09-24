/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostal- <acostal-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 12:03:59 by acostal-          #+#    #+#             */
/*   Updated: 2021/09/24 12:04:01 by acostal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strdup(const char *src)
{
	char	*dst;
	int		size;
	int		index;

	index = 0;
	size = ft_strlen(src);
	dst = malloc(sizeof(char) * (size + 1));
	if (dst == NULL)
		return (0);
	while (src[index])
	{
		dst[index] = src[index];
		index++;
	}
	dst[index] = '\0';
	return (dst);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	int		total_len;
	int		index;

	if (!s1 || !s2)
		return (NULL);
	total_len = ft_strlen(s1) + ft_strlen(s2) + 1;
	index = 0;
	new_str = malloc(sizeof(char) * total_len);
	if (!new_str)
		return (NULL);
	while (s1[index])
	{
		new_str[index] = s1[index];
		index++;
	}
	new_str[index] = '\0';
	ft_strlcat(new_str, s2, total_len);
	return (new_str);
}

size_t	ft_strlcpy(char *dest, const char *src,
					 size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	while (i < dstsize - 1 && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (ft_strlen(src));
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new_str;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < len)
		len = ft_strlen(s);
	new_str = malloc((sizeof(char) * len) + 1);
	if (start > ft_strlen(s))
	{
		*new_str = 0;
		return (new_str);
	}
	if (new_str == NULL)
		return (NULL);
	if (start <= ft_strlen(s))
		ft_strlcpy(new_str, s + start, len + 1);
	return (new_str);
}
