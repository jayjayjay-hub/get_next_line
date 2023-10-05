/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 13:14:26 by jtakahas          #+#    #+#             */
/*   Updated: 2023/10/05 17:59:02 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*new_file_str(char *file_str)
{
	size_t	i;
	size_t	j;
	char	*new_file_str;

	i = 0;
	j = 0;
	while (file_str[i] && file_str[i] != '\n')
		i++;
	if (!file_str[i])
	{
		free(file_str);
		return (NULL);
	}
	new_file_str = malloc(sizeof(char) * ((ft_strlen(file_str) - i) + 1));
	if (!new_file_str)
		return (NULL);
	i++;
	while (file_str[i])
		new_file_str[j++] = file_str[i++];
	new_file_str[j] = '\0';
	free(file_str);
	return (new_file_str);
}

static char	*search_indention(char *file_str)
{
	size_t	index;
	char	*next_line;

	index = 0;
	if (!file_str[index])
		return (NULL);
	while (file_str[index] && file_str[index] != '\n')
		index++;
	next_line = malloc(sizeof(char) * (index + 2));
	if (!next_line)
		return (NULL);
	index = 0;
	while (file_str[index] && file_str[index] != '\n')
	{
		next_line[index] = file_str[index];
		index++;
	}
	if (file_str[index] == '\n')
	{
		next_line[index] = '\n';
		index++;
	}
	next_line[index] = '\0';
	return (next_line);
}

static char	*read_file_str(int fd, char *file_str)
{
	char	*buf;
	int		read_byte;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	read_byte = 1;
	while ((ft_strchr(file_str, '\n') == NULL) && read_byte)
	{
		read_byte = read(fd, (void *)buf, BUFFER_SIZE);
		if (read_byte == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[read_byte] = '\0';
		file_str = ft_strjoin(file_str, buf);
	}
	free(buf);
	return (file_str);
}

char	*get_next_line(int fd)
{
	static char	*file_str[OPEN_MAX];
	char		*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	file_str[fd] = read_file_str(fd, file_str[fd]);
	if (!file_str[fd])
		return (NULL);
	next_line = search_indention(file_str[fd]);
	file_str[fd] = new_file_str(file_str[fd]);
	return (next_line);
}

// #include <stdio.h>
// #include <fcntl.h>

// __attribute__((destructor))
// static void	destructor(void)
// {
// 	system("leaks -q a.out");
// }

// int	main(void)
// {
// 	int		fd1;
// 	int		fd2;
// 	int		fd3;
// 	char	*line;
// 	int		i = 0;

// 	fd1 = open("test/test1.txt", O_RDONLY);
// 	fd2 = open("test/test2.txt", O_RDONLY);
// 	fd3 = open("test/test3.txt", O_RDONLY);
// 	if (fd1 < 0 || fd2 < 0 || fd3 < 0)
// 		return (0);
// 	// while (1)
// 	// {
// 	// 	line = get_next_line(fd1);
// 	// 	if (!line)
// 	// 		break ;
// 	// 	printf("%s", line);
// 	// 	free(line);
// 	// }
// 	// printf("\n\n\n\n");
// 	// while (1)
// 	// {
// 	// 	line = get_next_line(fd2);
// 	// 	if (!line)
// 	// 		break ;
// 	// 	printf("%s", line);
// 	// 	free(line);
// 	// }
// 	// printf("\n\n\n\n");
// 	// while (1)
// 	// {
// 	// 	line = get_next_line(fd3);
// 	// 	if (!line)
// 	// 		break ;
// 	// 	printf("%s", line);
// 	// 	free(line);
// 	// }
// 	// printf("\n\n\n");

// 	while (i < 10)
// 	{
// 		line = get_next_line(fd1);
// 		printf("test1 : %s\n", line);
// 		free(line);

// 		line = get_next_line(fd2);
// 		printf("test2 : %s\n", line);
// 		free(line);

// 		line = get_next_line(fd3);
// 		printf("test3 : %s\n", line);
// 		free(line);
// 		i++;
// 	}
// 	printf("\n\n\n");

// 	line = get_next_line(1);
// 	printf("%s", line);
// 	free(line);
// 	close(fd1);
// 	close(fd2);
// 	close(fd3);
// 	return (0);
// }