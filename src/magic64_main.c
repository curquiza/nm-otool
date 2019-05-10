#include "ft_nm.h"

static char		get_type_char(uint64_t type, void *ptr)
{
	(void)type;
	(void)ptr;
	return ('K');
}

static void		print_symbols_output(t_symbol64 *output_tab, size_t sym_count)
{
	size_t	i;

	i = 0;
	while (i < sym_count)
	{
		ft_printf("%c %s\n", output_tab[i].type_char, output_tab[i].name);
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
	print_symbols_output(file.output_tab, file.symtab_lc->nsyms);
	clean_magic64(&file);
	return (SUCCESS);
}
