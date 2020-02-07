# include "../inc/woody_woodpacker.h"

extern void		stub(void);
extern size_t	stub_len;

static Elf64_Phdr	*get_last_loadable(Elf64_Phdr *ph, size_t n_pt)
{
	size_t		i;
	Elf64_Phdr	*last_loadable;

	last_loadable = NULL;
	i = 0;
	while (i < n_pt)
	{
		if (ph[i].p_type == PT_LOAD)
		{
			if (last_loadable == NULL || ph[i].p_offset > last_loadable->p_offset)
				last_loadable = ph + i;
		}
		i++;
	}
	return (last_loadable);
}

t_content			*pack(void *to_pack, size_t size)
{
	Elf64_Ehdr	*h;
	Elf64_Phdr	*ph;
	Elf64_Phdr	*last_loadable;
	t_content	*packed;

	h = to_pack;
	ph = to_pack + h->e_phoff;
	if ((packed = malloc(sizeof(*packed))) == NULL)
		return (null_perror("Unable to allocate memory for packed elf"));
	packed->size = size + stub_len;
	if ((last_loadable = get_last_loadable(ph, h->e_phnum)) == NULL)
		return (null_error("Unable to find cave for our stub"));
	if ((packed->start = malloc(packed->size)) == NULL)
		return (null_perror("Unable to allocate memory for packed elf"));
	memcpy(packed->start, to_pack, size);
	memcpy(packed->start + size, (void *)stub, stub_len);
	((Elf64_Ehdr *)packed->start)->e_entry = last_loadable->p_vaddr + (size - last_loadable->p_offset);
	return (packed);
}
