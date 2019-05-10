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

static uint32_t		get_sections_in_segment(t_file64 *file, struct load_command *lc, uint32_t section_index)
{
	uint32_t					i;
	struct segment_command_64	*seg;
	struct section_64			*first_section;

	seg = (struct segment_command_64 *)lc; //check size
	first_section = (struct section_64 *)((void *)lc + sizeof(*seg)); //check size
	i = 0;
	while (i < seg->nsects && (i + section_index) < file->section_count)
	{
		file->sections[i + section_index] = (void *)first_section + i * sizeof(struct section_64); //check size
		i++;
	}
	return (i);
}

static void		get_file_info(t_file64 *file)
{
	uint32_t				i;
	uint32_t				section_index;
	struct load_command		*lc;

	lc = file->ptr + sizeof(*file->header); //check size
	section_index = 0;
	i = 0;
	while (i < file->header->ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
			file->symtab_lc = (struct symtab_command *)lc; //check size
		else if (lc->cmd == LC_SEGMENT_64)
			section_index += get_sections_in_segment(file, lc, section_index);
		i++;
		lc = (void *)lc + lc->cmdsize; //check size
	}
}

static uint32_t	get_section_count(t_file64 *file)
{
	struct load_command			*lc;
	struct segment_command_64	*seg;
	uint32_t					i;
	uint32_t					count;

	lc = file->ptr + sizeof(*file->header); //check size
	count = 0;
	i = 0;
	while (i < file->header->ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64)
		{
			seg = (struct segment_command_64 *)lc; //check size
			count += seg->nsects;
		}
		i++;
		lc = (void *)lc + lc->cmdsize; //check size
	}
	return (count);
}

void	print_sections_table(t_file64 *file)
{
	uint32_t i;

	i = 0;
	ft_printf("---------------\n");
	ft_printf("---------------\n");
	ft_printf("section count = %d\n", file->section_count);
	while (i < file->section_count)
	{
		ft_printf("------------\n");
		ft_printf("i = %d\n", i);
		ft_printf("section name = %s\n", file->sections[i]->sectname);
		i++;
	}
	ft_printf("---------------\n");
	ft_printf("---------------\n");
}

t_ex_ret		init(t_file64 *file, void *ptr, size_t size)
{
	file->ptr = ptr;
	file->size = size;
	file->header = (struct mach_header_64 *)ptr; //check size
	file->section_count = get_section_count(file);
	if (!(file->sections = (struct section_64 **)ft_memalloc(sizeof(*file->sections) * file->section_count)))
		return (FAILURE);
	get_file_info(file);
	print_sections_table(file);
	return (SUCCESS);
}

t_ex_ret	handle_magic_64(size_t size, void *ptr)
{
	t_file64	file;

	if (init(&file, ptr, size) == FAILURE)
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
