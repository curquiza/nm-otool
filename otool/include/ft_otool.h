/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 13:25:44 by curquiza          #+#    #+#             */
/*   Updated: 2019/06/25 13:25:45 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OTOOL_H
# define FT_OTOOL_H

# include "libft.h"

# include <fcntl.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/fat.h>
# include <errno.h>
# include <ar.h>
# include <mach-o/ranlib.h>

# define NOT_OBJ_ERR	"The file is not an object file"
# define NO_FILE_ERR	"No such file or directory"
# define PERM_ERR		"Permission denied"
# define IS_DIR_ERR		"Is a directory"
# define MALF_OBJ_ERR	"Malformed object"

# define TITLE			"Contents of (__TEXT,__text) section"

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

typedef struct	s_symbol
{
	char		*name;
	char		type_char;
	uint64_t	value;
}				t_symbol;

typedef struct	s_bin_file
{
	char			*filename;
	enum e_endian	endian;
	void			*ptr;
	uint64_t		size;
	uint32_t		text_offset;
	uint64_t		text_size;
	uint64_t		text_address;
	cpu_type_t		cpu_type;
}				t_bin_file;

t_bool			g_multi_display;
t_bool			g_title_display_inhib;

/*
** Function Prototypes
*/

uint32_t		swap_uint32_if(uint32_t n, enum e_endian endian);
uint64_t		swap_uint64_if(uint64_t n, enum e_endian endian);
t_bool			is_archi_x86_64(cpu_type_t cpu_type);
t_ex_ret		ret_usage(void);
t_ex_ret		ret_malloc_err(void);
char			*get_archi_name(cpu_type_t cpu_type, cpu_subtype_t cpu_subtype);
void			*check_and_move(t_bin_file *file, void *dest,
					uint64_t needed_size);

t_ex_ret		handle_32(uint64_t size, void *ptr, char *filename,
					enum e_endian endian);
t_ex_ret		handle_64(uint64_t size, void *ptr, char *filename,
					enum e_endian endian);
t_ex_ret		handle_fat32(char *filename, uint64_t size, void *ptr,
					enum e_endian endian);
t_ex_ret		handle_fat64(char *filename, uint64_t size, void *ptr,
					enum e_endian endian);
t_ex_ret		handle_archive(char *filename, uint64_t size, void *ptr);
t_ex_ret		ft_otool(uint64_t size, void *ptr, char *filename,
					char *archive_name);

t_ex_ret		print_output(t_bin_file *file, enum e_value value_type);

#endif
