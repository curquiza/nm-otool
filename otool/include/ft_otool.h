#ifndef FT_OTOOL_H
# define FT_OTOOL_H

# include "libft.h"

# include <fcntl.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <mach-o/loader.h>
// # include <mach-o/nlist.h>
# include <mach-o/fat.h>
# include <errno.h>
# include <ar.h>
// # include <mach-o/ranlib.h>

# define NOT_OBJ_ERR	"The file is not an object file"
# define NO_FILE_ERR	"No such file or directory"
# define PERM_ERR		"Permission denied"
# define IS_DIR_ERR		"Is a directory"
# define CMDSIZE_ERR	"Malformed object (cmdsize not a multiple of 8)"
# define FILE_END_ERR	"Malformed object (extends past the end of the file)"

# define TITLE			"Contents of (__TEXT,__text) section"

enum			e_endian
{
	CIGAM,
	MAGIC
};

// enum			e_value
// {
// 	VALUE_32,
// 	VALUE_64
// };

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

uint8_t			g_flags;
t_bool			g_multi_display;


/*
** Function Prototypes
*/

uint32_t		swap_uint32_if(uint32_t n, enum e_endian endian);
uint64_t		swap_uint64_if(uint64_t n, enum e_endian endian);
t_ex_ret		ret_usage(void);
t_ex_ret		ret_malloc_err(void);
void			*check_and_move(t_bin_file *file, void *dest,
					uint64_t needed_size);

t_ex_ret		handle_32(uint64_t size, void *ptr, char *filename,
					enum e_endian endian);
t_ex_ret		handle_64(uint64_t size, void *ptr, char *filename,
					enum e_endian endian);
t_ex_ret		ft_otool(uint64_t size, void *ptr, char *filename,
					char *archive_name);


#endif
