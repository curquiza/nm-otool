#include "ft_nm.h"

// static char		get_type_char(uint64_t type, void *ptr)
// {
// 	(void)type;
// 	(void)ptr;
// 	return ('P');
// }

// static void		fill_symbols_tab(t_symbol64 *symbols_tab, struct symtab_command *sym, void *ptr)
// {
// 	size_t			i;
// 	char			*string_table;
// 	struct nlist_64	*nlist;

// 	nlist = ptr + sym->symoff; //check size
// 	string_table = ptr + sym->stroff; //check size

// 	i = 0;
// 	while (i < sym->nsyms)
// 	{
// 		symbols_tab[i].name = string_table + nlist[i].n_un.n_strx;
// 		symbols_tab[i].type_char = get_type_char(nlist[i].n_type, ptr);
// 		i++;
// 	}
// }

// static void		print_symbols_table(t_symbol64 *symbols_tab, size_t sym_count)
// {
// 	size_t	i;

// 	i = 0;
// 	while (i < sym_count)
// 	{
// 		ft_printf("%c %s\n", symbols_tab[i].type_char ,symbols_tab[i].name);
// 		i++;
// 	}
// }

// t_symbol64				*symbols_tab;
// if (!(symbols_tab = (t_symbol64 *)ft_memalloc(sym->nsyms * sizeof(*symbols_tab))))
// 	return (FAILURE);
// fill_symbols_tab(symbols_tab, sym, ptr);
// print_symbols_table(symbols_tab, sym->nsyms);
// free(symbols_tab);

t_ex_ret	handle_magic_64(size_t size, void *ptr)
{
	t_file64	file;

	if (init_magic64(&file, ptr, size) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

t_ex_ret	ft_nm(size_t size, void *ptr)
{
	uint32_t	magic_number;

	magic_number = *(uint32_t *)ptr;
	if (magic_number == MH_MAGIC)
	{
		ft_printf("MAGIC 32 bits\n");
	}
	else if (magic_number == MH_MAGIC_64)
	{
		ft_printf("MAGIC 64 bits\n");
		return (handle_magic_64(size, ptr));
	}
	else if (magic_number == MH_CIGAM)
	{
		ft_printf("CIGAM 32 bits\n");
	}
	else if (magic_number == MH_CIGAM_64)
	{
		ft_printf("CIGAM 64 bits\n");
	}
	else
	{
		ft_dprintf(2, "Wrong magic number\n");
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
