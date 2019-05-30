#include "ft_nm.h"

static char			get_type_char_for_nsect(uint8_t n_sect, t_bin_file *file)
{
	if (n_sect == file->text_index)
		return ('T');
	else if (n_sect == file->data_index)
		return ('D');
	else if (n_sect == file->bss_index)
		return ('B');
	else
		return ('S');
}

static char		get_type_char(uint64_t value, uint8_t type, uint8_t n_sect,
						t_bin_file *file)
{
	uint8_t mask;
	unsigned char type_char;

	type_char = '?';
	if (type & N_STAB)
		return ('-');
	// limited global scope ??
	// if (type & N_PEXT)
	//	return (' ');
	mask = type & N_TYPE;
	if (mask == N_ABS)
		type_char = 'A';
	else if (mask == N_PBUD)
		type_char = 'P';
	else if (mask == N_INDR)
		type_char = 'I';
	else if (mask == N_SECT)
		type_char = get_type_char_for_nsect(n_sect, file);
	else if (mask == N_UNDF && value != 0 && (type & N_EXT))
		type_char = 'C';
	else if (mask == N_UNDF && (type & N_EXT))
		type_char = 'U';
	if (!(type & N_EXT))
		type_char = toggle_char(type_char);
	return (type_char);
}

static void		get_one_symbol(t_bin_file *file, struct nlist_64 *nlist,
					char *string_table, size_t i)
{
	uint64_t		n_value;

	file->symbols[i].name = check_and_move(file, string_table
			+ swap_uint32_if(nlist[i].n_un.n_strx, file->endian),
			sizeof(*file->symbols[i].name));
	if (!file->symbols[i].name)
		file->symbols[i].name = BAD_STRING_INDEX;
	n_value = swap_uint64_if(nlist[i].n_value, file->endian);
	file->symbols[i].type_char = get_type_char(n_value, nlist[i].n_type, nlist[i].n_sect, file);
	file->symbols[i].value = n_value;

}

static t_ex_ret	get_symbols_output(t_bin_file *file)
{
	size_t			i;
	char			*string_table;
	struct nlist_64	*nlist;
	uint32_t		nsyms;


	nsyms = swap_uint32_if(file->symtab_lc->nsyms, file->endian);
	nlist = (struct nlist_64 *)check_and_move(file, (void *)file->ptr
		+ swap_uint32_if(file->symtab_lc->symoff, file->endian),
		sizeof(*nlist) * nsyms);
	if (!nlist)
		return (ft_ret_err2(file->filename, VALID_OBJ_ERR));
	string_table = check_and_move(file,
		file->ptr + swap_uint32_if(file->symtab_lc->stroff, file->endian),
		sizeof(*string_table));
	if (!string_table)
		return (ft_ret_err2(file->filename, VALID_OBJ_ERR));
	i = 0;
	while (i < nsyms)
	{
		get_one_symbol(file, nlist, string_table, i);
		i++;
	}
	return (SUCCESS);
}

t_ex_ret	handle_64(size_t size, void *ptr, char *filename,
				enum e_endian endian)
{
	t_bin_file	file;

	ft_bzero(&file, sizeof(file));
	file.filename = filename;
	file.ptr = ptr;
	file.size = size;
	file.endian = endian;
	if (init_64(&file) == FAILURE)
		return (FAILURE);
	if (file.symtab_lc)
	{
		if (get_symbols_output(&file) == FAILURE)
		{
			clean(&file);
			return (FAILURE);
		}
		sort_symbols(&file);
		print_symbols_output(file.symbols,
			swap_uint32_if(file.symtab_lc->nsyms, file.endian));
		clean(&file);
	}
	return (SUCCESS);
}
