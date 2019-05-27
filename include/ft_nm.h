#ifndef FT_NM_H
# define FT_NM_H

# include "libft.h"

# include <fcntl.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>

# define OPTIONS		"gjnpruU"
# define TOGGLE_CASE	32

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
// - filename ?
uint8_t			g_flags;

/*
** Function Prototypes
*/

char			to_lower(char c);
t_bool			is_external_symbol(char c);
t_bool			is_undefined_symb(char c);
t_ex_ret		ret_malloc_err(void);
t_ex_ret		ret_usage(void);
t_ex_ret		activate_opt(char opt_letter);
t_bool			opt_is_activated(char opt_letter);

void			*check_and_move(t_bin_file *file, void *dest,
					size_t needed_size);
t_ex_ret		ft_nm(size_t size, void *ptr, char *filename);
t_ex_ret		init_magic64(t_bin_file *file, void *ptr, size_t size,
					char *filename);
t_ex_ret		handle_magic_64(size_t size, void *ptr, char *filename);

t_bool			value_sort_comp(t_symbol *symb1, t_symbol *symb2);
t_bool			alpha_sort_comp(t_symbol *symb1, t_symbol *symb2);
t_ex_ret		sort_symbols(t_bin_file *file);

void			print_symbols_output(t_symbol *symbols, size_t sym_count);

void			clean_magic64(t_bin_file *file);

#endif
