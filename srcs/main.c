# include "../inc/woody_woodpacker.h"

void	*map_file(int fd, size_t *size)
{
	struct stat	st;
	void		*mapped;

	if (fstat(fd, &st) == -1)
		return (null_perror("Unable to retrieve file stats"));
	*size = st.st_size;
	if ((mapped = mmap(NULL, *size, PROT_READ,
		MAP_PRIVATE, fd, 0)) == NULL)
			return (null_perror("Unable to map file content"));
	close(fd);
	return (mapped);
}

Elf64_Phdr	*get_last_loadable(Elf64_Phdr *ph, size_t n_pt, size_t size)
{
	size_t	i;

	i = 0;
	while (i < n_pt)
	{
		if (ph[i].p_type == PT_LOAD)
		{
			if ((ph[i].p_offset + ph[i].p_filesz) == size)
				return (ph + i);
		}
		i++;
	}
	return (NULL);
}

int		save_packed(void *packed, size_t size)
{
	int		fd;

	if ((fd = open("woody", O_CREAT | O_WRONLY)) == -1)
		return (int_perror("Unable to save packed"));
	if ((write(fd, packed, size)) == -1)
		return (int_perror("Unable to save packed"));
	fchmod(fd, S_IRUSR | S_IWUSR | S_IXUSR);
	return (0);
}

void	*pack(void *to_pack, size_t size)
{
	Elf64_Ehdr	*h;
	Elf64_Phdr	*ph;
	Elf64_Phdr	*last_loadable;
	void		*packed;

	h = to_pack;
	ph = to_pack + h->e_phoff;
	if ((last_loadable = get_last_loadable(ph, h->e_phnum, size)) != NULL)
		return (null_error("Unable to find cave for our stub"));
	if ((packed = malloc(size + size)) == NULL) // TODO: find real size
		return (null_perror("Unable to allocate memory for packed elf"));
	memcpy(packed, to_pack, size);
	memcpy(packed + size, to_pack, size); // TODO: do something useful
	((Elf64_Ehdr *)packed)->e_entry = h->e_entry + size;
	return (packed);
}

int		main(int ac, char **av)
{
	size_t	size;
	void	*elf;
	void	*packed;
	int		fd;

	if (ac != 2)
	{
		puts("usage: ./woody_woodpacker filename");
		return (1);
	}
	if ((fd = open(av[1], O_RDONLY)) == -1)
	{
		perror("Unable to open file");
		return (1);
	}
	if ((elf = map_file(fd, &size)) == NULL)
		return (1);
	if ((packed = pack(elf, size)) == NULL)
		return (1);
	if (save_packed(packed, 2 * size) == -1)
		return (-1);
	munmap(elf, size);
	free(packed);
	return (0);
}
