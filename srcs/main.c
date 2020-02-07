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

int		save_content(t_content *content, const char *name)
{
	int		fd;

	if ((fd = open(name, O_CREAT | O_WRONLY)) == -1)
		return (int_perror("Unable to save packed"));
	if ((write(fd, content->start, content->size)) == -1)
		return (int_perror("Unable to save content"));
	fchmod(fd, S_IRUSR | S_IWUSR | S_IXUSR);
	return (0);
}

int		main(int ac, char **av)
{
	size_t		size;
	void		*elf;
	t_content	*packed;
	int			fd;

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
	if (save_content(packed, "woody") == -1)
		return (-1);
	munmap(elf, size);
	free(packed->start);
	free(packed);
	return (0);
}
