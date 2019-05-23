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
	// void 	*address
}				t_symbol;

typedef struct	s_bin_file
{
	void					*ptr;
	// void					*end;
	size_t					size;
	// uint32_t				magic_number;
	uint32_t				section_count;
	// struct mach_header_64	*header;
	struct symtab_command	*symtab_lc; //generique ?
	// struct section_64		**sections;
	t_symbol				*symbols;
	//synbols table
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
