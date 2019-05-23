#ifndef FT_NM_H
# define FT_NM_H

# include "libft.h"

# include <fcntl.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>

# define TOGGLE_CASE	32
// # define SECT_TEXT		"__text"
// # define SECT_DATA		"__got"
// # define SECT_BSS		"__bss"

typedef struct  s_symbol
{
	char		*name;
	char		type_char;
	// void 	*address
}				t_symbol;

typedef struct	s_bin_file
{
	void					*ptr;
	size_t					size;
	// uint32_t				section_count;
	struct symtab_command	*symtab_lc; //generique ?
	t_symbol				*symbols;
	uint8_t					text_index;
	uint8_t					data_index;
	uint8_t					bss_index;
}				t_bin_file;

// Global avec :
// - flags
// - filename

/*
** Function Prototypes
*/

t_ex_ret		init_magic64(t_bin_file *file, void *ptr, size_t size);
t_ex_ret		handle_magic_64(size_t size, void *ptr);

#endif
