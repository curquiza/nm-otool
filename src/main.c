#include "ft_nm.h"

static char		get_type_char(uint64_t type, void *ptr)
{
	(void)type;
	(void)ptr;
	return ('K');
}

static void		print_output_tab(t_symbol64 *tab, size_t sym_count)
{
	size_t	i;

	i = 0;
	while (i < sym_count)
	{
		ft_printf("%c %s\n", tab[i].type_char, tab[i].name);
		i++;
	}
}

static void	get_symbols_output(t_file64 *file)
{
	size_t			i;
	char			*string_table;
	struct nlist_64	*nlist;

	nlist = file->ptr + file->symtab_lc->symoff; //check size
	string_table = file->ptr + file->symtab_lc->stroff; //check size
	i = 0;
	while (i < file->symtab_lc->nsyms)
	{
		file->output_tab[i].name = string_table + nlist[i].n_un.n_strx;
		file->output_tab[i].type_char = get_type_char(nlist[i].n_type, file->ptr);
		i++;
	}
}

static void	clean_magic64(t_file64 *file)
{
	free(file->output_tab);
	free(file->sections);
	file->sections = NULL;
	file->output_tab = NULL;
}

t_ex_ret	handle_magic_64(size_t size, void *ptr)
{
	t_file64	file;

	if (init_magic64(&file, ptr, size) == FAILURE)
	{
		clean_magic64(&file);
		return (FAILURE);
	}
	get_symbols_output(&file);
	print_output_tab(file.output_tab, file.symtab_lc->nsyms);
	clean_magic64(&file);
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
