#ifndef FT_NM_H
# define FT_NM_H

# include "libft.h"

# include <fcntl.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>

typedef struct  s_symbol64
{
	char		*name;
	char		type_char;
	// address
}				t_symbol64;

typedef struct	s_file64
{
	void					*ptr;
	size_t					size;
	uint32_t				section_count;
	struct mach_header_64	*header;
	struct symtab_command	*symtab_lc;
	struct section_64		**sections;
	t_symbol64				*output_tab;
	//synbols table
}				t_file64;

// Global avec :
// - flags
// - filename

/*
** Function Prototypes
*/

t_ex_ret		init_magic64(t_file64 *file, void *ptr, size_t size);
t_ex_ret		handle_magic_64(size_t size, void *ptr);

#endif
