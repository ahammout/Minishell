/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 15:06:22 by ahammout          #+#    #+#             */
/*   Updated: 2023/03/16 00:46:25 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*next_line(char **str_remainder)
{
	size_t	f;
	char	*line;
	char	*to_free; 

	to_free = *str_remainder;
	f = 0;
	while ((*str_remainder)[f] != '\n' && (*str_remainder)[f] != '\0')
		f++;
	if (fft_strchr(*str_remainder, '\n'))
	{
		line = fft_substr(*str_remainder, 0, f + 1);
		*str_remainder = fft_strdup(*str_remainder + (f + 1));
	}
	else
	{
		line = fft_substr(*str_remainder, 0, f);
		*str_remainder = NULL;
	}
	free (to_free);
	return (line);
}

static void	ft_tofill(int fd, char *buff, char **str)
{
	size_t	read_bytes;
	char	*tofree;

	read_bytes = 1;
	while (read_bytes)
	{
		read_bytes = read(fd, buff, BUFFER_SIZE);
		buff[read_bytes] = '\0';
		tofree = *str;
		*str = fft_strjoin(*str, buff);
		free (tofree);
		if ((fft_strchr(*str, '\n')))
			break ;
	}
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*line;
	char		*buff;

	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (0);
	if (fd < 0 || BUFFER_SIZE <= 0 || (read(fd, buff, 0) < 0))
	{
		free(buff);
		return (NULL);
	}
	if (!str)
		str = fft_strdup("");
	ft_tofill(fd, buff, &str);
	free(buff);
	line = next_line(&str);
	if (!line[0])
	{
		free(line);
		return (NULL);
	}
	return (line);
}
