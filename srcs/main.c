/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 14:44:08 by lsimon            #+#    #+#             */
/*   Updated: 2019/12/13 18:51:12 by lsimon           ###   ########.fr       */
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

/*
** Here we just need the e_entry, e_phoff and e_phnum fields of the 
** Elf32_Ehdr structure to have offset and number of Elf32_Phdr entries.
** For the Elf32_Phdr structure, we need to check if p_type is equal
** to PT_LOAD (we don't give a fuck about other segment types, they do not
** contain any useful information for us). If it's equal, we'll need p_offset,
** p_vaddr, p_filesz and p_memsz fields to have information about
** memory mapping.
*/
static void			lookup(t_content *content)
{
	t_elf		*header;
	t_p_header	*p_header;

	header = (t_elf *)content->start;
	printf("(debug) header->e_ident: %s\n", header->e_ident);
	printf("(debug) header->e_entry: %llu\n", header->e_entry);
	printf("(debug) header->e_phoff: %llu\n", header->e_phoff);
	printf("(debug) header->e_phnum: %hu\n", header->e_phnum);

	p_header = (t_p_header *)((char *)header + header->e_phoff);
	for (int i = 0; i < header->e_phnum; i++)
	{
		if (p_header[i].p_type == PT_LOAD)
		{
			printf("(debug) p_header[i].p_offset: %llu\n", p_header[i].p_offset);
			printf("(debug) p_header[i].p_vaddr: %llu\n", p_header[i].p_vaddr);
			printf("(debug) p_header[i].p_filesz: %llu\n", p_header[i].p_filesz);
			printf("(debug) p_header[i].p_memsz: %llu\n", p_header[i].p_memsz);
		}
	}
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
	lookup(content);
	munmap(content->start, content->len);
	return (0);
}
