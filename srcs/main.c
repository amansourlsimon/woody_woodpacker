/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 14:44:08 by lsimon            #+#    #+#             */
/*   Updated: 2019/12/08 17:30:23 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/woody_woodpacker.h"

/*
** Returned pointer must be freed using munmap
*/

static void		*map_file(const char *filename)
{
	void		*mapped_file;
	struct stat	buf;
	int			fd;

	if ((fd = open(filename, O_RDWR)) == -1)
		return (null_error("Unable to open file"));
	if (fstat(fd, &buf) == -1)
		return (null_error("Unable to read file stats"));
	mapped_file = mmap(NULL,
		buf.st_size,
		PROT_READ | PROT_WRITE,
		MAP_PRIVATE,
		fd,
		0);

	if (mapped_file == MAP_FAILED)
		return (null_error("Unable to map file content into virtual memory"));
	return (mapped_file);
}

int	main(int ac, char **av)
{
	void	*content;

	if (ac != 2)
	{
		dprintf(2, "usage: ./woody_woodpacker elf_path\n");
		return (1);
	}
	if ((content = map_file(av[1])) == NULL)
		return (1);
	return (0);
}
