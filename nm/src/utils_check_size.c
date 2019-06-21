#include "ft_nm.h"

void	*check_and_move(t_bin_file *file, void *dest, uint64_t needed_size)
{
	if ((uint64_t)(dest + needed_size - file->ptr) > file->size)
		return (NULL);
	return (dest);
}