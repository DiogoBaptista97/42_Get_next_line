/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbraga-b <dbraga-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 13:56:35 by dbraga-b          #+#    #+#             */
/*   Updated: 2022/11/16 14:34:28 by dbraga-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>
#include"get_next_line.h"
#include<stdlib.h>
#include<unistd.h>
#include <fcntl.h>

char	*ft_getline(char *stash)
{
	int		len;
	int		i;
	char	*str;

	i = 0;
	len = 0;
	if (!stash[i])
		return (NULL);
	while (stash[len] != '\n' && stash[len])
		len++;
	len++;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (i < len)
	{
		str[i] = stash[i];
		i++;
	}
	str[i] = 0;
	return (str);
}

char	*cleanstash(char *stash)
{
	int		start;
	int		i;
	char	*new;

	i = 0;
	start = 0;
	while (stash[start] != '\n' && stash[start])
		start++;
	if (!stash[start])
	{
		free(stash);
		return (NULL);
	}
	new = malloc(sizeof(char) * (ft_strlen(stash) - start) + 1);
	if (!new)
		return (NULL);
	start++;
	while (stash[start])
		new[i++] = stash[start++];
	new[i] = 0;
	free(stash);
	return (new);
}

char	*get_next_line(int fd)
{
	char		*str;
	static char	*stash[4096];

	if (fd < 0 || fd > 4095 || BUFFER_SIZE <= 0)
		return (NULL);
	if (stash[fd] == NULL)
	{
		stash[fd] = malloc(sizeof(char) * 1);
		stash[fd][0] = '\0';
	}
	stash[fd] = stashsize(fd, stash[fd]);
	if (!stash[fd])
		return (NULL);
	str = ft_getline(stash[fd]);
	stash[fd] = cleanstash(stash[fd]);
	return (str);
}
