#include "ft_nm.h"

static char	get_type_char_for_nsect(uint8_t n_sect, t_bin_file *file)
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

char		get_type_char(uint64_t value, uint8_t type, uint8_t n_sect,
				t_bin_file *file)
{
	uint8_t			mask;
	unsigned char	type_char;

	type_char = '?';
	if (type & N_STAB)
		return ('-');
	mask = type & N_TYPE;
	if (mask == N_ABS)
		type_char = 'A';
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
