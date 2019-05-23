#include "ft_nm.h"

char        get_type_char(uint64_t value, uint8_t type, t_bin_file *file)
{
    uint8_t mask;
    unsigned char type_char;
    (void)file;
    // printf("%d ", type);

    // debug, see stab.h afer
    if (type & N_STAB)
        return ('-');

    // limited global scope ??
    if (type & N_PEXT)
        return (' ');

    // type of the symbol
    mask = type & N_TYPE;
    if (mask == N_UNDF)
    {
        type_char = 'U';
    }
    if (mask == N_ABS)
    {
        type_char = 'A';
    }
    if (mask == N_PBUD)
    {
        type_char = 'P';
    }
    if (mask == N_INDR)
    {
        type_char = 'I';
    }
    if (mask == N_SECT)
    {
        type_char = 'S'; // T ou D ou B
    }
	if (mask == N_UNDF && value != 0)
	{
		type_char = 'C';
	}

    if (!(type & N_EXT)) // local symbol --> minuscule
        type_char ^= TOGGLE_CASE;
    return (type_char);
}

static void		print_symbols_output(t_symbol *symbols, size_t sym_count)
{
	size_t	i;

	i = 0;
	while (i < sym_count)
	{
		ft_printf("%c %s\n", symbols[i].type_char, symbols[i].name);
		i++;
	}
}

static void	get_symbols_output(t_bin_file *file)
{
	size_t			i;
	char			*string_table;
	struct nlist_64	*nlist;

	nlist = file->ptr + file->symtab_lc->symoff; //check size
	string_table = file->ptr + file->symtab_lc->stroff; //check size
	i = 0;
	while (i < file->symtab_lc->nsyms)
	{
		file->symbols[i].name = string_table + nlist[i].n_un.n_strx;
		file->symbols[i].type_char = get_type_char(nlist[i].n_value, nlist[i].n_type, file);
		i++;
	}
}

static void	clean_magic64(t_bin_file *file)
{
	free(file->symbols);
	// free(file->sections);
	// file->sections = NULL;
	file->symbols = NULL;
}

t_ex_ret	handle_magic_64(size_t size, void *ptr)
{
	t_bin_file	file;

	if (init_magic64(&file, ptr, size) == FAILURE)
	{
		clean_magic64(&file);
		return (FAILURE);
	}
	get_symbols_output(&file);
	print_symbols_output(file.symbols, file.symtab_lc->nsyms);
	clean_magic64(&file);
	return (SUCCESS);
}
