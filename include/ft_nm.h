#ifndef FT_NM_H
# define FT_NM_H

# include "libft.h"

# include <fcntl.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>

# define TOGGLE_CASE	32

typedef struct  s_symbol
{
	char		*name;
	char		type_char;
	uint64_t	value;
}				t_symbol;

typedef struct	s_bin_file
{
	void					*ptr;
	// void					*end;
	size_t					size;
	struct symtab_command	*symtab_lc; //generique ?
	t_symbol				*symbols;
	uint8_t					text_index;
	uint8_t					data_index;
	uint8_t					bss_index;
}				t_bin_file;

// Global avec :
// - flags
// - filename
uint8_t					g_flags;

/*
** Function Prototypes
*/

t_ex_ret		init_magic64(t_bin_file *file, void *ptr, size_t size);
t_ex_ret		handle_magic_64(size_t size, void *ptr);

void			sort_symbols(t_bin_file *file);

#endif
