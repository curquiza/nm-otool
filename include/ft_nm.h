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

typedef struct	s_data
{
	//section
	//flags
	//header ?
	//filename ?
}				t_data;

#endif
