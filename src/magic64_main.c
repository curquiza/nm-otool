#include "ft_nm.h"

static char        get_type_char(uint64_t value, uint8_t type, uint8_t n_sect, t_bin_file *file)
{
    uint8_t mask;
    unsigned char type_char;

	type_char = 0;
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
        type_char = 'S';
		if (n_sect == file->text_index)
			type_char = 'T';
		else if (n_sect == file->data_index)
			type_char = 'D';
		else if (n_sect == file->bss_index)
			type_char = 'B';
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
		if (symbols[i].type_char == '-')
			;
		else if (symbols[i].type_char == 'U' || symbols[i].type_char == 'u')
			ft_printf("%18c %s\n", symbols[i].type_char, symbols[i].name);
		else
			ft_printf("%.16llx %c %s\n", symbols[i].value, symbols[i].type_char, symbols[i].name);
		i++;
	}
}

static t_ex_ret	get_symbols_output(t_bin_file *file)
{
	size_t			i;
	char			*string_table;
	struct nlist_64	*nlist;

	// nlist = (struct nlist_64 *) ((void *)file->ptr + file->symtab_lc->symoff); //check size
	nlist = (struct nlist_64 *)check_and_move(file, (void *)file->ptr
		+ file->symtab_lc->symoff, sizeof(*nlist) * file->symtab_lc->nsyms); //check size
	if (!nlist)
		return (ft_ret_err2(file->filename, VALID_OBJ_ERR));
	// string_table = file->ptr + file->symtab_lc->stroff; //check size
	string_table = check_and_move(file, file->ptr + file->symtab_lc->stroff, sizeof(*string_table)); //check size
	if (!string_table)
		return (ft_ret_err2(file->filename, VALID_OBJ_ERR));
	i = 0;
	while (i < file->symtab_lc->nsyms)
	{
		// file->symbols[i].name = string_table + nlist[i].n_un.n_strx;
		file->symbols[i].name = check_and_move(file, string_table
			+ nlist[i].n_un.n_strx, sizeof(*file->symbols[i].name));
		if (!file->symbols[i].name)
			return (ft_ret_err2(file->filename, VALID_OBJ_ERR));
		file->symbols[i].type_char = get_type_char(nlist[i].n_value, nlist[i].n_type, nlist[i].n_sect, file);
		file->symbols[i].value = nlist[i].n_value;
		i++;
	}
	return (SUCCESS);
}

static void	clean_magic64(t_bin_file *file)
{
	free(file->symbols);
	file->symbols = NULL;
}

t_ex_ret	handle_magic_64(size_t size, void *ptr, char *filename)
{
	t_bin_file	file;

	if (init_magic64(&file, ptr, size, filename) == FAILURE)
		return (FAILURE);
	if (file.symtab_lc)
	{
		if (get_symbols_output(&file) == FAILURE)
		{
			clean_magic64(&file);
			return (FAILURE);
		}
		sort_symbols(&file);
		print_symbols_output(file.symbols, file.symtab_lc->nsyms);
		clean_magic64(&file);
	}
	return (SUCCESS);
}
