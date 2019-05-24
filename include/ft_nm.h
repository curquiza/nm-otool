#ifndef FT_NM_H
# define FT_NM_H

# include "libft.h"

# include <fcntl.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>

# define TOGGLE_CASE		32

# define VALID_OBJ_ERR	"The file was not recognized as a valid object file"

typedef struct  s_symbol
{
	char		*name;
	char		type_char;
	uint64_t	value;
}				t_symbol;

typedef struct	s_bin_file
{
	char					*filename;
	void					*ptr;
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
uint8_t			g_flags;

/*
** Function Prototypes
*/

t_ex_ret		init_magic64(t_bin_file *file, void *ptr, size_t size, char *filename);
t_ex_ret		handle_magic_64(size_t size, void *ptr, char *filename);

void			sort_symbols(t_bin_file *file);

// t_bool			is_in_file(t_bin_file *file, void *current_pos, size_t needed_size);
void			*check_and_move(t_bin_file *file, void *dest, size_t needed_size);

#endif
