#include "ft_nm.h"

// void	print_output(int nsyms, int symoff, int stroff, void *ptr)
// {
// 	int				i;
// 	char			*stringtable;
// 	struct nlist_64	*elem;

// 	elem = ptr + symoff;
// 	stringtable = ptr + stroff;

// 	i = 0;
// 	while (++i < nsyms)
// 	{
// 		printf("%s\n", stringtable + elem[i].n_un.n_strx);
// 	}

// }

// static void		free_if_malloc_failed(size_t count, t_symbol64 **tab)
// {
// 	size_t	i;

// 	i = 0;
// 	while (i < count)
// 	{
// 		free(*tab);
// 		i++;
// 	}
// 	free(tab);
// }

// t_symbol64		**create_symbols_tab(size_t symb_count)
// {
// 	t_symbol64	**rslt;
// 	size_t	i;

// 	rslt = NULL;
// 	if (!(rslt = (t_symbol64 **)ft_memalloc(symb_count * sizeof(*rslt))))
// 		return (NULL);
// 	i = 0;
// 	while (i < symb_count)
// 	{
// 		if (!(*rslt = (t_symbol64 *)ft_memalloc(sizeof(**rslt))))
// 		{
// 			free_if_malloc_failed(i, rslt);
// 			return (NULL);
// 		}
// 		i++;
// 	}
// 	return rslt;
// }

static char		get_type_char(uint64_t type, void *ptr)
{
	(void)type;
	(void)ptr;
	return ('P');
}

static void		fill_symbols_tab(t_symbol64 *symbols_tab, struct symtab_command *sym, void *ptr)
{
	size_t			i;
	char			*string_table;
	struct nlist_64	*nlist;

	nlist = ptr + sym->symoff; //check size
	string_table = ptr + sym->stroff; //check size

	i = 0;
	while (i < sym->nsyms)
	{
		symbols_tab[i].name = string_table + nlist[i].n_un.n_strx;
		symbols_tab[i].type_char = get_type_char(nlist[i].n_type, ptr);
		i++;
	}
}

static void		print_symbols_table(t_symbol64 *symbols_tab, size_t sym_count)
{
	size_t	i;

	i = 0;
	while (i < sym_count)
	{
		ft_printf("%c %s\n", symbols_tab[i].type_char ,symbols_tab[i].name);
		i++;
	}
}

t_ex_ret	handle_magic_64(size_t size, void *ptr)
{
	int						cmd_number;
	int						i;
	struct mach_header_64	*header;
	struct load_command		*lc;
	struct symtab_command	*sym;
	t_symbol64				*symbols_tab;

	(void)size;
	header = (struct mach_header_64 *)ptr;
	cmd_number = header->ncmds; //check size ?

	lc = ptr + sizeof(*header); //check size
	i = 0;
	while (i < cmd_number)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			puts("Section SYMTAB");
			sym = (struct symtab_command *)lc;
			printf("nb symbols: %d\n", sym->nsyms);
			if (!(symbols_tab = (t_symbol64 *)ft_memalloc(sym->nsyms * sizeof(*symbols_tab))))
				return (FAILURE);
			fill_symbols_tab(symbols_tab, sym, ptr);
			print_symbols_table(symbols_tab, sym->nsyms);
			free(symbols_tab);
			return (SUCCESS);
		}
		i++;
		lc = (void *)lc + lc->cmdsize; //check size
	}

	return (FAILURE);
}

t_ex_ret	ft_nm(size_t size, void *ptr)
{
	unsigned int	magic_number;

	magic_number = *(int *)ptr;
	printf("magic number: %x\n", magic_number);

	if (magic_number == MH_MAGIC)
	{
		printf("MAGIC 32 bits");
	}
	else if (magic_number == MH_MAGIC_64)
	{
		printf("MAGIC 64 bits");
		return (handle_magic_64(size, ptr));
	}
	else if (magic_number == MH_CIGAM)
	{
		printf("CIGAM 32 bits");
	}
	else if (magic_number == MH_CIGAM_64)
	{
		printf("CIGAM 64 bits");
	}
	else
	{
		dprintf(2, "Wrong magic number");
	}
	return (FAILURE);
}

int		main(int ac, char **av)
{
	int			fd;
	void		*ptr;
	struct stat buf;
	t_ex_ret	ret;

	ptr = NULL;

	if (ac != 2)
	{
		fprintf(stderr, "usage: nm binary_file [...]\n");
		return (FAILURE);
	}

	if ((fd = open(av[1], O_RDONLY)) < 0)
	{
		fprintf(stderr, "open: error\n");
		return (FAILURE);
	}

	if ((fstat(fd, &buf)) < 0)
	{
		fprintf(stderr, "fstat: error\n");
		return (FAILURE);
	}

	if ((ptr = mmap(ptr, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
	{
		fprintf(stderr, "mmap: error\n");
		return (FAILURE);
	}

	ret = ft_nm(buf.st_size, ptr);

	if (munmap(ptr, buf.st_size) < 0)
	{
		fprintf(stderr, "munmap: error\n");
		return (FAILURE);
	}

	//close !!

	return (ret);
}

// TODO:
// - gerer les binaires compilés avec -g : N_STAB dans n_type ?
