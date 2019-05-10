#include "ft_nm.h"

#include <stdio.h>
#include <sys/mman.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>

void	print_output(int nsyms, int symoff, int stroff, void *ptr)
{
	int				i;
	char			*stringtable;
	struct nlist_64	*elem;

	elem = ptr + symoff;
	stringtable = ptr + stroff;

	i = 0;
	while (++i < nsyms)
	{
		printf("%s\n", stringtable + elem[i].n_un.n_strx);
	}

}

void	handle_magic_64(char *ptr)
{
	int						ncmds;
	int						i;
	struct mach_header_64	*header;
	struct load_command		*lc;
	struct symtab_command	*sym;

	header = (struct mach_header_64 *)ptr;
	ncmds = header->ncmds;

	lc = (void *)ptr + sizeof(*header);
	i = 0;
	while (++i < ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			puts("Section SYMTAB");
			sym = (struct symtab_command *)lc;
			printf("nb symbols: %d\n", sym->nsyms);
			print_output(sym->nsyms, sym->symoff, sym->stroff, (void *)ptr);
			break ;
		}
		lc = (void *)lc + lc->cmdsize;
	}
}

void	ft_nm(size_t size, char *ptr)
{
	unsigned int	magic_number;

    (void)size;
	magic_number = *(int *)ptr;
	ft_printf("magic number: %x\n", magic_number);

    if (magic_number == MH_MAGIC)
    {
		ft_printf("MAGIC 32 bits");
	}
    else if (magic_number == MH_MAGIC_64)
	{
		ft_printf("MAGIC 64 bits");
		handle_magic_64(ptr);
	}
    else if (magic_number == MH_CIGAM)
    {
		ft_printf("CIGAM 32 bits");
	}
    else if (magic_number == MH_CIGAM_64)
    {
		ft_printf("CIGAM 64 bits");
	}
    else
    {
        ft_dprintf(2, "Wrong magic number");
    }
}

int		main(int ac, char **av)
{
	int			fd;
	char		*ptr;
	struct stat buf;

	ptr = NULL;

	if (ac != 2)
	{
		fprintf(stderr, "usage: nm binary_file [...]\n");
		return (EXIT_FAILURE);
	}

	if ((fd = open(av[1], O_RDONLY)) < 0)
	{
		fprintf(stderr, "open: error\n");
		return (EXIT_FAILURE);
	}

	if ((fstat(fd, &buf)) < 0)
	{
		fprintf(stderr, "fstat: error\n");
		return (EXIT_FAILURE);
	}

	if ((ptr = mmap(ptr, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
	{
		fprintf(stderr, "mmap: error\n");
		return (EXIT_FAILURE);
	}

	ft_nm(buf.st_size, ptr);

	if (munmap(ptr, buf.st_size) < 0)
	{
		fprintf(stderr, "munmap: error\n");
		return (EXIT_FAILURE);
	}

    //close

	return (EXIT_SUCCESS);
}
