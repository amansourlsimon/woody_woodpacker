/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 14:44:08 by lsimon            #+#    #+#             */
/*   Updated: 2019/12/13 13:10:13 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/woody_woodpacker.h"

static t_content	*init_content(void *start, size_t len)
{
	t_content	*content;

	if ((content = malloc(sizeof(content))) == NULL)
		return (null_error("Unable to allocate memory for t_content struct"));
	content->start = start;
	content->len = len;

	return (content);
}

/*
** Takes a filename and map the corresponding file into memory
** Returned pointer must be freed using munmap
*/
static t_content	*map_file(const char *filename)
{
	void		*start;
	struct stat	buf;
	int			fd;

	if ((fd = open(filename, O_RDWR)) == -1)
		return (null_error("Unable to open file"));
	if (fstat(fd, &buf) == -1)
	{
		close(fd);
		return (null_error("Unable to read file stats"));
	}
	start = mmap(NULL,
		buf.st_size,
		PROT_READ | PROT_WRITE,
		MAP_PRIVATE,
		fd,
		0);

	if (start == MAP_FAILED)
	{
		close(fd);
		return (null_error("Unable to map file content into virtual memory"));
	}
	close(fd);
	return (init_content(start, buf.st_size));
}

int	main(int ac, char **av)
{
	t_content	*content;

	if (ac != 2)
	{
		dprintf(2, "usage: ./woody_woodpacker elf_path\n");
		return (1);
	}
	if ((content = map_file(av[1])) == NULL)
		return (1);
	munmap(content->start, content->len);
	return (0);
}
