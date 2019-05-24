#include "ft_nm.h"

// t_bool	is_in_file(t_bin_file *file, void *current_pos, size_t needed_size)
// {
// 	size_t		used_size;

// 	used_size = current_pos - file->ptr;
// 	// ft_printf("begin = %d, end = %d\nfile_size = %d, needed_size = %d\n", file->ptr, current_pos, file->size, needed_size);
// 	// ft_printf("used_size = %d\n", used_size);
// 	return (file->size - used_size > needed_size);
// }

void	*check_and_move(t_bin_file *file, void *dest, size_t needed_size)
{
	if ((size_t)((dest + needed_size) - file->ptr) > file->size)
		return (NULL);
	return (dest);
}



