#include "ft_nm.h"

void	*check_and_move(t_bin_file *file, void *dest, size_t needed_size)
{
	if ((size_t)((dest + needed_size) - file->ptr) > file->size)
		return (NULL);
	return (dest);
}



