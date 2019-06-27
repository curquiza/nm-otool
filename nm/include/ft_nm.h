/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 13:29:35 by curquiza          #+#    #+#             */
/*   Updated: 2019/06/26 13:29:39 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H

# include "libft.h"

# include <fcntl.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>
# include <errno.h>
# include <ar.h>
# include <mach-o/ranlib.h>

# define OPTIONS		"gjnpruU"
# define TOGGLE_CASE	32

# define VALID_OBJ_ERR	"The file was not recognized as a valid object file"
# define IS_DIR_ERR		"Is a directory"
# define NO_FILE_ERR	"No such file or directory"
# define PERM_ERR		"Permission denied"
# define MALF_OBJ_ERR	"Malformed object"

# define BAD_STRING_INDEX	"bad string index"

enum			e_endian
{
	CIGAM,
	MAGIC
};

enum			e_value
{
	VALUE_32,
	VALUE_64
};

typedef struct	s_sort
{
	uint32_t		start1;
	uint32_t		end1;
	uint32_t		end2;
	uint32_t		cpt1;
	uint32_t		cpt2;
}				t_sort;

typedef struct	s_symbol
{
	char		*name;
	char		type_char;
	uint64_t	value;
}				t_symbol;

typedef struct	s_bin_file
{
	char					*filename;
	enum e_endian			endian;
	void					*ptr;
	uint64_t				size;
	struct symtab_command	*symtab_lc;
	t_symbol				*symbols;
	uint8_t					text_index;
	uint8_t					data_index;
	uint8_t					bss_index;
}				t_bin_file;

uint8_t			g_flags;
t_bool			g_multi_display;

/*
** Function Prototypes
*/

char			toggle_char(char c);
t_bool			is_external_symbol(char c);
t_bool			is_undefined_symb(char c);
t_bool			is_archi_x86_64(cpu_type_t cpu_type);
t_ex_ret		ret_malloc_err(void);
t_ex_ret		ret_usage(void);
t_ex_ret		activate_opt(char opt_letter);
t_bool			opt_is_activated(char opt_letter);

uint32_t		swap_uint32_if(uint32_t n, enum e_endian endian);
uint64_t		swap_uint64_if(uint64_t n, enum e_endian endian);
void			*check_and_move(t_bin_file *file, void *dest,
					uint64_t needed_size);

char			get_type_char(uint64_t value, uint8_t type, uint8_t n_sect,
					t_bin_file *file);
char			*get_archi_name(cpu_type_t cpu_type, cpu_subtype_t cpu_subtype);

t_ex_ret		process_single_file(char *filename);

t_ex_ret		init_64(t_bin_file *file);
t_ex_ret		handle_64(uint64_t size, void *ptr, char *filename,
					enum e_endian endian);
t_ex_ret		init_32(t_bin_file *file);
t_ex_ret		handle_32(uint64_t size, void *ptr, char *filename,
					enum e_endian endian);
t_ex_ret		handle_fat32(char *filename, uint64_t size, void *ptr,
					enum e_endian endian);
t_ex_ret		handle_fat64(char *filename, uint64_t size, void *ptr,
					enum e_endian endian);
t_ex_ret		handle_archive(char *filename, uint64_t size, void *ptr);
t_ex_ret		ft_nm(uint64_t size, void *ptr, char *filename,
					char *archive_name);

t_bool			value_sort_comp(t_symbol *symb1, t_symbol *symb2);
t_bool			alpha_sort_comp(t_symbol *symb1, t_symbol *symb2);
t_ex_ret		sort_symbols(t_bin_file *file);

void			print_symbols_output(t_symbol *symbols, size_t sym_count,
					enum e_value value_type);

void			clean(t_bin_file *file);

#endif
